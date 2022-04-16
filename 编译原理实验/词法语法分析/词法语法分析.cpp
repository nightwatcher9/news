#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include <string.h>
#include<stdlib.h>
using namespace std;
#define MAX 200
#define keywordSum 11
char *keyword[keywordSum] = {"if","else","for","while","read","write","do","int","function","switch","case"};
//纯单分界符（改动）
char singleword[50] = { '+','-','*','(',')','{','}',',',';',':' ,'.'};
//双分界符的首字母
char doubleword[10] = { '>','<','=','!' };
int Current=0;//用于统计全局变量的个数
char token[20],token1[40];
char scanin[300],scanout[300];//词法分析输入、输出文件名
char Scanin[300],Scanout[300];//前者表示语法输入文件的路径，后者表示语法树输出文件的路径
char WORD[MAX][MAX];//用来存储全局变量
FILE *fin, *fout,*fp,*fr;
int end=0;//判断是否结束语法分析，main中会修改该值
//函数声明
int TESTscan();
int TESTparse();
int program();
int fun_declaration(int section);
int main_declaration(int section);
int function_body(int section,char*ID);
int declaration_list(int section,int &current,char word[MAX][MAX]);
int declaration_stat(int section,int &current,char word[MAX][MAX]);
int statement_list(int section,char word[MAX][MAX],char*ID);
int statement(int section,char word[MAX][MAX],char*ID);
int if_stat(int section,char word[MAX][MAX],char*ID);
int while_stat(int section,char word[MAX][MAX],char*ID);
int for_stat(int section,char word[MAX][MAX],char*ID);
int do_while_stat(int section,char word[MAX][MAX],char*ID);
int write_stat(int section,char word[MAX][MAX],char*ID);
int read_stat(int section,char word[MAX][MAX],char*ID);
int compound_stat(int section,char word[MAX][MAX],char*ID);
int expression_stat(int section,char word[MAX][MAX],char*ID);
int call_stat(int section,char word[MAX][MAX],char*ID);
int expression(int section,char word[MAX][MAX],char*ID);
int bool_expr(int section,char word[MAX][MAX],char*ID);
int additive_expr(int section,char word[MAX][MAX],char*ID);
int term(int section,char word[MAX][MAX],char*ID);
int factor(int section,char word[MAX][MAX],char*ID);
int break_stat(int section);
int continue_stat(int section);
int switch_stat(int section,char word[MAX][MAX],char*ID);
int case_list(int section,char word[MAX][MAX],char*ID);//case序列

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
	scanf("%s",scanin);

  printf("请输入词法分析输出文件名（包括路径）：");
	scanf("%s",scanout);

	if((fin = fopen(scanin,"r"))==NULL){

		printf("\n打开词法分析输入文件出错！\n");

		return 1;										//输入文件出错返回错误代码1

	}

	if((fout = fopen(scanout,"w"))==NULL){

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
       {      /*if( token>='A' && token<='Z')
                {
                    printf("%s\t%s\n",token+32,token+32);
				fprintf(fout,"%s\t%s\n",token+32,token+32);
                }*/
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
  //  printf("测试一下能不能返回");
	return (es);

}














//控制语法树中空格输出的函数
void space(int section){
    for(int i=0;i<section;i++)
        fprintf(fout,"    ");
}
//语法分析程序
int TESTparse(){
    int es=0;
    fp=fopen(scanout,"r");//以词法分析的输出文件作为输入
    printf("\n请输入语法树输出文件的路径:\n");
    scanf("%s",Scanout);
    if((fout=fopen(Scanout,"w"))==NULL){
        es=13;//打开 输出语法树的文件出错错误
    }
    if(es==0)//正确创建文件后
        es=program();//进行分析
    printf("-------语法分析结果---------\n");
    switch(es){
        case 0:
            printf("语法分析过程中未出现错误！\n");
            break;
        case 1:
            printf("缺少标识符ID！\n");
            break;
        case 2:
            printf("缺少'('\n");
            break;
        case 3:
            printf("缺少')'\n");
            break;
        case 4:
            printf("缺少main函数\n");
            break;
        case 5:
            printf("缺少'{'\n");
            break;
        case 6:
            printf("缺少'}'\n");
            break;
        case 7:
            printf("缺少分号\n");
            break;
        case 8:
            printf("do while语句中缺少'while'\n");
            break;
        case 9:
            printf("缺少操作数!\n");
            break;
        case 10:
            printf("变量重复声明!\n");
            break;
        case 11:
            printf("变量调用前未声明!\n");
            break;
        case 12:
            printf("\n打开文件%s错误!\n",scanout);//词法分析输出文件是语法分析的输入
            break;
        case 13:
            printf("\n创建语法树输出文件%s时出错!",Scanout);
            break;
        case 14:
        	printf("缺少':' \n");
        	break;
        case 15:
        	printf("switch语句中缺少break!\n");
        	break;
        case 16:
			printf("switch语句中没有case!\n");
			break;
		case 17:
			printf("变量连续定义时缺少,\n");
			break;
		case 18:
			printf("main函数缺少 } !\n");
			break;
    }
    fclose(fp);
    fclose(fout);
    return es;
}
//一、<program> →<declaration_list>{ fun_declaration }<main_declaration>
//<程序>→<声明序列>{函数}<主函数>
//附加功能：全局变量的声明
int program(){
    int es=0;
    char *ID;
    int section=0;//画语法树时用于统计空格的数量
    space(section++);//输出后section=1
    fprintf(fout,"<program>\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格或换行时会结束
    printf("%s %s\n",token,token1);
    es=declaration_list(section,Current,WORD);//全局变量声明部分 section=1
    //declaration_list多读一个

    if(es>0)//如果出现错误则返回
        return es;
    while(strcmp(token,"function")==0){//读到标识符中函数的定义
        es=fun_declaration(section);//section=1
        if(es>0)
            return es;
            //error 多读了
        //fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束
        //printf("%s %s\n",token,token1);
    }
    es=main_declaration(section);//main函数的定义  section=1
    return es;
}

//二、<fun_declaration> → function [int]ID'(' [int ID] ')' <function_body>
//<函数>→functionID'('[int ID]')'<函数体>
// 通俗解释：function [int] 函数名([int 参数名]) 函数体
int fun_declaration(int section){
    int es=0;
    char *ID;//存储函数参数
    space(section++);//执行后section=2
    fprintf(fout,"<fun_declaration>\n");
    space(section);//section=2
    fprintf(fout,"function\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束
    printf("%s %s\n",token,token1);
    if(strcmp(token,"int")==0){//函数有int型的返回参数
        space(section);//section=2
        fprintf(fout,"int\n");
        fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束
        printf("%s %s\n",token,token1);
    }
    if(strcmp(token,"ID"))//判断函数名是否合法
        return (es=1);//不是标识符返回1
    space(section);//section=2
    fprintf(fout,"ID\n");
    space(section+1);//section=2
    fprintf(fout,"%s\n",token1);//输出标识符(函数名)
    fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束
    printf("%s %s\n",token,token1);
    if(strcmp(token,"("))
        return (es=2);//缺少"("返回2
    space(section);//section=2
    fprintf(fout,"(\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束
    printf("%s %s\n",token,token1);

    //检查是否有参数
    if(strcmp(token,"int")==0){//int关键字匹配成功
        space(section);//section=2
        fprintf(fout,"int\n");
        fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束
        printf("%s %s\n",token,token1);
        if(strcmp(token,"ID"))//查看参数是否为合法标识符
            return (es=1);//不是标识符返回1
        strcpy(ID,token1);//将参数记录到ID中

        space(section);//section=2
        fprintf(fout,"ID\n");
        space(section+1);//section=2
        fprintf(fout,"%s\n",token1);//输出参数中的标识符
        fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束
        printf("%s %s\n",token,token1);
    }
    if(strcmp(token,")"))
        return(es=3);//缺少")"返回3
    space(section);//section=2
    fprintf(fout,")\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束
    printf("%s %s\n",token,token1);

    //保证每次输出后，读入了下一行，进入函数直接进行输出和判断等操作
    es=function_body(section,ID);//进入函数体的定义
    return es;
}
//三、<main_declaration>::=main'('')'<function_body>
//<主函数>→main'('')'<函数体>
//通俗解释：即 main() 函数体
int main_declaration(int section){
    int es=0;
    char *ID;
    space(section++);//执行后seciton=2
    fprintf(fout,"<main_declaration>\n");
    if(strcmp(token1,"main"))
        return (es=4);//没有"main" 返回
    space(section);//section=2
    fprintf(fout,"main\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束
    printf("%s %s\n",token,token1);

    if(strcmp(token,"("))
        return (es=2);//缺少"("返回2
    space(section);//section=2
    fprintf(fout,"(\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束
    printf("%s %s\n",token,token1);
    if(strcmp(token,")"))
        return(es=3);//缺少")" 返回3

    space(section);//section=2
    fprintf(fout,")\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束
    printf("%s %s\n",token,token1);

    //保证每次输出后，读入了下一行，进入函数直接进行输出和判断等操作

    end=1;//进入了main的语法分析，main在是在function后进行分析的，因此设置为终止
    es=function_body(section,ID);//进入函数体的定义 section=2
    return es;
}
//四、<function_body>::='{'<declaration_list><statement_list>'}'
//<函数体>→'{'<声明序列><语句序列>'}'
//通俗解释: function_body{declaration_list statement_list }
//函数体中的内容： 声明序列 语句序列
int function_body(int section,char *ID){//ID是函数的参数 section=2
    int es=0;
    int current=0;//全局变量个数
    char word[MAX][MAX];//记录全局变量  一个函数内可以声明20个长度低于20的变量
    space(section++);//执行后section=3
    fprintf(fout,"<function_body>\n");
    if(strcmp(token,"{"))
        return (es=5);//缺少"{"

    space(section);//section=3
    fprintf(fout,"{\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束
    printf("%s %s\n",token,token1);

    //在进入声明和定义之前，已经读入了下一字符赋值给token了，所以进入函数后直接输出，接着比较

    es=declaration_list(section,current,word);//进入函数体中的声明部分（声明序列）section=3
    //declation_list多读
    if(es>0)//声明部分出错
        return es;

    es=statement_list(section,word,ID);//进入函数体中的定义部分 （定义序列）section=3
    //statement_list多读
    if(es>0)//定义部分出错
        return es;

    if((strcmp(token,"}"))&&(end==1))
        return (es=17);//main缺少"}"返回17
    else if(strcmp(token,"}")&&(end==0))
    	return (es=6);//缺少}，返回6
    space(section);
//	printf("%s %s\n",token,token1);
    fprintf(fout,"}\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束
  //  if()
    return es;
}
//五、<declaration_list>::={<declaration_stat>}
//<声明序列>→{声明语句}

int declaration_list(int section,int &current,char word[MAX][MAX]){//由于已经读入了字符给token，所以直接输出和比较 section=3
    int es=0;
    space(section++);//执行后section=4
    fprintf(fout,"<declaration_list>\n");
    while(strcmp(token,"int")==0){//如果是int型的声明
        es=declaration_stat(section,current,word);//进入声明语句 section=4
        if(es>0)
            return es;
    }
    return es;
}
//六、<declaration_stat>::=int ID{,ID};
//<声明语句>→int ID{,ID};
int declaration_stat(int section,int &current,char word[MAX][MAX]){
    int es=0;
    int i=0;//用来检查变量是否重复
    space(section++);
    fprintf(fout,"<declaration_stat>\n");
    space(section);
    fprintf(fout,"int\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束
    printf("%s %s\n",token,token1);

    while(strcmp(token,";")!=0)//没读到;时
	{
    if(strcmp(token,"ID"))
        return (es=1);//不是标识符返回1
    while(i<current){//判断是否与全局变量冲突
        if(strcmp(token1,word[i])==0)//查看当前函数定义的变量是否和全部变量冲突
           return (es=10);//变量重复声明
        i++;
    }
    strcpy(word[current++],token1);//新的变量加入到二维数组中，同时数量加一
    space(section);
    fprintf(fout,"ID\n");

    space(section+1);
    fprintf(fout,"%s\n",token1);//把标识符输出到文件
    fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束
    printf("%s %s\n",token,token1);
    if(strcmp(token,";")==0)//如果直接是一个ID后就是分号
    {
    	space(section);
    	fprintf(fout,";\n");
    	fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束
    	printf("%s %s\n",token,token1);
    	return es;//读到;时结束
	}
	//当读到不是分号
    if(strcmp(token,","))
        return (es=16);//缺少分号返回7
    space(section);
    fprintf(fout,",\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束
    printf("%s %s\n",token,token1);
    }
    //看定义的末尾是否为;
    if(strcmp(token,";")==0)
    {
    	space(section);
    	fprintf(fout,";\n");
    	fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束
    	printf("%s %s\n",token,token1);
    	return es;//读到;时结束
	}
	else
	return (es=7);//缺少分号
}
//七、<statement_list>::={<statement>}
//<语句序列>→{<语句>}
int statement_list(int section,char word[MAX][MAX],char *ID){//由于已经读入了字符给token，所以直接输出和比较
    int es=0;
    space(section++);//输出空格  且之后输出的会多一个空格
    fprintf(fout,"<statement_list>\n");
    while(strcmp(token,"}")){//follow集是{}}  如果没读到'}'则一直调用statement函数
        es=statement(section,word,ID);//读入语句，且保持输出的空格数一致 statement多读一个
		if(strcmp(token," ")==0)//当读到后续为空字符时
		return (es=17);
        if(es>0)//定义部分出错
            return es;
    }
    return es;
}

//判断声明的语句是哪种类型，接着进入对应的分析函数
int statement(int section,char word[MAX][MAX],char*ID){
    int es=0;
    space(section++);//输出空格，且之后的输出会多一个空格
    fprintf(fout,"<statement>\n");
    if(es==0&&strcmp(token,"if")==0){
        es=if_stat(section,word,ID);
    }
    else if(es==0&&strcmp(token,"while")==0){
        es=while_stat(section,word,ID);
        return es;
    }
    else if(es==0&&strcmp(token,"do")==0){
        es=do_while_stat(section,word,ID);
    }
    else if(es==0&&strcmp(token,"for")==0){
        es=for_stat(section,word,ID);
    }
    else if(es==0&&strcmp(token,"switch")==0)//新增switch语句的识别
        es=switch_stat(section,word,ID);
    else if(es==0&&strcmp(token,"read")==0){
        es=read_stat(section,word,ID);
    }
   else if(es==0&&strcmp(token,"write")==0){
        es=write_stat(section,word,ID);
        return es;
    }
    else if(es==0&&strcmp(token,"{")==0){//复合语句first集是{ { } for if while等语句的复合语句
        es=compound_stat(section,word,ID);
    }
    else if(es==0&&strcmp(token,"ID")==0||strcmp(token,"NUM")==0||strcmp(token,"(")==0||strcmp(token,";")==0){//书上好像少一个分号的判断
        es=expression_stat(section,word,ID);
    }
    else if(es==0&&strcmp(token,"call")==0){
        es=call_stat(section,word,ID);
    }
    else if(es==0&&strcmp(token,"break")==0){
        es=break_stat(section);
    }
    else if(es==0&&strcmp(token,"continue")==0){
        es=continue_stat(section);
    }
    else return(es=6);
    return es;
}
//九、<if_stat>::=if'('<expression>')'<statement>[else<statement>]
//<if语句>→if’(’<表达式>’)’<语句>[else<语句>]
//通俗解释: if(expression) 语句1 [else 语句2]
int if_stat(int section,char word[MAX][MAX],char*ID){
   int es=0;
    space(section++);
    fprintf(fout,"<if_stat>\n");
    space(section);
    fprintf(fout,"if\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束
    printf("%s %s\n",token,token1);
    if(strcmp(token,"("))
        return (es=2);//缺少"("
    space(section);
    fprintf(fout,"(\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束
    printf("%s %s\n",token,token1);

    es=expression(section,word,ID);//if中的表达式
    //expression多读一个

    if(es>0)
        return es;
    if(strcmp(token,")"))
        return (es=3);//缺少")"
    space(section);
    fprintf(fout,")\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束
    printf("%s %s\n",token,token1);

    es=statement(section,word,ID);//if语句中的语句
    if(es>0)
        return es;
    //statement结束后多读一个
    if(strcmp(token,"else")==0){
        space(section);
        fprintf(fout,"else\n");
        fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束
        printf("%s %s\n",token,token1);

        es=statement(section,word,ID);//else中的语句
        if(es>0)
            return es;
    }
    return es;
}
//十、<while_stat>::=while'('<expression>')’<statement>
//<while语句>→while'('<表达式>')'  '{' <语句> '}'
int while_stat(int section,char word[MAX][MAX],char*ID){
    int es=0;
    space(section++);//输出空格，之后的空格会多一个
    fprintf(fout,"<while_stat>\n");
    space(section);
    fprintf(fout,"while\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束
    printf("%s %s\n",token,token1);
    if(strcmp(token,"("))
        return (es=2);//缺少"("

    space(section);
    fprintf(fout,"(\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束
    printf("%s %s\n",token,token1);

    //while中的语句
    es=expression(section,word,ID);//多读一个
    if(es>0)
        return es;
    if(strcmp(token,")"))
        return (es=3);//缺少")"
    space(section);
    fprintf(fout,")\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束
    printf("%s %s\n",token,token1);

    es=statement(section,word,ID);


    return es;
}
//11.<for_stat>::=for'('<expression>;<expression>;<expression>')'<statement>
//<for语句>→for'('<表达式>;<表达式>;<表达式>')'<语句>
int for_stat(int section,char word[MAX][MAX],char*ID){
    int es=0;
    space(section++);
    fprintf(fout,"<for_stat>\n");
    space(section);
    fprintf(fout,"for\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束
    printf("%s %s\n",token,token1);
    if(strcmp(token,"("))
        return (es=2);//缺少"("
    space(section);
    fprintf(fout,"(\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束
    printf("%s %s\n",token,token1);
    es=expression(section,word,ID);//表达式1
    //expression多读一个
    if(es>0)
        return es;
    if(strcmp(token,";"))
        return (es=7);//缺少";"

    space(section);
    fprintf(fout,";\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束
    printf("%s %s\n",token,token1);
    es=expression(section,word,ID);//表达式2
    //expression多读一个
    if(es>0)
        return es;

    if(strcmp(token,";"))
        return (es=7);//缺少";"
    space(section);
    fprintf(fout,";\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束
    printf("%s %s\n",token,token1);

    es=expression(section,word,ID);//表达式3
    //expression多读一个
    if(es>0)
        return es;
    if(strcmp(token,")"))
        return (es=3);//缺少“)”
    space(section);
    fprintf(fout,")\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束
    printf("%s %s\n",token,token1);
    es=statement(section,word,ID);
    return es;
}
//附加功能
//12.<do_while_stat>::=do'{'<statement_list>'}'while'('<expression>')'
//<do_while语句>→do'{'<语句序列>'}'while'('<表达式>')'
int do_while_stat(int section,char word[MAX][MAX],char*ID){
    int es=0;
    space(section++);
    fprintf(fout,"<do_while>\n");
    space(section);
    fprintf(fout,"do\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束
    printf("%s %s\n",token,token1);
    if(strcmp(token,"{"))
        return (es=5);//缺少'{'
    space(section);
    fprintf(fout,"{\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束
    printf("%s %s\n",token,token1);

    //do中的语句
    es=statement_list(section,word,ID);
    //statement()多读一个

    if(es>0)
        return es;
    if(strcmp(token,"}"))
        return (es=6);//缺少'}'
    space(section);
    fprintf(fout,"}\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束
    printf("%s %s\n",token,token1);
    //接下来读while
    if(strcmp(token,"while"))
        return (es=8);//缺少while
    space(section+1);
    fprintf(fout,"while\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束
    printf("%s %s\n",token,token1);

    if(strcmp(token,"("))
        return (es=2);//缺少“(”
    space(section);
    fprintf(fout,"(\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束
    printf("%s %s\n",token,token1);
    es=expression(section,word,ID);
    //statement结束多读一个
    if(es>0)
        return es;

    if(strcmp(token,")"))
        return (es=3);//缺少“)”
    space(section);
    fprintf(fout,")\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束
    printf("%s %s\n",token,token1);

    if(strcmp(token,";"))
        return (es=7);//缺分号
    space(section);
    fprintf(fout,";\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束
    printf("%s %s\n",token,token1);
    return es;
}
//13.<write_stat>::=write<expression>;
//<write语句>::=write<表达式>;
int write_stat(int section,char word[MAX][MAX],char*ID){
    int es=0;
    space(section++);
    fprintf(fout,"<write_stat>\n");
    space(section);
    fprintf(fout,"write\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束
    printf("%s %s\n",token,token1);

    es=expression(section,word,ID);
    if(es>0)
        return es;

    if(strcmp(token,";"))
        return (es=7);//缺分号
    space(section);
    fprintf(fout,";\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束
    printf("%s %s\n",token,token1);
    return es;
}
//14.<read_stat>::=read ID;
//<read语句>::=read ID;
int read_stat(int section,char word[MAX][MAX],char*ID){
    int es=0;
    int i=0;
    space(section++);
    fprintf(fout,"<read_stat>\n");
    space(section);

    fprintf(fout,"read\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束
    printf("%s %s\n",token,token1);

    if(strcmp(token,"ID"))
        return (es=1);//缺少标识符
    while(i<MAX){
        if(strcmp(word[i],token1)==0||strcmp(WORD[i],token1)==0||strcmp(ID,token1)==0)
            break;
        i++;
    }
    if(i==MAX)
        return(es=11);//变量未声明就调用

    space(section);
    fprintf(fout,"ID\n");
    space(section+1);
    fprintf(fout,"%s\n",token1);
    fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束
    printf("%s %s\n",token,token1);

    if(strcmp(token,";"))
        return (es=7);//缺分号
    space(section);
    fprintf(fout,";\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束
    printf("%s %s\n",token,token1);
    return es;
}
//15.<compound_stat>::='{'<statement_list>'}'    if else while for等可能会使用复合语句
//<复合语句>→'{'<语句序列>'}'
int compound_stat(int section,char word[MAX][MAX],char*ID){
    int es=0;
    space(section++);
    fprintf(fout,"<compound_stat>\n");
    space(section);
    fprintf(fout,"{\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束
    printf("%s %s\n",token,token1);

    es=statement_list(section,word,ID);//语句序列 复合语句中是语句序列
    if(es>0)
        return es;
    if(strcmp(token,"}"))
        return(es=6);
    space(section);
    fprintf(fout,"}\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束
    printf("%s %s\n",token,token1);
    //会多读一个字符
    return es;
}
//16.<expression_stat>::=<expression>;|;
//<表达式语句>→<表达式>;|;
int expression_stat(int section,char word[MAX][MAX],char*ID){
    int es=0;
    space(section++);
    fprintf(fout,"<expression_stat>\n");
    //如果语句是空语句，即只是一个分号
    if(strcmp(token,";")==0){
        space(section);
        fprintf(fout,";\n");
        fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束
        printf("%s %s\n",token,token1);
        return es;
    }

    es=expression(section,word,ID);//语句不空时
    //expression多读一个
    if(es>0)
        return es;
    if(strcmp(token,";"))
        return (es=7);//缺少分号
    space(section);
    fprintf(fout,";\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束
    printf("%s %s\n",token,token1);
    return es;
}
//17.<call_stat>::=call ID'('[NUM|ID]')'  ';'
//<call语句>→call ID'('[NUM]|ID')'  ';'

int call_stat(int section,char word[MAX][MAX],char*ID){
    int es=0;
    int i=0;//用来判断变量是否声明时所用的量值
    space(section++);
    fprintf(fout,"<call_stat>\n");
    space(section);
    fprintf(fout,"call\n");
    fscanf(fp,"%s%s\n",&token,&token1);//fscanf遇到空格和换行时结束
    printf("%s %s\n",token,token1);

    if(strcmp(token,"ID"))
        return (es=1);//缺少标识符
    space(section);
    fprintf(fout,"ID\n");
    space(section+1);
    fprintf(fout,"%s\n",token1);
    fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束
    printf("%s %s\n",token,token1);

    if(strcmp(token,"("))
        return (es=2);//缺少"("
    space(section);
    fprintf(fout,"(\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束
    printf("%s %s\n",token,token1);
    if(strcmp(token,"NUM")==0||strcmp(token,"ID")==0){//调用的函数有参数，以int型数字或者已声明的变量 token是类型值，token1是属性值
        if(strcmp(token,"ID")==0){
            while(i<MAX){
                if(strcmp(word[i],token1)==0||strcmp(WORD[i],token1)==0||strcmp(ID,token1)==0)
                    break;
                i++;
            }
           if(i==MAX)
                return(es=11);//变量未声明就调用
            space(section);
            fprintf(fout,"ID\n");
            space(section+1);
            fprintf(fout,"%s\n",token1);//输出其参数
        }
        else{
            space(section);
            fprintf(fout,"NUM\n");
            space(section+1);
            fprintf(fout,"%s\n",token1);
        }
        fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束
        printf("%s %s\n",token,token1);
    }

    if(strcmp(token,")"))
        return (es=3);//缺少")"
    space(section);
    fprintf(fout,")\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束  此处读取的是;
    printf("%s %s\n",token,token1);//输出
    if(strcmp(token,";"))
        return (es=7);//缺分号
    space(section);
    fprintf(fout,";\n");
    printf("*****************");
    fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束
    printf("%s %s\n",token,token1);
    return es;
}
//18.<break_stat>→break';'
//<break语句>→break';'
int break_stat(int section){
    int es=0;
    space(section++);
    fprintf(fout,"<break_stat>\n");
    space(section);
    fprintf(fout,"break\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束
    printf("%s %s\n",token,token1);
    if(strcmp(token,";"))
        return (es=7);//缺分号
    space(section);
    fprintf(fout,";\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束
    printf("%s %s\n",token,token1);
    return es;
}
//19.<continue_stat>→continue';'
//<continue语句>→continue;
int continue_stat(int section){
    int es=0;
    space(section++);
    fprintf(fout,"<continue_stat>\n");
    space(section);
    fprintf(fout,"continue\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束
    printf("%s %s\n",token,token1);

    if(strcmp(token,";"))
        return (es=7);//缺分号
    space(section);
    fprintf(fout,";\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束
    printf("%s %s\n",token,token1);
    return es;
}
//20.<expression>::= ID=<bool_expr>|<bool_expr>
//由于前项和后项的first集可能有重复的"ID"，所以要进行判断
//<表达式>→ID=<布尔表达式>|<布尔表达式>
int expression(int section,char word[MAX][MAX],char *ID){
    int es=0,fileadd;
    int i=0;
    space(section++);
    fprintf(fout,"<expression>\n");
    char token2[20],token3[40];
    if(strcmp(token,"ID")==0){//如果表达式是以ID开始
        fileadd=ftell(fp);//记录当前文件的位置，方便之后的返回
        while(i<MAX){//判断变量是否声明
                if(strcmp(word[i],token1)==0||strcmp(WORD[i],token1)==0||strcmp(ID,token1)==0)
                    break;
                i++;
            }
        if(i==MAX)
            return(es=11);//变量未声明就调用
        fscanf(fp,"%s%s\n",&token2,&token3);//fscanf遇到空格和换行时结束
        if(strcmp(token2,"=")==0){//如果读入了=，则是 ID=<布尔表达式>
            space(section);
            fprintf(fout,"ID\n");
            space(section+1);
            fprintf(fout,"%s\n",token1);
            printf("%s %s\n",token2,token3);
            space(section);
            fprintf(fout,"=\n");
            //继续向下读
            fscanf(fp,"%s%s\n",&token,&token1);//fscanf遇到空格和换行时结束
            printf("%s %s\n",token,token1);
            es=bool_expr(section,word,ID);
            if(es>0)
                return es;
        }
        else{//如果读到的不是=，那么应该直接是
            fseek(fp,fileadd,0);//如果不是"="的话，将文件退回到记录位置
			//fseek函数用法 :  int fseek(FILE *stream, long offset, int fromwhere);函数设置文件指针stream的位置。
            //printf("%s %s\n",token,token1);
            es=bool_expr(section,word,ID);//继续向下读
            if(es>0)
                return es;
        }
    }
    else//表达式不是ID开始 直接匹配到 <布尔表达式>
        es=bool_expr(section,word,ID);
    return es;
}
//21.<bool_expr>::=<additive_expr>|<additive_expr> '(' > | < | >= | <= | == | != | && | || | ! ')' <additive_expr>
//<布尔表达式>→<算数表达式>|<算法表达式(>|<|>=|<=|==|!=|&&||||!)<算数表达式>
//扩充功能：逻辑运算符&& || ！
int bool_expr(int section,char word[MAX][MAX],char*ID){
    int es=0;
    space(section++);
    fprintf(fout,"<bool_expr>\n");
    es=additive_expr(section,word,ID);
    //多读一个
    if(es>0)
        return es;
    if(strcmp(token,">")==0||strcmp(token,"<")==0||strcmp(token,">=")==0||strcmp(token,"<=")==0||strcmp(token,"==")==0||strcmp(token,"!=")==0||strcmp(token,"&&")==0||strcmp(token,"||")==0||strcmp(token,"!")==0){
        space(section);
        fprintf(fout,"%s\n",token1);//输出运算符
        fscanf(fp,"%s%s\n",&token,&token1);//fscanf遇到空格和换行时结束
        printf("%s %s\n",token,token1);
        es=additive_expr(section,word,ID);
        if(es>0)
            return es;
    }
    return es;
}
//22.<additive_expr>::=<term>{(+|-)< term >}
//<算数表达式>→<项>{(+|-)<项>}
int additive_expr(int section,char word[MAX][MAX],char*ID){
    int es=0;
    space(section++);
    fprintf(fout,"<additive_expr>\n");
    es=term(section,word,ID);
    //term 多读一个字符
    if(es>0)
        return es;
    while(strcmp(token,"+")==0||strcmp(token,"-")==0){//处理后续表达式
        space(section);
        fprintf(fout,"%s\n",token1);
        fscanf(fp,"%s%s\n",&token,&token1);//fscanf遇到空格和换行时结束
        printf("%s %s\n",token,token1);
        es=term(section,word,ID);
        if(es>0)
            return es;
    }
    return es;
}
//23.<term>::=<factor>{(*|/)< factor >}
//<项>→<因子>{(*|/)<因子>}
int term(int section,char word[MAX][MAX],char*ID){
     int es=0;
     space(section++);
     fprintf(fout,"<term>\n");
     es=factor(section,word,ID);
     //factor多读一个
     if(es>0)
        return es;
     while(strcmp(token,"*")==0||strcmp(token,"/")==0){
        space(section);
        fprintf(fout,"%s\n",token1);
        fscanf(fp,"%s%s\n",&token,&token1);//fscanf遇到空格和换行时结束
        printf("%s %s\n",token,token1);
        es=factor(section,word,ID);
        if(es>0)
            return es;
    }
    return es;
}
//24.<factor>::='('<expression>')'|ID|NUM
//<因子>→'('<算数表达式>')'|ID|NUM
int factor(int section,char word[MAX][MAX],char*ID){
    int es=0;
    int i=0;
    space(section++);
    fprintf(fout,"<factor>\n");
    if(strcmp(token,"(")==0){//如果是算术表达式
        space(section);
        fprintf(fout,"(\n");
        fscanf(fp,"%s%s\n",&token,&token1);//fscanf遇到空格和换行时结束
        printf("%s %s\n",token,token1);

        es=expression(section,word,ID);//多读
        if(es>0)
            return es;

        if(strcmp(token,")"))
            return (es=3);//缺少右括号
        space(section);
        fprintf(fout,")\n");
        fscanf(fp,"%s%s\n",&token,&token1);//fscanf遇到空格和换行时结束
        printf("%s %s\n",token,token1);
    }
    else{//是标识符或者数字
        if(strcmp(token,"ID")==0||strcmp(token,"NUM")==0){
            if(strcmp(token,"ID")==0){//如果是标识符
            while(i<MAX){
                if(strcmp(word[i],token1)==0||strcmp(WORD[i],token1)==0||strcmp(ID,token1)==0)
                    break;
                i++;
            }
            if(i==MAX)
                return(es=11);//变量未声明就调用
            }
            space(section);
            fprintf(fout,"%s\n",token1);
            fscanf(fp,"%s%s\n",&token,&token1);//fscanf遇到空格和换行时结束
            printf("%s %s\n",token,token1);
            return es;
        }
        else//不是标识符 不是数字 不是表达式  语句缺操作数
            return(es=9);//缺少操作数，匹配不到语法
    }
    return es;
}
//二十五:<switch_case>::= <switch_stat> '(' factor ')' '{' case_list'}'
int switch_stat(int section,char word[MAX][MAX],char*ID)
{
	int es=0;
    space(section++);
    fprintf(fout,"<switch_stat>\n");
    space(section);
    fprintf(fout,"switch\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束
    printf("%s %s\n",token,token1);
    if(strcmp(token,"("))
        return (es=2);//缺少"("
    space(section);
    fprintf(fout,"(\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束
    printf("%s %s\n",token,token1);

    es=factor(section,word,ID);//switch中的表达式
    //factor多读一个
    if(es>0)
        return es;
    if(strcmp(token,")"))
        return (es=3);//缺少")"
    space(section);
    fprintf(fout,")\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束
    printf("%s %s\n",token,token1);

    if(strcmp(token,"{"))
        return (es=5);//缺少'{'
    space(section);
    fprintf(fout,"{\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束
    printf("%s %s\n",token,token1);
    if(strcmp(token,"case")==0)//如果读入的是case
   {
    es=case_list(section,word,ID);
    //case_list()多读一个
    if(es>0)
        return es;
    }
    else
    return (es=16);//如果读入的不是case

    if(strcmp(token,"}"))
        return (es=6);//缺少'}'
    space(section);
    fprintf(fout,"}\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束
    printf("%s %s\n",token,token1);
    return es;
}

//case序列 ::= case <factor> : {<expression>} break;
int case_list(int section,char word[MAX][MAX],char*ID)
{
	int es=0;
    space(section++);
    fprintf(fout,"<case_stat>\n");
    space(section);
    fprintf(fout,"case\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束
    printf("%s %s\n",token,token1);

    es=factor(section,word,ID);//case选择的 某一语句
    //factor()多读一个
    if(es>0)//项出错
        return es;
    if(strcmp(token,":"))
        return (es=14);//缺少":"
    space(section);
    fprintf(fout,":\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束
    printf("%s %s\n",token,token1);
	if(strcmp(token,"break"))//有语句，不是单个的break
{
    es=expression(section,word,ID);//case中的语句
    //expression中多读一个
    if(es>0)
        return es;
    if(strcmp(token,";"))
        return (es=7);//缺少;
    space(section);
	fprintf(fout,";\n");

	fscanf(fp,"%s%s\n",token,token1);//fscanf遇到空格和换行时结束
    printf("%s %s\n",token,token1);
	es=break_stat(section);
    if(es>0)
    return (es=15);
}
	else//直接是一个break的情况
	{
	es=break_stat(section);
	if(es>0)
    return (es=15);
	}

    //break_stat中多读一个
	if(strcmp(token,"case")==0)//看后续有无case
		case_list(section-1,word,ID);//之后的case要与之前的对齐
    return es;
}
int  main(){
     system("color f0\n");
//先开始词法分析	并且将词法分析的输出文件作为语法分析的输入文件
	int result=0;
	printf("温钧雄的程序\n");
	result=TESTscan();//接受返回值，判断是否分析成功
    if(result=0)
    {printf("\n词法分析完成");}
    int es;
    es=TESTparse();
    if(es>0)
        printf("语法分析错误！\n");
    else
        printf("语法分析成功！\n");
    printf("温钧雄的程序\n");
    return es;
}
