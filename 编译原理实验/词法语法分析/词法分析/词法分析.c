
//�ʷ�����
#include<stdio.h>
#include<ctype.h>
#include<string.h>
//��������Ŀ�뱣��������
#define keywordSum 8
char *keyword[keywordSum] = {"if","else","for","while","read","write","do","int"};
char singleword[50] = "+-*(){};,:";//�����ֽ��
char doubleword[10] = "<>=!";//˫�ֽ�����ַ�
extern char Scanin[300],Scanout[300];//���ڽ�����������ļ���
extern FILE *fin,*fout;//����ָ����������ļ���ָ��
extern int TESTscan();
char Scanin[300],Scanout[300];
FILE *fin, *fout;


//���ڶԱ������������ð����������Ϊ�۰������׼����
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



//���ڲ��ұ����ֱ���۰���Һ����������ֲ����ִ�Сд��
int Search_Bin(char *KW[],char *keyword){

	sort(KW);

	int low=0,high=keywordSum-1;

	int mid;

	while(low<=high){

		mid = (low+high)/2;

		if(stricmp(keyword,KW[mid])==0) return 1;		//stricmp�Ƚϲ����ִ�Сд ����1��ʾ���ҵ�

		else if(stricmp(keyword,KW[mid])>0) low=mid+1;

		else high=mid-1;

	}

	return 0;											//����0��ʾ����ʧ��

}



int TESTscan(){

	char ch,token[40];									//ch���ڱ��浱ǰ�������ַ���token���ڱ���ʶ����ĵ���

	int es=0,j,n;										//esΪ����ʶ����룬0��ʾû�д���

	int linenum=1;										//���ڱ����к�

	printf("������Դ�����ļ���������·������");

	scanf("%s",Scanin);

	printf("������ʷ���������ļ���������·������");

	scanf("%s",Scanout);

	if((fin = fopen(Scanin,"r"))==NULL){

		printf("\n�򿪴ʷ����������ļ�����\n");

		return 1;										//�����ļ������ش������1

	}

	if((fout = fopen(Scanout,"w"))==NULL){

		printf("\n�򿪴ʷ�����1����ļ�����\n");

		return 2; 										//����ļ������ش������2

	}

	ch = getc(fin);

	while(ch!=EOF){

		while(ch==' '||ch=='\n'||ch=='\t'){

			if(ch=='\n')								//��¼�к�

				linenum++;

			ch=getc(fin);

		}

		if(isalpha(ch)){								//���ch����ĸ�Ļ������б�ʶ������

			token[0]=ch;

			j=1;

			ch=getc(fin);

			while(isalnum(ch)){							//���ch����ĸ�������ֵĻ�

				token[j++]=ch;							//��ϵı�ʶ��������token��

				ch=getc(fin);							//����һ���ַ�

			}

			token[j]='\0';								//��ʶ����Ͻ���

			//�鱣����

			n=Search_Bin(keyword,token);

			if(n==1)									//�Ǳ�����
       {      if( token>='A' && token<='Z')
                {
                    printf("%s\t%s\n",token+32,token+32);
				fprintf(fout,"%s\t%s\n",token+32,token+32);
                }
                printf("%s\t%s\n",token,token);
				fprintf(fout,"%s\t%s\n",token,token);}

			else

				{printf("%s\t%s\n","ID",token);
				fprintf(fout,"%s\t%s\n","ID",token);}	//���Ǳ�����

		}

		else if(isdigit(ch)){							//���ch�����ֵĻ��������ֽ��д���

			token[0]=ch;

			j=1;

			ch=getc(fin);

			while(isdigit(ch)){							//��������������������������˳�

				token[j++]=ch;

				ch=getc(fin);

			}

			token[j]='\0';

			printf("%s\t%s\n","NUM",token);
			fprintf(fout,"%s\t%s\n","NUM",token);

		}

		else if(strchr(singleword,ch)!=NULL){			//strchr���ڲ���ĳ�ַ��Ƿ������ĳ�ַ������У����򷵻�ָ�룬�����򷵻�NULL

			token[0]=ch;

			token[1]='\0';

			ch=getc(fin);								//����һ�������Ա�ʶ�𵥴�

			printf("%s\t%s\n",token,token);
			fprintf(fout,"%s\t%s\n",token,token);

		}

		else if(strchr(doubleword,ch)!=NULL){

			token[0]=ch;

			ch=getc(fin);								//����һ���ַ��ж��Ƿ���˫�ֽ��

			if((token[0]!='&'&&token[0]!='|'&&ch=='=')||(token[0]=='|'&&ch=='|')||(token[0]=='&'&&ch=='&')){				//�����=��|��&�����˫�ֽ��

				token[1]=ch;

				token[2]='\0';

				ch=getc(fin);

			}

			else{										//����Ϊ���ֽ��

				token[1]='\0';

			}

			if(token[0]=='!'||token[0]=='<'||token[0]=='>'||token[0]=='='){

				printf("%s\t%s\n",token,token);
				fprintf(fout,"%s\t%s\n",token,token);

			}

			else{

				printf("%d�з�������",linenum);
				printf("\n%s\t%s\n","ERROR",token);
				fprintf(fout,"\n%s\t%s\n","ERROR",token);

				fprintf(fout,"%s  %d\n\n","�����к�Ϊ��",linenum);

			}

		}

		else if(ch=='/'){								//ע�ʹ���

			ch=getc(fin);

			if(ch=='*'){								//�����һ���ַ���*��ʼ����ע�ʹ���

				char ch1;

				ch1=getc(fin);

				do{

					if(ch1=='\n'){

						linenum++;

					}

					ch=ch1;

					ch1=getc(fin);

				}while((ch!='*'||ch1!='/')&&ch1!=EOF);	//ɾ��ע��

				ch=getc(fin);

			}

			else{										//����*��������ֽ��

				token[0]='/';

				token[1]='\0';

				printf("%s\t%s\n",token,token);
				fprintf(fout,"%s\t%s\n",token,token);

			}

		}

		else{

			token[0]=ch;								//�������

			token[1]='\0';

			ch=getc(fin);

			es=3;										//���ô������

			printf("%d�з�������",linenum);
			printf("\n%s\t%s\n","ERROR",token);

			fprintf(fout,"\n%s\t%s\n","ERROR",token);

			fprintf(fout,"%s  %d\n\n","�����к�Ϊ��",linenum);

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
  if(es>0)printf('�ʷ���������');
  else printf('�ʷ������ɹ�');
}
