#include<stdio.h>
#include<ctype.h>//ctype.h是C标准函数库中的头文件，定义了一批C语言字符分类函数，用于测试字符是否属于特定的字符类别
#include<conio.h>//conio.h库文件定义了通过控制台进行数据输入和数据输出的函数，主要是一些用户通过按键盘产生的对应操作
#include<string.h>
#include<stdlib.h>
//保留字数目与保留字数组
#define keywordSum 8
char *keyword[keywordSum] = {"if","else","for","while","read","write","do","int"};
//纯单分界符（改动）
char singleword[50] = { '+','-','*','(',')','{','}',',',';',':' ,'.'};
//双分界符的首字母
char doubleword[10] = { '>','<','=','!' };
//输入、输出文件名
char Scanin[300],Scanout[300],Result[300];
//指向文件的指针
FILE *fin, *fout,*fp,*fr;
char token[20], token1[40];//token保存单词符号，token1保存单词值

//函数声明
int TESTscan();
int TESTparse();
int program();
int declaration_list();
int statement_list();
int if_stat();
int while_stat();
int for_stat();
int write_stat();
int read_stat();
int declaration_stat();
int compound_stat();
int expression_stat();
int statement();
int expression();
int bool_expr();
int additive_expr();
int term();
int factor();

//词法分析函数
//用于对保留字数组进行冒泡排序函数（为折半查找做准备）
void sort(char *KW[]){

	int i,j;

	char *temp;

	for(i=0;i<keywordSum;i++){

		for(j=0;j<keywordSum-1;j++){

			if(strcmp(KW[j],KW[j+1])>0){

				temp = KW[j];

				KW[j] = KW[j+1];

				KW[j+1] = temp;

			}

		}

	}

}



//用于查找保留字表的折半查找函数（保留字不区分大小写）
int Search_Bin(char *KW[],char *keyword){

	sort(KW);

	int low=0,high=keywordSum-1;

	int mid;

	while(low<=high){

		mid = (low+high)/2;

		if(stricmp(keyword,KW[mid])==0) return 1;		//stricmp比较不区分大小写 返回1表示查找到

		else if(stricmp(keyword,KW[mid])>0) low=mid+1;

		else high=mid-1;

	}

	return 0;											//返回0表示查找失败

}



int TESTscan(){

	char ch,token[40];									//ch用于保存当前读出的字符，token用于保存识别出的单词

	int es=0,j,n;										//es为错误识别代码，0表示没有错误。

	int linenum=1;										//用于保存行号

	printf("请输入源程序文件名（包括路径）：");

	scanf("%s",Scanin);

	printf("请输入词法分析输出文件名（包括路径）：");

	scanf("%s",Scanout);

	if((fin = fopen(Scanin,"r"))==NULL){

		printf("\n打开词法分析输入文件出错！\n");

		return 1;										//输入文件出错返回错误代码1

	}

	if((fout = fopen(Scanout,"w"))==NULL){

		printf("\n打开词法分析1输出文件出错！\n");

		return 2; 										//输出文件出错返回错误代码2

	}

	ch = getc(fin);

	while(ch!=EOF){

		while(ch==' '||ch=='\n'||ch=='\t'){

			if(ch=='\n')								//记录行号

				linenum++;

			ch=getc(fin);

		}

		if(isalpha(ch)){								//如果ch是字母的话，进行标识符处理

			token[0]=ch;

			j=1;

			ch=getc(fin);

			while(isalnum(ch)){							//如果ch是字母或者数字的话

				token[j++]=ch;							//组合的标识符保存在token中

				ch=getc(fin);							//读下一个字符

			}

			token[j]='\0';								//标识符组合结束

			//查保留字

			n=Search_Bin(keyword,token);

			if(n==1)									//是保留字
       {      if( token>='A' && token<='Z')
                {
                    printf("%s\t%s\n",token+32,token+32);
				fprintf(fout,"%s\t%s\n",token+32,token+32);
                }
                printf("%s\t%s\n",token,token);
				fprintf(fout,"%s\t%s\n",token,token);}

			else

				{printf("%s\t%s\n","ID",token);
				fprintf(fout,"%s\t%s\n","ID",token);}	//不是保留字

		}

		else if(isdigit(ch)){							//如果ch是数字的话，对数字进行处理

			token[0]=ch;

			j=1;

			ch=getc(fin);

			while(isdigit(ch)){							//如果是数字则整合整数，否则退出

				token[j++]=ch;

				ch=getc(fin);

			}

			token[j]='\0';

			printf("%s\t%s\n","NUM",token);
			fprintf(fout,"%s\t%s\n","NUM",token);

		}

		else if(strchr(singleword,ch)!=NULL){			//strchr用于查找某字符是否存在于某字符数组中，是则返回指针，不是则返回NULL

			token[0]=ch;

			token[1]='\0';

			ch=getc(fin);								//读下一个符号以便识别单词

			printf("%s\t%s\n",token,token);
			fprintf(fout,"%s\t%s\n",token,token);

		}

		else if(strchr(doubleword,ch)!=NULL){

			token[0]=ch;

			ch=getc(fin);								//读下一个字符判断是否是双分界符

			if((token[0]!='&'&&token[0]!='|'&&ch=='=')||(token[0]=='|'&&ch=='|')||(token[0]=='&'&&ch=='&')){				//如果是=，|，&则组合双分界符

				token[1]=ch;

				token[2]='\0';

				ch=getc(fin);

			}

			else{										//否则为单分界符

				token[1]='\0';

			}

			if(token[0]=='!'||token[0]=='<'||token[0]=='>'||token[0]=='='){

				printf("%s\t%s\n",token,token);
				fprintf(fout,"%s\t%s\n",token,token);

			}

			else{

				printf("%d行发生错误",linenum);
				printf("\n%s\t%s\n","ERROR",token);
				fprintf(fout,"\n%s\t%s\n","ERROR",token);

				fprintf(fout,"%s  %d\n\n","错误行号为：",linenum);

			}

		}

		else if(ch=='/'){								//注释处理

			ch=getc(fin);

			if(ch=='*'){								//如果下一个字符是*则开始进行注释处理

				char ch1;

				ch1=getc(fin);

				do{

					if(ch1=='\n'){

						linenum++;

					}

					ch=ch1;

					ch1=getc(fin);

				}while((ch!='*'||ch1!='/')&&ch1!=EOF);	//删除注释

				ch=getc(fin);

			}

			else{										//不是*则输出单分界符

				token[0]='/';

				token[1]='\0';

				printf("%s\t%s\n",token,token);
				fprintf(fout,"%s\t%s\n",token,token);

			}

		}

		else{

			token[0]=ch;								//处理错误

			token[1]='\0';

			ch=getc(fin);

			es=3;										//设置错误代码

			printf("%d行发生错误",linenum);
			printf("\n%s\t%s\n","ERROR",token);

			fprintf(fout,"\n%s\t%s\n","ERROR",token);

			fprintf(fout,"%s  %d\n\n","错误行号为：",linenum);

		}

	}

	fclose(fin);

	fclose(fout);

	return es;

}

//语法分析函数
int TESTparse()
{

	int es = 0;

	printf("请输入词法分析输出文件名（包括路径）：");
	scanf("%s",Scanout);
	if ((fp = fopen(Scanout, "r")) == NULL)
	{
		printf("\n打开词法分析输出文件出错！\n");
		es=10;
	}
	printf("请输入语法分析输出文件名（包括路径）：");
	scanf("%s", Result);
	if ((fr = fopen(Result, "w")) == NULL)
	{
		printf("\n打开语法分析输出文件出错！\n");
		return(8);
	}
	if (es == 0)
		es = program();
	printf("\n语法分析结果如下：\n");
	switch (es)
	{
	case 0:
		printf("语法分析成功！\n");
		fprintf(fr,"\n%s\n","语法分析成功！\n");
		break;
	case 1:
		printf("缺少{\n");
		fprintf(fr, "\n%s\n", "缺少{\n");
		break;
	case 2:
		printf("缺少}\n");
		fprintf(fr, "\n%s\n", "缺少}\n");
		break;
	case 3:
		printf("缺少识别符\n");//declaration_stat()
		fprintf(fr, "\n%s\n", "缺少识别符\n");
		break;
	case 4:
		printf("缺少分号\n");
		fprintf(fr, "\n%s\n", "缺少分号\n");
		break;
	case 5:
		printf("缺少(\n");
		fprintf(fr, "\n%s\n", "缺少（\n");
		break;
	case 6:
		printf("缺少)\n");
		fprintf(fr, "\n%s\n", "缺少）\n");
		break;
	case 7:
		printf("缺少操作数\n");//factor()
		fprintf(fr, "\n%s\n", "缺少操作数\n");
		break;
	case 8:
		printf("\n打开语法分析输出文件出错！\n");
		fprintf(fr, "\n%s\n", "\n打开语法分析输出文件出错！\n");
		break;
	case 10:
		printf("\n打开词法分析输出文件出错！\n");
		fprintf(fr, "\n%s\n", "\n打开词法分析输出文件出错！\n");
		break;
	}
	fclose(fp);
	fclose(fr);
	return(es);
}

//程序 子函数
int program()
{
	int es = 0;
	fscanf(fp,"%s\t%s\n",&token,&token1);//“读文件”函数
	fprintf(fr, "%s\t%s\n", &token, &token1);
	if (strcmp(token, "{"))//相等时，返回“0”，不执行该语句，比较的是token
	{
		es = 1;
		return es;
	}
	fscanf(fp, "%s\t%s\n", &token, &token1);
	fprintf(fr, "%s\t%s\n", &token, &token1);
	es = declaration_list();//fscanf和printf操作包含在子函数中
	if (es > 0)
		return(es);
	es = statement_list();
	if (es > 0)
		return(es);
	if (strcmp(token, "}"))
	{
		es = 2;
		return(es);
	}
	return(es);
}

int declaration_list()
{
	int es = 0;
	while ((strcmp(token,"int")==0)||(strcmp(token,"char")==0))//扩充了char型
	{
		es = declaration_stat();
		if (es > 0)
			return(es);
	}
	return(es);
}

int declaration_stat()
{
	int es = 0;
	fscanf(fp, "%s\t%s\n", &token, &token1);
	fprintf(fr, "%s\t%s\n", &token, &token1);
	if (strcmp(token, "ID"))
		return(es=3);//缺少识别符
	fscanf(fp, "%s\t%s\n", &token, &token1);
	fprintf(fr, "%s\t%s\n", &token, &token1);
	if (strcmp(token, ";"))
		return(es = 4);
	fscanf(fp, "%s\t%s\n", &token, &token1);//读下一个token，用于判断declaration_list()的循环条件
	fprintf(fr, "%s\t%s\n", &token, &token1);
	return(es);
}

int statement_list()
{
	int es = 0;
	while (strcmp(token, "}"))//当扫描到token是“}”时，while（0）,此语句不执行，即不再有statement了。program结束！
		                      //结合program()函数来看
	{
		es = statement();
		if (es > 0)
			return(es);
	}
	return(es);
}

int compound_stat()
{
	int es = 0;
	fscanf(fp, "%s\t%s\n", &token, &token1);
	fprintf(fr, "%s\t%s\n", &token, &token1);
	es = statement_list();
	return(es);
}

int statement()
{
	int es = 0;
	if (es == 0 && strcmp(token, "if") == 0)
	{
		fprintf(fr, "\n%s\n", "\n---if语句---\n");
		printf("\n源程序存在if语句\n");
		es = if_stat();
	}
	if (es == 0 && strcmp(token, "while") == 0)
		{
		fprintf(fr, "\n%s\n", "\n---while语句---\n");
			printf("\n源程序存在while语句\n");
			es = while_stat();
		}
	if (es == 0 && strcmp(token, "for") == 0)
		{
		fprintf(fr, "\n%s\n", "\n---for语句---\n");
			printf("\n源程序存在for语句\n");
			es = for_stat();
		}
	if (es == 0 && strcmp(token, "read") == 0)
		{
		fprintf(fr, "\n%s\n", "\n---read语句---\n");
			printf("\n源程序存在read语句\n");
			es = read_stat();
		}
	if (es == 0 && strcmp(token, "write") == 0)
		{
		fprintf(fr, "\n%s\n", "\n---write语句---\n");
			printf("\n源程序存在write语句\n");
			es = write_stat();
		}
	if (es == 0 && strcmp(token, "{") == 0)
		{
		fprintf(fr, "\n%s\n", "\n---复合语句---\n");
			printf("\n源程序存在复合语句\n");
			es = compound_stat();
		}
	if (es == 0 && strcmp(token, "ID") == 0 || strcmp(token, "NUM") == 0 || strcmp(token, "(") == 0)
		{

			printf("\n源程序存在表达式语句\n");
			es = expression_stat();
		}
	return(es);
}

int if_stat(){
    int es=0;

    fscanf(fp,"%s\t%s\n",&token,&token1);
	fprintf(fr, "%s\t%s\n", &token, &token1);
    if(strcmp(token,"("))
		return(es=5);
    fscanf(fp,"%s\t%s\n",&token,&token1);
	fprintf(fr, "%s\t%s\n", &token, &token1);
    es=expression();
    if(es>0)
		return(es);
    if(strcmp(token,")"))
		return(es=6);
    fscanf(fp,"%s\t%s\n",&token,&token1);
	fprintf(fr, "%s\t%s\n", &token, &token1);
    es=statement();
    if(es>0)
		return(es);
    if(strcmp(token,"else")==0)
    {
      fscanf(fp,"%s\t%s\n",&token,&token1);
	  fprintf(fr, "%s\t%s\n", &token, &token1);
      es=statement();
      if(es>0)
		  return(es);
    }
    return(es);
}

int while_stat()
{
	int es = 0;

	fscanf(fp, "%s\t%s\n", &token, &token1);
	fprintf(fr, "%s\t%s\n", &token, &token1);
	if (strcmp(token, "("))
		return(es = 5);
	fscanf(fp, "%s\t%s\n", &token, &token1);
	fprintf(fr, "%s\t%s\n", &token, &token1);
	es = expression();
	if (es>0)
		return(es);
	if (strcmp(token, ")"))
		return(es = 6);
	fscanf(fp, "%s\t%s\n", &token, &token1);
	fprintf(fr, "%s\t%s\n", &token, &token1);
	es = statement();
	return(es);
}

int for_stat()
{
	int es = 0;

	fscanf(fp, "%s\t%s\n", &token, &token1);
	fprintf(fr, "%s\t%s\n", &token, &token1);
	if (strcmp(token, "("))
		return(es = 5);
	fscanf(fp, "%s\t%s\n", &token, &token1);
	fprintf(fr, "%s\t%s\n", &token, &token1);
	es = expression();
	if (es>0)
		return(es);
	if (strcmp(token, ";"))
		return(es = 4);
	fscanf(fp, "%s\t%s\n", &token, &token1);
	fprintf(fr, "%s\t%s\n", &token, &token1);
	es = expression();
	if (es>0)
		return(es);
	if (strcmp(token, ";"))
		return(es = 4);
	fscanf(fp, "%s\t%s\n",&token, &token1);
	fprintf(fr, "%s\t%s\n", &token, &token1);
	es = expression();
	if (es>0)
		return(es);
	if (strcmp(token, ")"))
		return(es = 6);
	fscanf(fp, "%s\t%s\n", &token, &token1);
	fprintf(fr, "%s\t%s\n", &token, &token1);
	es = statement();

	return(es);
}

int write_stat()
{
	int es = 0;

	fscanf(fp, "%s\t%s\n", &token, &token1);
	fprintf(fr, "%s\t%s\n", &token, &token1);
	es = expression();
	if (es>0)
		return(es);
	if (strcmp(token, ";"))
		return(es = 4);
	fscanf(fp, "%s\t%s\n", &token, &token1);
	fprintf(fr, "%s\t%s\n", &token, &token1);
	return(es);
}

int read_stat()
{
	int es = 0;

	fscanf(fp, "%s\t%s\n", &token, &token1);
	fprintf(fr, "%s\t%s\n", &token, &token1);
	if (strcmp(token, "ID"))
		return(es = 3);
	fscanf(fp, "%s\t%s\n", &token, &token1);
	fprintf(fr, "%s\t%s\n", &token, &token1);
	if (strcmp(token, ";"))
		return(es = 4);
	fscanf(fp, "%s\t%s\n", &token, &token1);
	fprintf(fr, "%s\t%s\n", &token, &token1);
	return (es);
}

int expression_stat()
{
	int es = 0;
	if (strcmp(token, ";") == 0)
	{
		fscanf(fp, "%s\t%s\n", &token, &token1);
		fprintf(fr, "%s\t%s\n", &token, &token1);
		return(es);
	}
	es = expression();
	if (es > 0)
		return(es);
	if (es == 0 && strcmp(token, ";") == 0)
	{
		fscanf(fp, "%s\t%s\n", &token, &token1);
		fprintf(fr, "%s\t%s\n", &token, &token1);
		return(es);
	}
	else
	{
		es = 4;
		return(es);//缺少；
	}
}

int expression()
{
	int es = 0, fileadd;
	char token2[20], token3[40];
	if (strcmp(token, "ID") == 0)
	{
		fileadd = ftell(fp);
		fscanf(fp, "%s\t%s\n", &token2, &token3);
		fprintf(fr, "%s\t%s\n", &token2, &token3);
		if (strcmp(token2, "=") == 0)
		{
			fscanf(fp, "%s\t%s\n", &token, &token1);
			fprintf(fr, "%s\t%s\n", &token, &token1);
			es = bool_expr();
			if (es>0)
				return(es);
		}
		else
		{
			fseek(fp, fileadd, 0);

			es = bool_expr();
			if (es>0)
				return(es);
		}
	}
	else
		es = bool_expr();
	return(es);
}

int bool_expr()
{
	int es = 0;
	es = additive_expr();
	if (es>0)
		return(es);
	if (strcmp(token, ">") == 0 || strcmp(token, ">=") == 0 || strcmp(token, "<") == 0 || strcmp(token, "<=") == 0 || strcmp(token, "==") == 0 || strcmp(token, "!=") == 0)
	{
		fscanf(fp, "%s\t%s\n", &token, &token1);
		fprintf(fr, "%s\t%s\n", &token, &token1);
		es = additive_expr();
		if (es>0)
			return(es);
	}
	return(es);
}

int additive_expr(){
	int es = 0;
	es = term();
	if (es>0)
		return(es);
	while (strcmp(token, "+") == 0 || strcmp(token, "-") == 0)
	{
		fscanf(fp, "%s\t%s\n", &token, &token1);
		fprintf(fr, "%s\t%s\n", &token, &token1);
		es = term();
		if (es>0) return(es);
	}
	return(es);
}

int term(){
	int es = 0;
	es = factor();
	if (es>0)
		return(es);
	while (strcmp(token, "*") == 0 || strcmp(token, "/") == 0)
	{
		fscanf(fp, "%s\t%s\n", &token, &token1);
		fprintf(fr, "%s\t%s\n", &token, &token1);
		es = factor();
		if (es>0)
			return(es);
	}
	return(es);
}

int factor(){
	int es = 0;
	if (strcmp(token, "(") == 0)
	{
		fscanf(fp, "%s\t%s\n", &token, &token1);
		fprintf(fr, "%s\t%s\n", &token, &token1);
		es = expression();
		if (es>0)
			return(es);
		if (strcmp(token, ")"))
			return(es = 6);
		fscanf(fp, "%s\t%s\n", &token, &token1);
		fprintf(fr, "%s\t%s\n", &token, &token1);
	}
	else
	{
		if (strcmp(token, "ID") == 0 || strcmp(token, "NUM") == 0)
		{
			fscanf(fp, "%s\t%s\n", &token, &token1);
			fprintf(fr, "%s\t%s\n", &token, &token1);
			return(es);
		}
		else
		{
			es = 7;
			return(es);
		}
	}
	return(es);
}

//主函数
void main()
{
  int es=0;
  es=TESTscan();
  if(es>0)
  {printf('词法分析出错');}
  else
  {printf('词法分析成功');}
  if (es == 0)
  {
		es = TESTparse();
		if (es == 0)
			printf("语法分析成功！\n");
		else
			printf("语法分析错误！\n");
  }
	system("pause");
}
