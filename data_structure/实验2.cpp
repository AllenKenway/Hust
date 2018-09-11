#include<stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include<string.h>

#define FALSE -1 
#define OK 1
#define ERROR -2 
#define TRUE 1
#define INFEASTABLE -1
#define OVERFLOW -2

typedef int status;
typedef int ElemType; //����Ԫ�����Ͷ���

#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
struct ListNode {
	ElemType data;
	struct ListNode *next;
};
struct MultiList {
	struct ListNode *ListHead;				/*ָ��һ�����Ա��ͷ�ڵ�*/
	int num;									/*���Ա�ı���*/
	struct MultiList *next;			/*ָ����һ����ͷ�ڵ�*/
};

void show(MultiList *List);
status IntiaList(ListNode *L);
status InitiaList2(MultiList *head, MultiList **List);
status DestroyList(ListNode* L);
status DestroyList2(MultiList *head, MultiList **List);
status ClearList(ListNode *L);
status ListEmpty(ListNode L);
int ListLength(ListNode L);
status GetElem(ListNode L, int i, ElemType *e);
status LocateElem(ListNode L, ElemType e);
status PriorElem(ListNode L, ElemType cur, ElemType *pre_e);
status NextElem(ListNode L, ElemType cur, ElemType *next_e);
status ListInsert(ListNode * L, int i, ElemType e);
status ListDelete(ListNode * L, int i, ElemType * e);
status ListTrabverse(ListNode L);
status MultiListTrabverse(MultiList head);
status SaveList(FILE *fp, ListNode L, char filename[30]);
status LoadList(FILE *fp, ListNode *L, char filename[30]);
MultiList *ExList(MultiList *head);

int main()
{
	struct MultiList* head = (MultiList *)malloc(sizeof(MultiList));
	head->ListHead = NULL; head->next = NULL; head->num = 0;
	struct MultiList* List;
	List = head->next;

	FILE  *fp=NULL;
	char filename[30];	/*�洢�ļ���*/

	int op = 1;
	status a;
	int i = 0, cur,num1,num2;
	ElemType e = 0, e1 = 0;
	ElemType pre_e = 0, next_e = 0;
	while (op)
	{
		show(List);
		scanf("%d", &op);
		switch (op)
		{
		case 0:
			break;
		case 1:
			if (InitiaList2(head, &List) == OK)
				printf("���Ա����ɹ���\n");
			else
				printf("���Ա���ʧ�ܣ�\n");
			getchar(); getchar();
			break;
		case 2:
			if (List == NULL)
				printf("��ǰû�л��\n");
			else
			{
				if (DestroyList2(head, &List) != ERROR)
					printf("���Ա����ٳɹ���\n");
				else
					printf("���Ա�����ʧ�ܣ�\n");
			}
			getchar(); getchar();
			break;
		case 3:
			if (List == NULL)
				printf("��ǰû�л��\n");
			else
			{
				if (ClearList(List->ListHead) != ERROR)
					printf("���Ա��ÿճɹ���\n");
				else
					printf("���Ա��ÿ�ʧ�ܣ�\n");
			}
			getchar(); getchar();
			break;
		case 4:
			if (List == NULL)
				printf("��ǰû�л��\n");
			else
			{
				if (ListEmpty(*(List->ListHead)) != ERROR)
					printf("���Ա�Ϊ�ձ�\n");
				else
					printf("���Ա�Ϊ�ձ�\n");
			}
			getchar(); getchar();
			break;
		case 5:
			if (List == NULL)
				printf("��ǰû�л��\n");
			else
				printf("���Ա�ĳ���Ϊ%d", ListLength(*(List->ListHead)));
			getchar(); getchar();
			break;
		case 6:
			if (List == NULL)
				printf("��ǰû�л��\n");
			else
			{
				printf("��������Ҫ���ҵ�Ԫ�ص�λ��");
				scanf("%d", &i);
				if (GetElem(*(List->ListHead), i, &e) != ERROR)
					printf("��%d��Ԫ��Ϊ%d", i, e);
			}
			getchar();getchar();
			break;
		case 7:
			if (List == NULL)
				printf("��ǰû�л��\n");
			else
			{
				printf("��������Ҫ���жԱȵ�Ԫ��e��");
				scanf("%d", &e);
				a = LocateElem(*(List->ListHead), e);
				if (a != ERROR&&a!=0)
					printf("��%d��Ԫ����Ԫ��e��ͬ��", a);
				else  if(a==0)
					printf("��������e��ͬ��Ԫ�أ�");
				else
					printf("�ñ�Ϊ�ձ���λʧ�ܡ�\n");
			}
			getchar();getchar();
			break;
		case 8:
			if (List == NULL)
				printf("��ǰû�л��\n");
			else
			{
				printf("����������Ԫ��cur��");
				scanf("%d", &cur);
				if (PriorElem(*(List->ListHead), cur, &pre_e) == OK)
					printf("%d��ǰ������Ԫ��Ϊ%d", cur, pre_e);
			}
			getchar();getchar();
			break;
		case 9:
			if (List == NULL)
				printf("��ǰû�л��\n");
			else
			{
				printf("����������Ԫ��cur��");
				scanf("%d", &cur);
				if (NextElem(*(List->ListHead), cur, &next_e) != ERROR)
					printf("%d�ĺ������Ԫ��Ϊ%d", cur, next_e);
			}
			getchar();getchar();
			break;
		case 10:
			if (List == NULL)
				printf("��ǰû�л��\n");
			else
			{
				printf("��������Ҫ�����λ��i��");
				scanf("%d", &i);
				printf("������Ҫ�����Ԫ��e��");
				scanf("%d", &e);
				if (ListInsert(List->ListHead, i, e) == OK)
					printf("����Ԫ�سɹ���");
				else
					printf("����Ԫ��ʧ�ܣ�");
			}
			getchar();getchar();
			break;
		case 11:
			if (List == NULL)
				printf("��ǰû�л��\n");
			else
			{
				printf("������Ҫɾ����Ԫ�ص�λ��i��");
				scanf("%d", &i);
				if (ListDelete(List->ListHead, i, &e) == OK)
					printf("λ��Ϊ%d��Ԫ�ص�ֵΪ%d\nɾ��Ԫ�سɹ���", i, e);
				else
					printf("ɾ��Ԫ��ʧ�ܣ�");
			}
			getchar();getchar();
			break;
		case 12:
			if (List == NULL)
				printf("��ǰû�л��\n");
			else
				ListTrabverse(*(List->ListHead));
			getchar(); getchar();
			break;
		case 13:
			if (List == NULL)
				printf("��ǰû�л��,���ܽ����ļ���ȡ��\n");
			else
				SaveList(fp, *(List->ListHead), filename);
			getchar();getchar();
			break;
		case 14:
			if (List == NULL)
				printf("��ǰû�л��,���ܽ����ļ���ȡ��\n");
			else
				LoadList(fp, List->ListHead, filename);
			getchar();getchar();
			break;
		case 15:
			if (head->next== NULL)
			{
				printf("û�пɲ����ı�");
				getchar();	getchar();
				break;
			}
			if (MultiListTrabverse(*head) == NULL)
				break;
			List = ExList(head);
			getchar();
			break;
		default:
			printf("����ѡ������Ч�����롣\n");
			getchar(); getchar();
		}
	}
	printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
	getchar();	getchar();
}
/******************
* �������ƣ�ExList
* ����������MultiList��ͷָ��
* �������ܣ����ж���л�����
* ����ֵ��һ��ָ���л���Ļ���ָ��
*******************/
MultiList* ExList(MultiList *head)
{
	int num;
	printf("��������Ҫ���в����ı�ı�ţ�");
	scanf("%d", &num);
	MultiList * List = head->next;
	if(num<1)
	{
		printf("����ı��벻�Ϸ���\n");
		getchar(); 
	}
	for (int i = 1; i<num&&List != NULL; i++)
		List = List->next;
	if (List == NULL)
	{
		printf("����ı��벻�Ϸ���\n");
		getchar(); 
	}
	return List;
}
/******************
*�������ƣ�MultiListTrabverse
*����������MultiListͷָ��head
*�������ܣ�������ʾÿһ�����Ա�ı��롢���Լ����Ա��е�ÿ��Ԫ�ء�
*����ֵ���ɹ��������������Ա�ĳ��ȣ����򷵻�ERROR
******************/
status MultiListTrabverse(MultiList head)
{
	MultiList *p = (&head)->next;
	if (p == NULL)
		printf("��ǰ�����Ա���ڡ�\n");
	while (p)
	{
		printf("������%d\t", p->num);
		ListTrabverse(*p->ListHead);
		printf("\n");
		p = p->next;
	}
	getchar();
	return OK;
}
/******************
*�������ƣ�LoadList
*�����������ļ�ָ�룬���Ա�L,�ļ���filename[30]
*�������ܣ����ݼ��أ�Ϊ���Ա�����Ԫ�ء�
*����ֵ�����سɹ�����OK������ʧ�ܷ���ERROR
******************/
status LoadList(FILE *fp, ListNode *L, char filename[30])
{
	int e,i=0;
	printf("������Ҫ�������ݵ��ļ���: ");
	scanf("%s",filename,30);
	if ((fp=fopen(filename, "r+")) == NULL)
	{
		printf("�ļ���ʧ�ܣ�\n");
		return ERROR;
	}
	L->data = 0;
	while (fscanf(fp, "%d", &e) != EOF)
	{
			i++;
			printf("�����%d��Ԫ��%d...\n", i, e);
			ListInsert(L, i, e);
	}
	getchar();
	
	printf("�������.");
	fclose(fp);
	return OK;
}
/******************
*�������ƣ�SaveList
*�����������ļ�ָ�룬���Ա�L��ͷ��㣬�ļ���filename[30]
*�������ܣ���L�е����ݱ��浽fpָ��ָ����ļ���
*����ֵ���ɹ�����OK��ʧ�ܷ���ERROR
******************/
status SaveList(FILE *fp, ListNode L, char filename[30])
{
	printf("������Ҫд����ļ���: ");
	scanf("%s",filename);
	if ((fp=fopen(filename, "w")) ==NULL)
	{
		printf("�ļ���ʧ�ܡ�");
		getchar();
		return ERROR;
	}
	ListNode*p = &L;
	for (int i = 0; i < L.data&&p!=NULL; i++)
	{
		p = p->next;
		fprintf(fp, "%d ", p->data);
	}
	printf("�ļ�д��ɹ���\n");
	fclose(fp);			
	return OK;
}
/******************
*�������ƣ�ListTrabverse
*�������������Ա�L��ͷ���
*�������ܣ�������ʾ���Ա��е�ÿ��Ԫ�ء�
*����ֵ���ɹ������������Ա�ĳ��ȣ����򷵻�ERROR
******************/
status ListTrabverse(ListNode L) 
{
	ListNode*q = &L;
	int i;
	if (L.data == 0)
	{
		printf("���Ա��ǿձ�\n");
	}
	else
		printf("����%d\n", L.data);
	printf("-----------all elements -----------------------\n");
	for (i = 0; i < L.data; i++)
	{
		q = q->next;
		printf("%3d ", q->data);
	}
	printf("\n------------------ end ------------------------\n");
	return OK;
}
/******************
*�������ƣ�ListDelete
*�������������Ա�L��ͷָ�룬ɾ����λ��i��ָ��e�ĵ�ַ��
*�������ܣ�ɾ��L�ĵ�i������Ԫ�أ���e������ֵ��
*����ֵ���ɹ�ɾ������OK�����򷵻�ERROR
******************/
status ListDelete(ListNode* L, int i, ElemType * e)
{
	if (i<1 || i>L->data)
	{
		printf("iֵ���Ϸ���");
		return ERROR;
	}
	ListNode *q = L;
	for (int j = 0; (j + 1) != i; j++)
		q = q->next;
	ListNode *p = q->next;
	q->next = p->next;
	*e = p->data;
	p->next = NULL;
	free(p);
	L->data--;
	return OK;
}
/******************
*�������ƣ�ListInsert
*�������������Ա�L��ͷָ�룬�����λ��i�����������Ԫ��e��
*�������ܣ���L�ĵ�i��λ��֮ǰ�����µ�����Ԫ��e��
*����ֵ���ɹ����뷵��OK�����򷵻�ERROR
******************/
status ListInsert(ListNode* L, int i, ElemType e)
{
	if (i<1 || i>L->data+1)
	{
		printf("iֵ���Ϸ�������ʧ�ܡ�\n");
		return ERROR;
	}
	ListNode *q = L;
	for (int j = 0; (j + 1) != i; j++)
		q = q->next;
	ListNode *temp=(ListNode*)malloc(sizeof(ListNode));
	temp->data = e;
	temp->next=q->next;
	q->next = temp;
	L->data++;
	return OK;
}
/******************
*�������ƣ�NextElem
*�������������Ա�L��ͷ��㣬���ҵ�����cur_e,����next_e��
*�������ܣ�����L����cur_e��ͬ�ĵ�һ�����ݣ�����next_e��������
*����ֵ���ɹ��򷵻���cur_e��ͬ�ĵ�һ�����ݣ�������OK�����޺����Լ���������򷵻�ERROR
******************/
status NextElem(ListNode L, ElemType cur, ElemType *next_e)
{
	int i= LocateElem(L, cur);
	if (i == ERROR || i == 0)
	{
		printf("%d ���ǻ���е�Ԫ��\n", cur);
		return ERROR;
	}
	else if (i == L.data)
	{
		printf("%d is the last letter has no next_elem��\n", cur);
		return ERROR;
	}
	else
	{
		ListNode *q = &L;
		for (int j = 0; (j -1)!= i; j++)
			q = q->next;
		*next_e = q->data;
		return OK;
	}
}
/******************
*�������ƣ�PriorElem
*�������������Ա�L��ͷ��㣬���ҵ�����cur,ǰ��pre_e��
*�������ܣ�����L����cur��ͬ�ĵ�һ�����ݣ�����pre_e������ǰ��
*����ֵ���ɹ��򷵻���cur��ͬ�ĵ�һ�����ݣ�������OK������ǰ���Լ���������򷵻�ERROR
******************/
status PriorElem(ListNode L, ElemType cur, ElemType *pre_e)
{
	int i = LocateElem(L, cur);
	if (i == ERROR || i == 0)
	{
		printf("%d ���ǻ���е�Ԫ��\n", cur);
		return ERROR;
	}
	else if (i == 1)
	{
		printf("%d is the first letter has no prior_elem\n", cur);
		return ERROR;
	}
	else {
		ListNode *q = &L;
		for (int j = 0; (j+1) != i; j++)
			q = q->next;
		*pre_e = q->data;
		return OK;
	}
}
/******************
*�������ƣ�LocateElem
*�������������Ա�L��ͷ��㣬��Աȵ�Ԫ��ֵ��
*�������ܣ�����L����e��ͬ�������ڵ�λ��λ���1��ʼ
*����ֵ���ɹ��򷵻ص�һ����e��ͬ�����ݵ�λ�򣬲������򷵻�0�������������ERROR
******************/
status LocateElem(ListNode L, ElemType e)
{
	int i = 1;
	if (L.data == 0)
		return ERROR;
	ListNode *q = (&L)->next;
	for (; q->data != e; )
	{
		q = q->next;
		i++;
		if (q == NULL)break;
	}
	if (i > L.data)
		return 0;
	else
		return i ;
}
/******************
*�������ƣ�GetElem
*�������������Ա�L��ͷ��㣬eΪ��i�����ݵĵ�ַ��
*�������ܣ����Ҳ���e����L�е�i��Ԫ�ص�ֵ��
*����ֵ���ɹ��򷵻�OK�����򷵻�ERROR
******************/
status GetElem(ListNode L, int i, ElemType *e)
{
	if (L.data == 0)
	{
		printf("�ñ�Ϊ�ձ�����ʧ�ܡ�\n");
		return ERROR;
	}
	if (i < 1 || i>L.data)
	{
		printf("iֵ���Ϸ���i��ȡֵ��ΧӦΪ1<=i<=%d��\n", ListLength(L));
		return ERROR;
	}
	ListNode *q = &L;
	for (int j=0;j!=i;j++)
		q = q->next;
	*e = q->data;
	return OK;
}
/******************
*�������ƣ�ListLength
*�������������Ա�L��ͷ���
*�������ܣ��������Ա�L������Ԫ�ظ�����
*����ֵ���ɹ�����L������Ԫ�ظ�����ʧ�ܷ���ERROR
******************/
int ListLength(ListNode L)
{
	return L.data;
}
/******************
*�������ƣ�ListEmpty
*�������������Ա�L��ͷ���
*�������ܣ��ж����Ա��Ƿ�Ϊ��
*����ֵ����LΪ�ձ��򷵻�OK�����򷵻�ERROR
******************/
status ListEmpty(ListNode L)
{
	if (L.data == 0)
		return OK;
	else
		return ERROR;
}
/******************
*�������ƣ�ClearList
*�������������Ա�L��ͷָ��
*�������ܣ������Ա�L����Ϊһ���ձ�
*����ֵ���ɹ��ÿշ���OK�����򷵻�ERROR
******************/
status ClearList(ListNode *L)
{
	if (L->next == NULL)
		return OK;
	DestroyList(L->next);
	L->data = 0;
	L->next = NULL;
	return OK;
}
/******************
*��������:DestroyList
*��������:�ͷű�L��ÿһ�����Ŀռ估ͷָ��Ŀռ�
*�������:L���ָ��ListNode��ָ��
*�������:��
*������ֵ:ʧ�ܷ���ERROR,�������ٳɹ�����OK
*����˵��:��
******************/
status DestroyList(ListNode *L)
{
	ListNode *q;
	while (L)
	{
		q = L->next;
		free(L);
		L = q;
	}
	return OK;
}
/******************
*�������ƣ�DestroyList2
*����������MultiList��ͷָ��head������ָ��List��
*�������ܣ�����MultiList�Ľ��List�����ListΪ�ա�
*����ֵ���ɹ����ٷ���OK�����򷵻�ERROR
******************/
status DestroyList2(MultiList *head, MultiList **List)
{
	MultiList *p = head;
	MultiList *q = p;
	while (p != *List)
	{
		q = p;
		p = p->next;
	}
	q->next = p->next;
	if (DestroyList(p->ListHead) == ERROR)
		return ERROR;
	free(p);
	*List = NULL;
	return OK;
}
/******************
*��������:InitiaList
*��������:��ʼ����L,
*�������:List->HeadList,
*�������:����ʼ�����Lָ��
*������ֵ:�������ڴ�ʧ��ʱ����ERROR,
*		 �����ʼ����ɹ�����SUCCESS
******************/
status IntiaList(ListNode *L)
{
	if (L == NULL)//�����ڴ�ʧ�� 
		return ERROR;
	L->next = NULL;
	L->data = 0;
	return OK;
}
/******************
* �������ƣ�InitiaList2
* ����������MultiList��ͷָ��head������ָ��List
* �������ܣ�����һ���յ�MultiList�ڵ�
* ����ֵ���ɹ����췵��OK�����򷵻�ERROR
******************/
status InitiaList2(MultiList *head, MultiList **List)
{
	MultiList *q = head;
	while (q->next)
	{
		q = q->next;
	}
	q->next = (MultiList *)malloc(sizeof(MultiList));
	*List = q->next;
	(*List)->num = q->num + 1;
	(*List)->ListHead = (ListNode*)malloc(sizeof(ListNode));
	if (IntiaList((*List)->ListHead) == ERROR)
		return ERROR;
	(*List)->next = NULL;
	return OK;
}
/******************
* �������ƣ�show
* ��������������ָ��List
* �������ܣ���ʾα�˵�����
* ����ֵ����
*******************/
void show(MultiList *List)
{
	system("cls");
	printf("\n\n");
	printf("      Menu for Linear Table On Chain Structure \n");
	printf("-------------------------------------------------\n");
	printf("    	  1. IntiaList      9. NextElem\n");
	printf("    	  2. DestroyList    10.ListInsert\n");
	printf("    	  3. ClearList      11.ListDelete\n");
	printf("    	  4. ListEmpty      12.ListTrabverse\n");
	printf("    	  5. ListLength     13.SaveList\n");
	printf("    	  6. GetElem        14.LoadList\n");
	printf("	  7. LocateElem     15.ExList\n");
	printf("	  8. PriorElem      0. Exit\n");
	printf("-------------------------------------------------\n");
	if (List == NULL)
		printf("\n-----------��ǰû�л��-----------\n");
	else
		printf("\n-----------��ǰ�Ա� %d ���в���-----------\n", List->num);
	printf("    ��ѡ����Ĳ���[0~15]:");
}
