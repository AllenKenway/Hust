#include<stdio.h>
#include<math.h>
/* ����ԭ�ͣ�����f(x) */
double f(double);
/* ����ԭ�ͣ�����f(x)�ĵ��� */
double ff(double);
int main()
{
	double x = 3;
	double xx = x - f(x) / ff(x);
	while (fabs(xx - x)>1e-6)
	{
		x = xx;
		xx = x - f(x) / ff(x);
	}
	printf("%lf\n", xx);
}
/*�������ܣ�����f(x)
���������double x
�� �� ֵ��f(x)*/
double f(double x)
{
	return (3 * pow(x, 3) - 4 * pow(x, 2) - 5 * x + 13);
}
/*
�������ܣ�����f(x)
���������double x
�� �� ֵ��f(x)�ĵ���
*/
double ff(double x)
{
	return (9 * pow(x, 2) - 8 * x - 5);
}

