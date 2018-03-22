#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;
//ͳ���ı��ַ�����
int CountChars(char *szFile)
{
    int n=0;
    FILE *fp;
    char buffer[1024];
    if ((fp=fopen(szFile,"r"))==NULL)
    {
        return -1;
    }

    while (!feof(fp))
    {
        //���ļ��ж�һ��
        if (fgets(buffer, sizeof(buffer),fp)!=NULL)
            n+=strlen(buffer);
    }
    //�ر��ļ�
    fclose(fp);
    return n;
}
//ͳ��һ�е��ʸ���
int WordLine(const char *szLine)
{
    int n=0;
    int flag=0;
    for(int i=0;i<strlen(szLine)-1;i++)
    {
        if(*(szLine+i)==' '||*(szLine+i)==',')
        {
            flag=0;
        }
        else
        {
            if(flag==0)
            {
                flag=1;
                n++;
            }
        }
    }

    return n;
}
//ͳ���ı����ʸ���
int CountWords(char *szFile)
{
    int n=0;
    FILE *fp;
    char buffer[1024];
    if ((fp=fopen(szFile,"r"))==NULL)
    {
        return -1;
    }
    while (!feof(fp))
    {
        if (fgets(buffer, sizeof(buffer),fp)!=NULL&&buffer[0]!='\0')
            n+=WordLine(buffer);

    }
    fclose(fp);
    return n;
}
//ͳ���ı�����
int CountLines(char *szFile)
{
    int n=0;
    FILE *fp;
    char buffer[1024];
    if ((fp=fopen(szFile,"r"))==NULL)
    {
        return -1;
    }
    while (!feof(fp))
    {
        if (fgets(buffer, sizeof(buffer),fp)!=NULL)
            n+=1;
    }
    fclose(fp);
    return n;
}
//ȥ���ַ����е�ĳЩ�ַ�
int rem(char *r,char ex)
{
    char data[100]={0};
    strcpy(data,r);
    int i=0,j=0;
    for(;data[i]!='\0';i++)
    {
        if(data[i]!=ex)
            data[j++]=data[i];
    }
    data[j]='\0';
    strcpy(r,data);
}
//ͳ���ı�������
int BlaLine(char *szFile)
{
    int n=0;
    FILE *fp;
    char buffer[1024];
    if ((fp=fopen(szFile,"r"))==NULL)
    {
        return -1;
    }

    while (!feof(fp))
    {
        fgets(buffer,sizeof(buffer),fp);
        rem(buffer,' ');
        rem(buffer,'\t');
        rem(buffer,'\n');
        if(strlen(buffer)<=1) n++;
    }
    fclose(fp);
    return n;
}
//ͳ���ı�ע������
int ExLine(char *szFile)
{
    int n=0;
    FILE *fp;
    char buffer[1024];
    if ((fp=fopen(szFile,"r"))==NULL)
    {
        return -1;
    }

    while (!feof(fp))
    {
        fgets(buffer,sizeof(buffer),fp);
        if(strstr(buffer,"//")!=NULL) n++;
    }
    fclose(fp);
    return n;
}
//ͳ���ı���������
int CodeLine(char *szFile)
{
    int n=0;
    FILE *fp;
    char buffer[1024];
    if ((fp=fopen(szFile,"r"))==NULL)
    {
        return -1;
    }

    while (!feof(fp))
    {
        fgets(buffer,sizeof(buffer),fp);
        rem(buffer,' ');
        rem(buffer,'\t');
        rem(buffer,'\n');
        if(strlen(buffer)>1&&strncmp(buffer,"//",2)!=0) n++;
    }
    fclose(fp);
    return n;
}
int main(int argc,char** argv)
{
    char* szFile,* outFile,* stopList;
    int c=0,w=0,l=0,o=0,s=0,a=0,i=1;
    const char sz[2]="-";
    const char csz[3]="-c";
    const char wsz[3]="-w";
    const char lsz[3]="-l";
    const char osz[3]="-o";
    const char asz[3]="-a";
    const char esz[3]="-e";
    for(;i<argc;i++)
    {
        if(strcmp(argv[i],csz)==0)
        {
            c++;
        }
        if(strcmp(argv[i],wsz)==0)
        {
            w++;
        }
        if(strcmp(argv[i],lsz)==0)
        {
            l++;
        }
        if(strcmp(argv[i],asz)==0)
        {
            a++;
        }
        if(strcmp(argv[i],osz)==0)
        {
            o++;
        }
        if(strncmp(argv[i],sz,1)!=0)
        {
            if(o==0)
                szFile=argv[i];
            else
                outFile=argv[i];
        }
    }
    if(c>=1)
    {
        wcout<<szFile<<",Characters :  "<<CountChars(szFile)<<endl;
    }
    if(w>=1)
    {
        cout<<szFile<<",Words :  "<<CountWords(szFile)<<endl;
    }
    if(l>=1)
    {
        cout<<szFile<<",Lines :  "<<CountLines(szFile)<<endl;
    }
    if(a>=1)
    {
        cout<<szFile<<", CodeLines/BlankLines/ExplainLines:  "<<CodeLine(szFile)<<"/"<<BlaLine(szFile)<<"/"<<ExLine(szFile)<<endl;
    }
    if(o>=1)
    {
        if(outFile==NULL)
            cout<<"error"<<endl;
        else{
        FILE *fpWrite=fopen(outFile,"w");
        if(fpWrite==NULL)
        {
            return -1;
        }
        if(c>=1)
        {
            fprintf(fpWrite,"%s,�ַ����� %d\n",szFile,CountChars(szFile));
        }
        if(w>=1)
        {
            fprintf(fpWrite,"%s,�������� %d\n",szFile,CountWords(szFile));
        }
        if(l>=1)
        {
            fprintf(fpWrite,"%s,������ %d\n",szFile,CountLines(szFile));
        }
        if(a>=1)
        {
            fprintf(fpWrite,"%s,������/����/ע����: %d/%d/%d",szFile,CodeLine(szFile),BlaLine(szFile),ExLine(szFile));
        }
        }
    }

}



