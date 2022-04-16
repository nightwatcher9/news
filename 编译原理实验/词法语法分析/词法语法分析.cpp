#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include <string.h>
#include<stdlib.h>
using namespace std;
#define MAX 200
#define keywordSum 11
char *keyword[keywordSum] = {"if","else","for","while","read","write","do","int","function","switch","case"};
//�����ֽ�����Ķ���
char singleword[50] = { '+','-','*','(',')','{','}',',',';',':' ,'.'};
//˫�ֽ��������ĸ
char doubleword[10] = { '>','<','=','!' };
int Current=0;//����ͳ��ȫ�ֱ����ĸ���
char token[20],token1[40];
char scanin[300],scanout[300];//�ʷ��������롢����ļ���
char Scanin[300],Scanout[300];//ǰ�߱�ʾ�﷨�����ļ���·�������߱�ʾ�﷨������ļ���·��
char WORD[MAX][MAX];//�����洢ȫ�ֱ���
FILE *fin, *fout,*fp,*fr;
int end=0;//�ж��Ƿ�����﷨������main�л��޸ĸ�ֵ
//��������
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
int case_list(int section,char word[MAX][MAX],char*ID);//case����

//�ʷ���������
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
	scanf("%s",scanin);

  printf("������ʷ���������ļ���������·������");
	scanf("%s",scanout);

	if((fin = fopen(scanin,"r"))==NULL){

		printf("\n�򿪴ʷ����������ļ�����\n");

		return 1;										//�����ļ������ش������1

	}

	if((fout = fopen(scanout,"w"))==NULL){

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
       {      /*if( token>='A' && token<='Z')
                {
                    printf("%s\t%s\n",token+32,token+32);
				fprintf(fout,"%s\t%s\n",token+32,token+32);
                }*/
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
  //  printf("����һ���ܲ��ܷ���");
	return (es);

}














//�����﷨���пո�����ĺ���
void space(int section){
    for(int i=0;i<section;i++)
        fprintf(fout,"    ");
}
//�﷨��������
int TESTparse(){
    int es=0;
    fp=fopen(scanout,"r");//�Դʷ�����������ļ���Ϊ����
    printf("\n�������﷨������ļ���·��:\n");
    scanf("%s",Scanout);
    if((fout=fopen(Scanout,"w"))==NULL){
        es=13;//�� ����﷨�����ļ��������
    }
    if(es==0)//��ȷ�����ļ���
        es=program();//���з���
    printf("-------�﷨�������---------\n");
    switch(es){
        case 0:
            printf("�﷨����������δ���ִ���\n");
            break;
        case 1:
            printf("ȱ�ٱ�ʶ��ID��\n");
            break;
        case 2:
            printf("ȱ��'('\n");
            break;
        case 3:
            printf("ȱ��')'\n");
            break;
        case 4:
            printf("ȱ��main����\n");
            break;
        case 5:
            printf("ȱ��'{'\n");
            break;
        case 6:
            printf("ȱ��'}'\n");
            break;
        case 7:
            printf("ȱ�ٷֺ�\n");
            break;
        case 8:
            printf("do while�����ȱ��'while'\n");
            break;
        case 9:
            printf("ȱ�ٲ�����!\n");
            break;
        case 10:
            printf("�����ظ�����!\n");
            break;
        case 11:
            printf("��������ǰδ����!\n");
            break;
        case 12:
            printf("\n���ļ�%s����!\n",scanout);//�ʷ���������ļ����﷨����������
            break;
        case 13:
            printf("\n�����﷨������ļ�%sʱ����!",Scanout);
            break;
        case 14:
        	printf("ȱ��':' \n");
        	break;
        case 15:
        	printf("switch�����ȱ��break!\n");
        	break;
        case 16:
			printf("switch�����û��case!\n");
			break;
		case 17:
			printf("������������ʱȱ��,\n");
			break;
		case 18:
			printf("main����ȱ�� } !\n");
			break;
    }
    fclose(fp);
    fclose(fout);
    return es;
}
//һ��<program> ��<declaration_list>{ fun_declaration }<main_declaration>
//<����>��<��������>{����}<������>
//���ӹ��ܣ�ȫ�ֱ���������
int program(){
    int es=0;
    char *ID;
    int section=0;//���﷨��ʱ����ͳ�ƿո������
    space(section++);//�����section=1
    fprintf(fout,"<program>\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո����ʱ�����
    printf("%s %s\n",token,token1);
    es=declaration_list(section,Current,WORD);//ȫ�ֱ����������� section=1
    //declaration_list���һ��

    if(es>0)//������ִ����򷵻�
        return es;
    while(strcmp(token,"function")==0){//������ʶ���к����Ķ���
        es=fun_declaration(section);//section=1
        if(es>0)
            return es;
            //error �����
        //fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����
        //printf("%s %s\n",token,token1);
    }
    es=main_declaration(section);//main�����Ķ���  section=1
    return es;
}

//����<fun_declaration> �� function [int]ID'(' [int ID] ')' <function_body>
//<����>��functionID'('[int ID]')'<������>
// ͨ�׽��ͣ�function [int] ������([int ������]) ������
int fun_declaration(int section){
    int es=0;
    char *ID;//�洢��������
    space(section++);//ִ�к�section=2
    fprintf(fout,"<fun_declaration>\n");
    space(section);//section=2
    fprintf(fout,"function\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����
    printf("%s %s\n",token,token1);
    if(strcmp(token,"int")==0){//������int�͵ķ��ز���
        space(section);//section=2
        fprintf(fout,"int\n");
        fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����
        printf("%s %s\n",token,token1);
    }
    if(strcmp(token,"ID"))//�жϺ������Ƿ�Ϸ�
        return (es=1);//���Ǳ�ʶ������1
    space(section);//section=2
    fprintf(fout,"ID\n");
    space(section+1);//section=2
    fprintf(fout,"%s\n",token1);//�����ʶ��(������)
    fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����
    printf("%s %s\n",token,token1);
    if(strcmp(token,"("))
        return (es=2);//ȱ��"("����2
    space(section);//section=2
    fprintf(fout,"(\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����
    printf("%s %s\n",token,token1);

    //����Ƿ��в���
    if(strcmp(token,"int")==0){//int�ؼ���ƥ��ɹ�
        space(section);//section=2
        fprintf(fout,"int\n");
        fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����
        printf("%s %s\n",token,token1);
        if(strcmp(token,"ID"))//�鿴�����Ƿ�Ϊ�Ϸ���ʶ��
            return (es=1);//���Ǳ�ʶ������1
        strcpy(ID,token1);//��������¼��ID��

        space(section);//section=2
        fprintf(fout,"ID\n");
        space(section+1);//section=2
        fprintf(fout,"%s\n",token1);//��������еı�ʶ��
        fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����
        printf("%s %s\n",token,token1);
    }
    if(strcmp(token,")"))
        return(es=3);//ȱ��")"����3
    space(section);//section=2
    fprintf(fout,")\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����
    printf("%s %s\n",token,token1);

    //��֤ÿ������󣬶�������һ�У����뺯��ֱ�ӽ���������жϵȲ���
    es=function_body(section,ID);//���뺯����Ķ���
    return es;
}
//����<main_declaration>::=main'('')'<function_body>
//<������>��main'('')'<������>
//ͨ�׽��ͣ��� main() ������
int main_declaration(int section){
    int es=0;
    char *ID;
    space(section++);//ִ�к�seciton=2
    fprintf(fout,"<main_declaration>\n");
    if(strcmp(token1,"main"))
        return (es=4);//û��"main" ����
    space(section);//section=2
    fprintf(fout,"main\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����
    printf("%s %s\n",token,token1);

    if(strcmp(token,"("))
        return (es=2);//ȱ��"("����2
    space(section);//section=2
    fprintf(fout,"(\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����
    printf("%s %s\n",token,token1);
    if(strcmp(token,")"))
        return(es=3);//ȱ��")" ����3

    space(section);//section=2
    fprintf(fout,")\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����
    printf("%s %s\n",token,token1);

    //��֤ÿ������󣬶�������һ�У����뺯��ֱ�ӽ���������жϵȲ���

    end=1;//������main���﷨������main������function����з����ģ��������Ϊ��ֹ
    es=function_body(section,ID);//���뺯����Ķ��� section=2
    return es;
}
//�ġ�<function_body>::='{'<declaration_list><statement_list>'}'
//<������>��'{'<��������><�������>'}'
//ͨ�׽���: function_body{declaration_list statement_list }
//�������е����ݣ� �������� �������
int function_body(int section,char *ID){//ID�Ǻ����Ĳ��� section=2
    int es=0;
    int current=0;//ȫ�ֱ�������
    char word[MAX][MAX];//��¼ȫ�ֱ���  һ�������ڿ�������20�����ȵ���20�ı���
    space(section++);//ִ�к�section=3
    fprintf(fout,"<function_body>\n");
    if(strcmp(token,"{"))
        return (es=5);//ȱ��"{"

    space(section);//section=3
    fprintf(fout,"{\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����
    printf("%s %s\n",token,token1);

    //�ڽ��������Ͷ���֮ǰ���Ѿ���������һ�ַ���ֵ��token�ˣ����Խ��뺯����ֱ����������űȽ�

    es=declaration_list(section,current,word);//���뺯�����е��������֣��������У�section=3
    //declation_list���
    if(es>0)//�������ֳ���
        return es;

    es=statement_list(section,word,ID);//���뺯�����еĶ��岿�� ���������У�section=3
    //statement_list���
    if(es>0)//���岿�ֳ���
        return es;

    if((strcmp(token,"}"))&&(end==1))
        return (es=17);//mainȱ��"}"����17
    else if(strcmp(token,"}")&&(end==0))
    	return (es=6);//ȱ��}������6
    space(section);
//	printf("%s %s\n",token,token1);
    fprintf(fout,"}\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����
  //  if()
    return es;
}
//�塢<declaration_list>::={<declaration_stat>}
//<��������>��{�������}

int declaration_list(int section,int &current,char word[MAX][MAX]){//�����Ѿ��������ַ���token������ֱ������ͱȽ� section=3
    int es=0;
    space(section++);//ִ�к�section=4
    fprintf(fout,"<declaration_list>\n");
    while(strcmp(token,"int")==0){//�����int�͵�����
        es=declaration_stat(section,current,word);//����������� section=4
        if(es>0)
            return es;
    }
    return es;
}
//����<declaration_stat>::=int ID{,ID};
//<�������>��int ID{,ID};
int declaration_stat(int section,int &current,char word[MAX][MAX]){
    int es=0;
    int i=0;//�����������Ƿ��ظ�
    space(section++);
    fprintf(fout,"<declaration_stat>\n");
    space(section);
    fprintf(fout,"int\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����
    printf("%s %s\n",token,token1);

    while(strcmp(token,";")!=0)//û����;ʱ
	{
    if(strcmp(token,"ID"))
        return (es=1);//���Ǳ�ʶ������1
    while(i<current){//�ж��Ƿ���ȫ�ֱ�����ͻ
        if(strcmp(token1,word[i])==0)//�鿴��ǰ��������ı����Ƿ��ȫ��������ͻ
           return (es=10);//�����ظ�����
        i++;
    }
    strcpy(word[current++],token1);//�µı������뵽��ά�����У�ͬʱ������һ
    space(section);
    fprintf(fout,"ID\n");

    space(section+1);
    fprintf(fout,"%s\n",token1);//�ѱ�ʶ��������ļ�
    fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����
    printf("%s %s\n",token,token1);
    if(strcmp(token,";")==0)//���ֱ����һ��ID����Ƿֺ�
    {
    	space(section);
    	fprintf(fout,";\n");
    	fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����
    	printf("%s %s\n",token,token1);
    	return es;//����;ʱ����
	}
	//���������Ƿֺ�
    if(strcmp(token,","))
        return (es=16);//ȱ�ٷֺŷ���7
    space(section);
    fprintf(fout,",\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����
    printf("%s %s\n",token,token1);
    }
    //�������ĩβ�Ƿ�Ϊ;
    if(strcmp(token,";")==0)
    {
    	space(section);
    	fprintf(fout,";\n");
    	fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����
    	printf("%s %s\n",token,token1);
    	return es;//����;ʱ����
	}
	else
	return (es=7);//ȱ�ٷֺ�
}
//�ߡ�<statement_list>::={<statement>}
//<�������>��{<���>}
int statement_list(int section,char word[MAX][MAX],char *ID){//�����Ѿ��������ַ���token������ֱ������ͱȽ�
    int es=0;
    space(section++);//����ո�  ��֮������Ļ��һ���ո�
    fprintf(fout,"<statement_list>\n");
    while(strcmp(token,"}")){//follow����{}}  ���û����'}'��һֱ����statement����
        es=statement(section,word,ID);//������䣬�ұ�������Ŀո���һ�� statement���һ��
		if(strcmp(token," ")==0)//����������Ϊ���ַ�ʱ
		return (es=17);
        if(es>0)//���岿�ֳ���
            return es;
    }
    return es;
}

//�ж�������������������ͣ����Ž����Ӧ�ķ�������
int statement(int section,char word[MAX][MAX],char*ID){
    int es=0;
    space(section++);//����ո���֮���������һ���ո�
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
    else if(es==0&&strcmp(token,"switch")==0)//����switch����ʶ��
        es=switch_stat(section,word,ID);
    else if(es==0&&strcmp(token,"read")==0){
        es=read_stat(section,word,ID);
    }
   else if(es==0&&strcmp(token,"write")==0){
        es=write_stat(section,word,ID);
        return es;
    }
    else if(es==0&&strcmp(token,"{")==0){//�������first����{ { } for if while�����ĸ������
        es=compound_stat(section,word,ID);
    }
    else if(es==0&&strcmp(token,"ID")==0||strcmp(token,"NUM")==0||strcmp(token,"(")==0||strcmp(token,";")==0){//���Ϻ�����һ���ֺŵ��ж�
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
//�š�<if_stat>::=if'('<expression>')'<statement>[else<statement>]
//<if���>��if��(��<���ʽ>��)��<���>[else<���>]
//ͨ�׽���: if(expression) ���1 [else ���2]
int if_stat(int section,char word[MAX][MAX],char*ID){
   int es=0;
    space(section++);
    fprintf(fout,"<if_stat>\n");
    space(section);
    fprintf(fout,"if\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����
    printf("%s %s\n",token,token1);
    if(strcmp(token,"("))
        return (es=2);//ȱ��"("
    space(section);
    fprintf(fout,"(\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����
    printf("%s %s\n",token,token1);

    es=expression(section,word,ID);//if�еı��ʽ
    //expression���һ��

    if(es>0)
        return es;
    if(strcmp(token,")"))
        return (es=3);//ȱ��")"
    space(section);
    fprintf(fout,")\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����
    printf("%s %s\n",token,token1);

    es=statement(section,word,ID);//if����е����
    if(es>0)
        return es;
    //statement��������һ��
    if(strcmp(token,"else")==0){
        space(section);
        fprintf(fout,"else\n");
        fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����
        printf("%s %s\n",token,token1);

        es=statement(section,word,ID);//else�е����
        if(es>0)
            return es;
    }
    return es;
}
//ʮ��<while_stat>::=while'('<expression>')��<statement>
//<while���>��while'('<���ʽ>')'  '{' <���> '}'
int while_stat(int section,char word[MAX][MAX],char*ID){
    int es=0;
    space(section++);//����ո�֮��Ŀո���һ��
    fprintf(fout,"<while_stat>\n");
    space(section);
    fprintf(fout,"while\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����
    printf("%s %s\n",token,token1);
    if(strcmp(token,"("))
        return (es=2);//ȱ��"("

    space(section);
    fprintf(fout,"(\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����
    printf("%s %s\n",token,token1);

    //while�е����
    es=expression(section,word,ID);//���һ��
    if(es>0)
        return es;
    if(strcmp(token,")"))
        return (es=3);//ȱ��")"
    space(section);
    fprintf(fout,")\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����
    printf("%s %s\n",token,token1);

    es=statement(section,word,ID);


    return es;
}
//11.<for_stat>::=for'('<expression>;<expression>;<expression>')'<statement>
//<for���>��for'('<���ʽ>;<���ʽ>;<���ʽ>')'<���>
int for_stat(int section,char word[MAX][MAX],char*ID){
    int es=0;
    space(section++);
    fprintf(fout,"<for_stat>\n");
    space(section);
    fprintf(fout,"for\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����
    printf("%s %s\n",token,token1);
    if(strcmp(token,"("))
        return (es=2);//ȱ��"("
    space(section);
    fprintf(fout,"(\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����
    printf("%s %s\n",token,token1);
    es=expression(section,word,ID);//���ʽ1
    //expression���һ��
    if(es>0)
        return es;
    if(strcmp(token,";"))
        return (es=7);//ȱ��";"

    space(section);
    fprintf(fout,";\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����
    printf("%s %s\n",token,token1);
    es=expression(section,word,ID);//���ʽ2
    //expression���һ��
    if(es>0)
        return es;

    if(strcmp(token,";"))
        return (es=7);//ȱ��";"
    space(section);
    fprintf(fout,";\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����
    printf("%s %s\n",token,token1);

    es=expression(section,word,ID);//���ʽ3
    //expression���һ��
    if(es>0)
        return es;
    if(strcmp(token,")"))
        return (es=3);//ȱ�١�)��
    space(section);
    fprintf(fout,")\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����
    printf("%s %s\n",token,token1);
    es=statement(section,word,ID);
    return es;
}
//���ӹ���
//12.<do_while_stat>::=do'{'<statement_list>'}'while'('<expression>')'
//<do_while���>��do'{'<�������>'}'while'('<���ʽ>')'
int do_while_stat(int section,char word[MAX][MAX],char*ID){
    int es=0;
    space(section++);
    fprintf(fout,"<do_while>\n");
    space(section);
    fprintf(fout,"do\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����
    printf("%s %s\n",token,token1);
    if(strcmp(token,"{"))
        return (es=5);//ȱ��'{'
    space(section);
    fprintf(fout,"{\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����
    printf("%s %s\n",token,token1);

    //do�е����
    es=statement_list(section,word,ID);
    //statement()���һ��

    if(es>0)
        return es;
    if(strcmp(token,"}"))
        return (es=6);//ȱ��'}'
    space(section);
    fprintf(fout,"}\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����
    printf("%s %s\n",token,token1);
    //��������while
    if(strcmp(token,"while"))
        return (es=8);//ȱ��while
    space(section+1);
    fprintf(fout,"while\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����
    printf("%s %s\n",token,token1);

    if(strcmp(token,"("))
        return (es=2);//ȱ�١�(��
    space(section);
    fprintf(fout,"(\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����
    printf("%s %s\n",token,token1);
    es=expression(section,word,ID);
    //statement�������һ��
    if(es>0)
        return es;

    if(strcmp(token,")"))
        return (es=3);//ȱ�١�)��
    space(section);
    fprintf(fout,")\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����
    printf("%s %s\n",token,token1);

    if(strcmp(token,";"))
        return (es=7);//ȱ�ֺ�
    space(section);
    fprintf(fout,";\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����
    printf("%s %s\n",token,token1);
    return es;
}
//13.<write_stat>::=write<expression>;
//<write���>::=write<���ʽ>;
int write_stat(int section,char word[MAX][MAX],char*ID){
    int es=0;
    space(section++);
    fprintf(fout,"<write_stat>\n");
    space(section);
    fprintf(fout,"write\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����
    printf("%s %s\n",token,token1);

    es=expression(section,word,ID);
    if(es>0)
        return es;

    if(strcmp(token,";"))
        return (es=7);//ȱ�ֺ�
    space(section);
    fprintf(fout,";\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����
    printf("%s %s\n",token,token1);
    return es;
}
//14.<read_stat>::=read ID;
//<read���>::=read ID;
int read_stat(int section,char word[MAX][MAX],char*ID){
    int es=0;
    int i=0;
    space(section++);
    fprintf(fout,"<read_stat>\n");
    space(section);

    fprintf(fout,"read\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����
    printf("%s %s\n",token,token1);

    if(strcmp(token,"ID"))
        return (es=1);//ȱ�ٱ�ʶ��
    while(i<MAX){
        if(strcmp(word[i],token1)==0||strcmp(WORD[i],token1)==0||strcmp(ID,token1)==0)
            break;
        i++;
    }
    if(i==MAX)
        return(es=11);//����δ�����͵���

    space(section);
    fprintf(fout,"ID\n");
    space(section+1);
    fprintf(fout,"%s\n",token1);
    fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����
    printf("%s %s\n",token,token1);

    if(strcmp(token,";"))
        return (es=7);//ȱ�ֺ�
    space(section);
    fprintf(fout,";\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����
    printf("%s %s\n",token,token1);
    return es;
}
//15.<compound_stat>::='{'<statement_list>'}'    if else while for�ȿ��ܻ�ʹ�ø������
//<�������>��'{'<�������>'}'
int compound_stat(int section,char word[MAX][MAX],char*ID){
    int es=0;
    space(section++);
    fprintf(fout,"<compound_stat>\n");
    space(section);
    fprintf(fout,"{\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����
    printf("%s %s\n",token,token1);

    es=statement_list(section,word,ID);//������� ������������������
    if(es>0)
        return es;
    if(strcmp(token,"}"))
        return(es=6);
    space(section);
    fprintf(fout,"}\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����
    printf("%s %s\n",token,token1);
    //����һ���ַ�
    return es;
}
//16.<expression_stat>::=<expression>;|;
//<���ʽ���>��<���ʽ>;|;
int expression_stat(int section,char word[MAX][MAX],char*ID){
    int es=0;
    space(section++);
    fprintf(fout,"<expression_stat>\n");
    //�������ǿ���䣬��ֻ��һ���ֺ�
    if(strcmp(token,";")==0){
        space(section);
        fprintf(fout,";\n");
        fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����
        printf("%s %s\n",token,token1);
        return es;
    }

    es=expression(section,word,ID);//��䲻��ʱ
    //expression���һ��
    if(es>0)
        return es;
    if(strcmp(token,";"))
        return (es=7);//ȱ�ٷֺ�
    space(section);
    fprintf(fout,";\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����
    printf("%s %s\n",token,token1);
    return es;
}
//17.<call_stat>::=call ID'('[NUM|ID]')'  ';'
//<call���>��call ID'('[NUM]|ID')'  ';'

int call_stat(int section,char word[MAX][MAX],char*ID){
    int es=0;
    int i=0;//�����жϱ����Ƿ�����ʱ���õ���ֵ
    space(section++);
    fprintf(fout,"<call_stat>\n");
    space(section);
    fprintf(fout,"call\n");
    fscanf(fp,"%s%s\n",&token,&token1);//fscanf�����ո�ͻ���ʱ����
    printf("%s %s\n",token,token1);

    if(strcmp(token,"ID"))
        return (es=1);//ȱ�ٱ�ʶ��
    space(section);
    fprintf(fout,"ID\n");
    space(section+1);
    fprintf(fout,"%s\n",token1);
    fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����
    printf("%s %s\n",token,token1);

    if(strcmp(token,"("))
        return (es=2);//ȱ��"("
    space(section);
    fprintf(fout,"(\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����
    printf("%s %s\n",token,token1);
    if(strcmp(token,"NUM")==0||strcmp(token,"ID")==0){//���õĺ����в�������int�����ֻ����������ı��� token������ֵ��token1������ֵ
        if(strcmp(token,"ID")==0){
            while(i<MAX){
                if(strcmp(word[i],token1)==0||strcmp(WORD[i],token1)==0||strcmp(ID,token1)==0)
                    break;
                i++;
            }
           if(i==MAX)
                return(es=11);//����δ�����͵���
            space(section);
            fprintf(fout,"ID\n");
            space(section+1);
            fprintf(fout,"%s\n",token1);//��������
        }
        else{
            space(section);
            fprintf(fout,"NUM\n");
            space(section+1);
            fprintf(fout,"%s\n",token1);
        }
        fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����
        printf("%s %s\n",token,token1);
    }

    if(strcmp(token,")"))
        return (es=3);//ȱ��")"
    space(section);
    fprintf(fout,")\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����  �˴���ȡ����;
    printf("%s %s\n",token,token1);//���
    if(strcmp(token,";"))
        return (es=7);//ȱ�ֺ�
    space(section);
    fprintf(fout,";\n");
    printf("*****************");
    fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����
    printf("%s %s\n",token,token1);
    return es;
}
//18.<break_stat>��break';'
//<break���>��break';'
int break_stat(int section){
    int es=0;
    space(section++);
    fprintf(fout,"<break_stat>\n");
    space(section);
    fprintf(fout,"break\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����
    printf("%s %s\n",token,token1);
    if(strcmp(token,";"))
        return (es=7);//ȱ�ֺ�
    space(section);
    fprintf(fout,";\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����
    printf("%s %s\n",token,token1);
    return es;
}
//19.<continue_stat>��continue';'
//<continue���>��continue;
int continue_stat(int section){
    int es=0;
    space(section++);
    fprintf(fout,"<continue_stat>\n");
    space(section);
    fprintf(fout,"continue\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����
    printf("%s %s\n",token,token1);

    if(strcmp(token,";"))
        return (es=7);//ȱ�ֺ�
    space(section);
    fprintf(fout,";\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����
    printf("%s %s\n",token,token1);
    return es;
}
//20.<expression>::= ID=<bool_expr>|<bool_expr>
//����ǰ��ͺ����first���������ظ���"ID"������Ҫ�����ж�
//<���ʽ>��ID=<�������ʽ>|<�������ʽ>
int expression(int section,char word[MAX][MAX],char *ID){
    int es=0,fileadd;
    int i=0;
    space(section++);
    fprintf(fout,"<expression>\n");
    char token2[20],token3[40];
    if(strcmp(token,"ID")==0){//������ʽ����ID��ʼ
        fileadd=ftell(fp);//��¼��ǰ�ļ���λ�ã�����֮��ķ���
        while(i<MAX){//�жϱ����Ƿ�����
                if(strcmp(word[i],token1)==0||strcmp(WORD[i],token1)==0||strcmp(ID,token1)==0)
                    break;
                i++;
            }
        if(i==MAX)
            return(es=11);//����δ�����͵���
        fscanf(fp,"%s%s\n",&token2,&token3);//fscanf�����ո�ͻ���ʱ����
        if(strcmp(token2,"=")==0){//���������=������ ID=<�������ʽ>
            space(section);
            fprintf(fout,"ID\n");
            space(section+1);
            fprintf(fout,"%s\n",token1);
            printf("%s %s\n",token2,token3);
            space(section);
            fprintf(fout,"=\n");
            //�������¶�
            fscanf(fp,"%s%s\n",&token,&token1);//fscanf�����ո�ͻ���ʱ����
            printf("%s %s\n",token,token1);
            es=bool_expr(section,word,ID);
            if(es>0)
                return es;
        }
        else{//��������Ĳ���=����ôӦ��ֱ����
            fseek(fp,fileadd,0);//�������"="�Ļ������ļ��˻ص���¼λ��
			//fseek�����÷� :  int fseek(FILE *stream, long offset, int fromwhere);���������ļ�ָ��stream��λ�á�
            //printf("%s %s\n",token,token1);
            es=bool_expr(section,word,ID);//�������¶�
            if(es>0)
                return es;
        }
    }
    else//���ʽ����ID��ʼ ֱ��ƥ�䵽 <�������ʽ>
        es=bool_expr(section,word,ID);
    return es;
}
//21.<bool_expr>::=<additive_expr>|<additive_expr> '(' > | < | >= | <= | == | != | && | || | ! ')' <additive_expr>
//<�������ʽ>��<�������ʽ>|<�㷨���ʽ(>|<|>=|<=|==|!=|&&||||!)<�������ʽ>
//���书�ܣ��߼������&& || ��
int bool_expr(int section,char word[MAX][MAX],char*ID){
    int es=0;
    space(section++);
    fprintf(fout,"<bool_expr>\n");
    es=additive_expr(section,word,ID);
    //���һ��
    if(es>0)
        return es;
    if(strcmp(token,">")==0||strcmp(token,"<")==0||strcmp(token,">=")==0||strcmp(token,"<=")==0||strcmp(token,"==")==0||strcmp(token,"!=")==0||strcmp(token,"&&")==0||strcmp(token,"||")==0||strcmp(token,"!")==0){
        space(section);
        fprintf(fout,"%s\n",token1);//��������
        fscanf(fp,"%s%s\n",&token,&token1);//fscanf�����ո�ͻ���ʱ����
        printf("%s %s\n",token,token1);
        es=additive_expr(section,word,ID);
        if(es>0)
            return es;
    }
    return es;
}
//22.<additive_expr>::=<term>{(+|-)< term >}
//<�������ʽ>��<��>{(+|-)<��>}
int additive_expr(int section,char word[MAX][MAX],char*ID){
    int es=0;
    space(section++);
    fprintf(fout,"<additive_expr>\n");
    es=term(section,word,ID);
    //term ���һ���ַ�
    if(es>0)
        return es;
    while(strcmp(token,"+")==0||strcmp(token,"-")==0){//����������ʽ
        space(section);
        fprintf(fout,"%s\n",token1);
        fscanf(fp,"%s%s\n",&token,&token1);//fscanf�����ո�ͻ���ʱ����
        printf("%s %s\n",token,token1);
        es=term(section,word,ID);
        if(es>0)
            return es;
    }
    return es;
}
//23.<term>::=<factor>{(*|/)< factor >}
//<��>��<����>{(*|/)<����>}
int term(int section,char word[MAX][MAX],char*ID){
     int es=0;
     space(section++);
     fprintf(fout,"<term>\n");
     es=factor(section,word,ID);
     //factor���һ��
     if(es>0)
        return es;
     while(strcmp(token,"*")==0||strcmp(token,"/")==0){
        space(section);
        fprintf(fout,"%s\n",token1);
        fscanf(fp,"%s%s\n",&token,&token1);//fscanf�����ո�ͻ���ʱ����
        printf("%s %s\n",token,token1);
        es=factor(section,word,ID);
        if(es>0)
            return es;
    }
    return es;
}
//24.<factor>::='('<expression>')'|ID|NUM
//<����>��'('<�������ʽ>')'|ID|NUM
int factor(int section,char word[MAX][MAX],char*ID){
    int es=0;
    int i=0;
    space(section++);
    fprintf(fout,"<factor>\n");
    if(strcmp(token,"(")==0){//������������ʽ
        space(section);
        fprintf(fout,"(\n");
        fscanf(fp,"%s%s\n",&token,&token1);//fscanf�����ո�ͻ���ʱ����
        printf("%s %s\n",token,token1);

        es=expression(section,word,ID);//���
        if(es>0)
            return es;

        if(strcmp(token,")"))
            return (es=3);//ȱ��������
        space(section);
        fprintf(fout,")\n");
        fscanf(fp,"%s%s\n",&token,&token1);//fscanf�����ո�ͻ���ʱ����
        printf("%s %s\n",token,token1);
    }
    else{//�Ǳ�ʶ����������
        if(strcmp(token,"ID")==0||strcmp(token,"NUM")==0){
            if(strcmp(token,"ID")==0){//����Ǳ�ʶ��
            while(i<MAX){
                if(strcmp(word[i],token1)==0||strcmp(WORD[i],token1)==0||strcmp(ID,token1)==0)
                    break;
                i++;
            }
            if(i==MAX)
                return(es=11);//����δ�����͵���
            }
            space(section);
            fprintf(fout,"%s\n",token1);
            fscanf(fp,"%s%s\n",&token,&token1);//fscanf�����ո�ͻ���ʱ����
            printf("%s %s\n",token,token1);
            return es;
        }
        else//���Ǳ�ʶ�� �������� ���Ǳ��ʽ  ���ȱ������
            return(es=9);//ȱ�ٲ�������ƥ�䲻���﷨
    }
    return es;
}
//��ʮ��:<switch_case>::= <switch_stat> '(' factor ')' '{' case_list'}'
int switch_stat(int section,char word[MAX][MAX],char*ID)
{
	int es=0;
    space(section++);
    fprintf(fout,"<switch_stat>\n");
    space(section);
    fprintf(fout,"switch\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����
    printf("%s %s\n",token,token1);
    if(strcmp(token,"("))
        return (es=2);//ȱ��"("
    space(section);
    fprintf(fout,"(\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����
    printf("%s %s\n",token,token1);

    es=factor(section,word,ID);//switch�еı��ʽ
    //factor���һ��
    if(es>0)
        return es;
    if(strcmp(token,")"))
        return (es=3);//ȱ��")"
    space(section);
    fprintf(fout,")\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����
    printf("%s %s\n",token,token1);

    if(strcmp(token,"{"))
        return (es=5);//ȱ��'{'
    space(section);
    fprintf(fout,"{\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����
    printf("%s %s\n",token,token1);
    if(strcmp(token,"case")==0)//����������case
   {
    es=case_list(section,word,ID);
    //case_list()���һ��
    if(es>0)
        return es;
    }
    else
    return (es=16);//�������Ĳ���case

    if(strcmp(token,"}"))
        return (es=6);//ȱ��'}'
    space(section);
    fprintf(fout,"}\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����
    printf("%s %s\n",token,token1);
    return es;
}

//case���� ::= case <factor> : {<expression>} break;
int case_list(int section,char word[MAX][MAX],char*ID)
{
	int es=0;
    space(section++);
    fprintf(fout,"<case_stat>\n");
    space(section);
    fprintf(fout,"case\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����
    printf("%s %s\n",token,token1);

    es=factor(section,word,ID);//caseѡ��� ĳһ���
    //factor()���һ��
    if(es>0)//�����
        return es;
    if(strcmp(token,":"))
        return (es=14);//ȱ��":"
    space(section);
    fprintf(fout,":\n");
    fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����
    printf("%s %s\n",token,token1);
	if(strcmp(token,"break"))//����䣬���ǵ�����break
{
    es=expression(section,word,ID);//case�е����
    //expression�ж��һ��
    if(es>0)
        return es;
    if(strcmp(token,";"))
        return (es=7);//ȱ��;
    space(section);
	fprintf(fout,";\n");

	fscanf(fp,"%s%s\n",token,token1);//fscanf�����ո�ͻ���ʱ����
    printf("%s %s\n",token,token1);
	es=break_stat(section);
    if(es>0)
    return (es=15);
}
	else//ֱ����һ��break�����
	{
	es=break_stat(section);
	if(es>0)
    return (es=15);
	}

    //break_stat�ж��һ��
	if(strcmp(token,"case")==0)//����������case
		case_list(section-1,word,ID);//֮���caseҪ��֮ǰ�Ķ���
    return es;
}
int  main(){
     system("color f0\n");
//�ȿ�ʼ�ʷ�����	���ҽ��ʷ�����������ļ���Ϊ�﷨�����������ļ�
	int result=0;
	printf("�¾��۵ĳ���\n");
	result=TESTscan();//���ܷ���ֵ���ж��Ƿ�����ɹ�
    if(result=0)
    {printf("\n�ʷ��������");}
    int es;
    es=TESTparse();
    if(es>0)
        printf("�﷨��������\n");
    else
        printf("�﷨�����ɹ���\n");
    printf("�¾��۵ĳ���\n");
    return es;
}
