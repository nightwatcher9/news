
//词法分析
#include<stdio.h>
#include<ctype.h>
#include<string.h>
//保留字数目与保留字数组
#define keywordSum 8
char *keyword[keywordSum] = {"if","else","for","while","read","write","do","int"};
char singleword[50] = "+-*(){};,:";//纯单分界符
char doubleword[10] = "<>=!";//双分界符首字符
extern char Scanin[300],Scanout[300];//用于接收输入输出文件名
extern FILE *fin,*fout;//用于指向输入输出文件的指针
extern int TESTscan();
char Scanin[300],Scanout[300];
FILE *fin, *fout;


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
void main()
{
  int es=0;
  es=TESTscan();
  if(es>0)printf('词法分析出错');
  else printf('词法分析成功');
}
