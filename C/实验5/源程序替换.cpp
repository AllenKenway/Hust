#include<stdio.h>
#include<stdlib.h>
#define M 10
#define N 3
int main()
{
	int i, k = 0, count = M, a[M];
	for (i = 0; i < M; i++)
		a[i] = 1;//a�����ÿ��Ԫ�س�ֵΪ1����ʾ�����˶���Ȧ��
	for (i = 0;; i++)
	{
		if (a[i] == 0)//˵��������Ѿ�����Ȧ��
		{
			if (i == M - 1)
				i = -1;
			continue;
		}
		k++;
		if (k == N)
		{
			a[i] = 0;
			printf("%6d", i + 1);
			k = 0;
			count--;
		}
		if (count == 0)
			break;
		if (i == M - 1)//�����������ĩβ������������ͷ��
			i = -1;
	}
	printf("\n");
	system("pause");
}
