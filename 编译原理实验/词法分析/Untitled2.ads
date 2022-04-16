 #include<stdio.h>
 #include<string.h>
 #define KEY_WORD_COUNT 8
 char *KEY_WORD [KEY_WORD_COUNT]={"if","else","for","while","do","int","read","write"};
 char SINGLE_WORD[]="+-*(){}:,;";//��������ע��һ����
 char FIRST_WORD[]="><=!";

 //FILE *scanMidleFile;
 char WORD[50];//���浥�ʷ���
 char WORD_TYPE[20];//�������
 int WORD_INDEX=-1;
 char SCAN_IN;//ɨ��Դ����������ַ�

void getIdentifier(FILE *fIn);//��ȡindentifier
int  getNumber(FILE *fIn);//��ȡ����
void getSingleWord(FILE *fIn);// ��ȡ���ֽ����������˫�ֽ���ĵ�һ���ַ��ķ���getDoubleWord�д���
void getDoubleWord(FILE *fIn);//��ȡ˫�ֽ��
int  dealComment(FILE *fIn);//����ֽ����/"���п��ܵõ����ǳ���


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
  if(isalpha(SCAN_IN))//������������ĸ
  getIdentifier(fIn);//
  else if(isdigit(SCAN_IN))//��������������
  error=getNumber(fIn);//
  else if(strchr(SINGLE_WORD,SCAN_IN)>0)//���������ǵ��ֽ��
  getSingleWord(fIn);
  else if(strchr(FIRST_WORD,SCAN_IN))//������롰firstWord��
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

void getIdentifier(FILE *fIn)//��ȡindentifier
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
else//�Ǳ�ʶ��
strcpy(WORD_TYPE,"ID");
}


int getNumber(FILE *fIn)//��ȡ����
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


void getSingleWord(FILE *fIn)// ��ȡ���ֽ����������˫�ֽ���ĵ�һ���ַ��ķ���getDoubleWord�д���
{
WORD_TYPE[0]=WORD[0]=SCAN_IN;
WORD_TYPE[1]=WORD[1]='\0';
SCAN_IN=getc(fIn);
WORD_INDEX++;
}



void getDoubleWord(FILE *fIn)//��ȡ˫�ֽ��
{
WORD[0]=SCAN_IN;
SCAN_IN=getc(fIn);  //����һ���ַ��ж��Ƿ�Ϊ˫�ֽ��
if ('='==SCAN_IN)  //�����=�����˫�ֽ��
{
WORD[1]=SCAN_IN;
WORD[2]='\0';  //���˫�ֽ������
SCAN_IN=getc(fIn);  //����һ�������Ա�ʶ����һ������
strcpy(WORD_TYPE,WORD);
WORD_INDEX+=2;
     }
else//����=��Ϊ���ֽ��'
{
WORD[1]='\0';
strcpy(WORD_TYPE,WORD);
WORD_INDEX++;
}
}



int dealComment(FILE *fIn)//����ֽ����/"���п��ܵõ����ǳ���
{
SCAN_IN=getc(fIn);  //����һ���ַ�
if (SCAN_IN=='*')  //�����*����ʼ����ע��
{
char ch1;
ch1=getc(fIn);  //����һ���ַ�
do
{
SCAN_IN=ch1;
ch1=getc(fIn);
}  //ɾ��ע��
while ((SCAN_IN!='*' || ch1!='/')&&ch1!=EOF);  //ֱ������ע�ͽ�����*/���ļ�β
SCAN_IN=getc(fIn);//����һ�������Ա�ʶ����һ������
}
else  //����*�����ֽ��/
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
