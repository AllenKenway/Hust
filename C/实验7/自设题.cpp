#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*�洢ѧ����Ϣ�Ľṹ*/ 
struct stu{
	char id[15];
	char name[20];
	float english;
	float math;
	float phy;
	float c;
	struct stu *next;	
};
struct stu *head=NULL;
void creat(int n);
void show(int n);
struct stu* insert(char* a);
/*���ӽ��ĺ���*/
struct stu* insert(char* a)
{
	struct stu * current=head,*after,*other;
	while((strcmp(current->id,a))!=0&&current!=NULL)
	    current=current->next;
	if(!current)return NULL;
	after=current->next;
	other=(struct stu*)malloc(sizeof(struct stu));
	printf("���³�Ա��ֵ��\n");
	scanf("%s",other->id);
	scanf("%s",other->name);
	scanf("%f",&other->english);
	scanf("%f",&other->math);
	scanf("%f",&other->phy);
	scanf("%f",&other->c);
	if(after)
	{
		other->next=after;
		current->next=other;
	}
	else
	{
		other->next=NULL;
		current->next=other;
	}
	return current;
}
/*������������*/
void creat(int n)
{
    struct stu *p=head,**headp=&head;
    scanf("%s",head->id);
	scanf("%s",head->name);
	scanf("%f",&head->english);
	scanf("%f",&head->math);
	scanf("%f",&head->phy);
	scanf("%f",&head->c);
	for(int i=1;i<n;i++)
	{
		p->next=(struct stu*)malloc(sizeof(struct stu));
		p=p->next;
		scanf("%s",p->id);
		scanf("%s",p->name);
		scanf("%f",&p->english);
		scanf("%f",&p->math);
		scanf("%f",&p->phy);
		scanf("%f",&p->c);
	}
	p->next=NULL;
}
int main()
{
	head=(struct stu*)malloc(sizeof(struct stu));
	int n;
	scanf("%d",&n);
	creat(n);
	show(n);
	char a[15];
	printf("����λ�õ���һ��ѧ����ѧ�ţ�");
	scanf("%s",a);
	insert(a);
	show(n+1);
	return 0;
}
/*����ʽ���ѧ����Ϣ�ĺ���*/ 
void show(int n)
{
	printf("%-15s%-20s%-10s%-10s%-10s%-10s\n","ID","Name","English","Math","Physics","C");
    struct stu *p=head;
	for(int i=0;i<n;i++)
	{
		printf("%-15s",p->id);
		printf("%-20s",p->name);
		printf("%-10.2f",p->english);
		printf("%-10.2f",p->math);
		printf("%-10.2f",p->phy);
		printf("%-10.2f\n",p->c);
		p=p->next;
	}
	printf("\n");
}
