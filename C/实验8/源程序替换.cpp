#include<stdio.h>
#include<stdlib.h>
int main(int argc, char* argv[])
{
	char ch;
	if(argc!=2){
		printf("Arguments error!\n");
		exit(-1);
	}
  	if(freopen(argv[1],"r",stdin)==NULL){    /*ʹstdinָ��Ŀ���ļ�*/
	printf("Can't open %s file!\n",argv[1]);
	exit(-1);
	}	
    while((ch=getchar())!=EOF)    /* ��stdin�ж��ַ� */
	   putchar(ch);                
	fclose(stdin);       /* �ر�stdin */
    return 0;	
}
