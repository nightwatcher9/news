 #include<stdio.h>
 #include<string.h>
 #define KEY_WORD_COUNT 8
 char *KEY_WORD [KEY_WORD_COUNT]={"if","else","for","while","do","int","read","write"};
 char SINGLE_WORD[]="+-*(){}:,;";//除号在于注释一起处理
 char FIRST_WORD[]="><=!";

 //FILE *scanMidleFile;
 char WORD[50];//保存单词符号
 char WORD_TYPE[20];//单词类别
 int WORD_INDEX=-1;
 char SCAN_IN;//扫描源代码输入的字符

void getIdentifier(FILE *fIn);//获取indentifier
int  getNumber(FILE *fIn);//获取数字
void getSingleWord(FILE *fIn);// 获取单分界符。可能是双分界符的第一个字符的放在getDoubleWord中处理
void getDoubleWord(FILE *fIn);//获取双分界符
int  dealComment(FILE *fIn);//处理分界符“/"。有可能得到的是除号


 int TESTscan(FILE *fIn)
 {
  int error=1;
  SCAN_IN=getc(fIn);

  while(SCAN_IN!=EOF)
  {
  while(' '==SCAN_IN||'\t'==SCAN_IN||'\n'==SCAN_IN)
  SCAN_IN=getc(fIn);
  if(EOF==SCAN_IN)
  break;
  if(isalpha(SCAN_IN))//如果输入的是字母
  getIdentifier(fIn);//
  else if(isdigit(SCAN_IN))//如果输入的是数字
  error=getNumber(fIn);//
  else if(strchr(SINGLE_WORD,SCAN_IN)>0)//如果输入的是单分界符
  getSingleWord(fIn);
  else if(strchr(FIRST_WORD,SCAN_IN))//如果输入“firstWord”
  getDoubleWord(fIn);
  else if('/'==SCAN_IN)
  error=dealComment(fIn);
  else
  error=0;

  if(error==1)
{
if(WORD_INDEX!=-1)
{
  printf("%s\t%s\n",WORD_TYPE,WORD);
  WORD_INDEX=-1;
}
  }
  else
  {
printf("errer!!!\n");
WORD_INDEX=0;
  return 1;
  }
  }
  return 0;
 }

void getIdentifier(FILE *fIn)//获取indentifier
{
int i;
WORD[++WORD_INDEX]=SCAN_IN;
while(isalnum(SCAN_IN=getc(fIn)))
WORD[++WORD_INDEX]=SCAN_IN;
WORD[++WORD_INDEX]='\0';
for(i=0;i<50;i++)
if(strcmp(KEY_WORD[i],WORD)==0)
break;
if(i)
strcpy(WORD_TYPE,KEY_WORD[i]);
else//是标识符
strcpy(WORD_TYPE,"ID");
}


int getNumber(FILE *fIn)//获取数字
{
WORD[++WORD_INDEX]=SCAN_IN;
while(isdigit(SCAN_IN=getc(fIn)))
WORD[++WORD_INDEX]=SCAN_IN;
if(isalpha(SCAN_IN))
return 0;
else
{
strcpy(WORD_TYPE,"NUM");
WORD[++WORD_INDEX]='\0';
}
return 1;
}


void getSingleWord(FILE *fIn)// 获取单分界符。可能是双分界符的第一个字符的放在getDoubleWord中处理
{
WORD_TYPE[0]=WORD[0]=SCAN_IN;
WORD_TYPE[1]=WORD[1]='\0';
SCAN_IN=getc(fIn);
WORD_INDEX++;
}



void getDoubleWord(FILE *fIn)//获取双分界符
{
WORD[0]=SCAN_IN;
SCAN_IN=getc(fIn);  //读下一个字符判断是否为双分界符
if ('='==SCAN_IN)  //如果是=，组合双分界符
{
WORD[1]=SCAN_IN;
WORD[2]='\0';  //组合双分界符结束
SCAN_IN=getc(fIn);  //读下一个符号以便识别下一个单词
strcpy(WORD_TYPE,WORD);
WORD_INDEX+=2;
     }
else//不是=则为单分界符'
{
WORD[1]='\0';
strcpy(WORD_TYPE,WORD);
WORD_INDEX++;
}
}



int dealComment(FILE *fIn)//处理分界符“/"。有可能得到的是除号
{
SCAN_IN=getc(fIn);  //读下一个字符
if (SCAN_IN=='*')  //如果是*，则开始处理注释
{
char ch1;
ch1=getc(fIn);  //读下一个字符
do
{
SCAN_IN=ch1;
ch1=getc(fIn);
}  //删除注释
while ((SCAN_IN!='*' || ch1!='/')&&ch1!=EOF);  //直到遇到注释结束符*/或文件尾
SCAN_IN=getc(fIn);//读下一个符号以便识别下一个单词
}
else  //不是*则处理单分界符/
{
WORD_TYPE[0]=WORD[0]='/';
WORD_TYPE[1]=WORD[1]='\0';
WORD_INDEX++;
}
return 1;
}

int main()
{

FILE *fIn;
FILE *fout;
if(NULL==(fIn=fopen("sourceCode.c","r")))
printf("%s\n","fairein");
TESTscan(fIn);
fclose(fIn);
}
