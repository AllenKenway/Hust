#include<stdio.h>
#include<stdbool.h>
int main()
{
	int N;
	scanf("%d", &N);
	getchar();
	for (int k = 0; k<N; k++)//��������N������
	{
		int i = 0;
		bool flag = true;
		char c;
		while ((c = getchar()) != '\n')//ѭ�����뵥���ַ�c
		{
			if (flag == true && c == ' ')//3.1
			{
				putchar(c);
				flag = false;
			}
			if (flag == true && c != ' ')//3.2
			{
				printf("%c", c);
			}
			if (flag == false && c != ' ')//3.3
			{
				printf("%c", c);
				flag = true;
			}
			else continue;
		}
		printf("\n");
	}
}

