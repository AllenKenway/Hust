/*��2�����ô�СΪn��ָ������ָ����gets���������n�У�ÿ�в�����80���ַ���
��дһ������������ÿһ���������Ķ���ո��ַ�ѹ��Ϊһ���ո��ַ���
�ڵ��ú��������ѹ���ո��ĸ��У����в��������*/

#include <stdio.h>  
void ChangeInput(void) 
{ 
	for(;;)
	{
		char s[100][80];     
    	char *p[100];     
    	int i,n; 
	    scanf("%d",&n);
    	if(!n) break;
    	getchar();
    	for (i=0; i<n; i++)     
		{
			fgets(s[i],80,stdin);         
	     	p[i] = s[i];     
		} 
        for (i=0; i<n; i++)     
		{ 
			int j; 
            for (j=0; p[i][j]!='\0';j++ )
			{ 
				if (p[i][j]==' ' && p[i][j+1]==' ')             
				{ 
					int k=j+1; 
                    while (p[i][k++]==' ');                 
     				k--; 
                    int tmp=j+1; 
                    while (p[i][tmp++]=p[i][k++]);             
				}  
			}     
		}      
        for (i=0; i<n; i++)
			if(p[i][0]!='\n') printf("%s",*(p+i));
			putchar('\n');
	}   
}
int main(void)
{ 
    ChangeInput();     
	return 0; 
}  







 