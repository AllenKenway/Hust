#include<stdio.h>
int main()
{
	unsigned short x,m,n;
	printf("����x��m��0~15����n��1~16-m����\n ");
	scanf("%hu%hu%hu",&x,&m,&n);
	if(m>=0&&m<=15&&n>=1&&n<=(16-m))//�ж�m��n��ֵ�Ƿ��ں���Χ�� 
	{
		x=(x>>m)<<(16-n);
		printf("ans=%hu\n",x);
	}
	else
		printf("�������\n");
	return 0;
}
