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
struct SqList{  
	ElemType * elem;//ָ�����Ա����ݵ����Դ洢��
	int length;//����Ԫ�صĸ���	
	int listsize;//������Ԫ�ظ���
};
struct MultiList {
	SqList *L;				/*ָ��һ�����Ա�*/
	int num;				/*�Զ����ɵı�ı���*/ 
	struct MultiList *next;	/*ָ����һ����ڵ�*/
};
status IntiaList(SqList *L);
status InitiaList2(MultiList *head, MultiList **List);
status DestroyList2(MultiList *head, MultiList **List);
status ClearList(SqList *L);
status ListEmpty(SqList L);
int ListLength(SqList L);
status GetElem(SqList L, int i, ElemType *e);
status LocateElem(SqList L, ElemType e);
status PriorElem(SqList L, ElemType cur, ElemType *pre_e);
status NextElem(SqList L, ElemType cur, ElemType *next_e);
status ListInsert(SqList * L, int i, ElemType e);
status ListDelete(SqList * L, int i, ElemType * e);
status ListTrabverse(SqList L);
status MultiListTrabverse(MultiList *head);
void show();
void updata(MultiList *head);
MultiList *ExList(MultiList *head);
status SaveList(FILE *fp,SqList L, char filename[30]); 
status LoadList(FILE *fp,SqList *L,char filename[30]);

int main(void) {
	int op = 1;
	int i = 0, cur;
	ElemType e = 0,e1=0;
	ElemType pre_e = 0, next_e = 0;
	status a;

	FILE  *fp;
	char filename[30];	/*�洢�ļ���*/

	MultiList head; head.L = NULL; head.next = NULL; 
	MultiList *List = head.next;

	int num;
	while (op) {
		show();
		if (List == NULL)
			printf("\n-----------��ǰû�л��-----------\n");
		else
			printf("\n-----------��ǰ�Ա� %d ���в���-----------\n", List->num);
		scanf("%d", &op);getchar();
		switch (op) {
		case 1:
			if (InitiaList2(&head, &List) == OK)
				printf("���Ա����ɹ���\n");
			else
				printf("���Ա���ʧ�ܣ�\n");
			getchar();
			break;
		case 2:
			if (List == NULL)
				printf("��ǰû�л��\n");
			else
			{
				if (DestroyList2(&head, &List) != ERROR)
					printf("���Ա����ٳɹ���\n");
				else
					printf("���Ա�����ʧ�ܣ�\n");
			}
			getchar();
			break;
		case 3:
			if (List == NULL)
				printf("��ǰû�л��\n");
			else
			{
				if (ClearList(List->L) == OK)
					printf("���Ա����óɹ���\n");
				else
					printf("��ǰû�л��\n");
			}
			getchar();
			break;
		case 4:
			if (List == NULL)
				printf("��ǰû�л��\n");
			else
				ListEmpty(*(List->L));
			getchar();
			break;
		case 5:
			if (List == NULL)
				printf("��ǰû�л��\n");
			else
			{
				a=ListLength(*(List->L));
				if (a!= ERROR)
					printf("���Ա�ĳ���Ϊ%d", a);
				else
					printf("��ǰû�л��\n");
			}
			getchar();
			break;
		case 6:
			if (List == NULL)
				printf("��ǰû�л��\n");
			else
			{
				printf("��������Ҫ���ҵ�Ԫ�ص�λ��");
				scanf("%d", &i);
				if (GetElem(*(List->L), i, &e) != ERROR)
					printf("��%d��Ԫ��Ϊ%d", i, e);
					getchar(); 
			}
			getchar();
			break;
		case 7:
			if (List == NULL)
				printf("��ǰû�л��\n");
			else
			{
				printf("��������Ҫ���жԱȵ�Ԫ��e��");
				scanf("%d", &e);
				a = LocateElem(*(List->L), e);
				if (a != ERROR)
					printf("��%d��Ԫ����Ԫ��e��ͬ��", a);
				else
					printf("��������e��ͬ��Ԫ�أ�");
				getchar();
			}
			getchar(); 
			break;
		case 8:
			if (List == NULL)
				printf("��ǰû�л��\n");
			else
			{
				printf("����������Ԫ��cur��");
				scanf("%d", &cur);
				if (PriorElem(*(List->L), cur, &pre_e) != ERROR)
					printf("%d��ǰ������Ԫ��Ϊ%d", cur, pre_e);
				getchar();
			}
			getchar(); 
			break;
		case 9:
			if (List == NULL)
				printf("��ǰû�л��\n");
			else
			{
				printf("����������Ԫ��cur��");
				scanf("%d", &cur);
				if (NextElem(*(List->L), cur, &next_e) != ERROR)
					printf("%d�ĺ������Ԫ��Ϊ%d", cur, next_e);
				getchar();
			}
			getchar(); 
			break;
		case 10:
			if (List == NULL)
				printf("��ǰû�л��\n");
			else
			{
				printf("������Ҫ�����Ԫ��e��");
				scanf("%d", &e);
				printf("��������Ҫ�����λ��i��");
				scanf("%d", &i);
				if (ListInsert(List->L, i, e) == OK)
					printf("����Ԫ�سɹ���");
				else
					printf("����Ԫ��ʧ�ܣ�");
				getchar();
			}
			getchar(); 
			break;
		case 11:
			if (List == NULL)
				printf("��ǰû�л��\n");
			else
			{
				printf("������Ҫɾ����Ԫ�ص�λ��i��");
				scanf("%d", &i);
				if (ListDelete(List->L, i, &e) == OK)
					printf("λ��Ϊ%d��Ԫ�ص�ֵΪ%d\nɾ��Ԫ�سɹ���", i, e);
				else
					printf("ɾ��Ԫ��ʧ�ܣ�");
				getchar();	
			}
			getchar(); 
			break;
		case 12:
			if (List == NULL)
				printf("��ǰû�л��\n");
			else 
				ListTrabverse(*(List->L));
			getchar(); 
			break;
		case 13:
			if (List == NULL)
				printf("��ǰû�л��,���ܽ����ļ���ȡ��\n");
			else
				SaveList(fp,*List->L,filename);
			getchar(); 
			break;
		case 14:
			if (List == NULL)
				printf("��ǰû�л��,���ܽ����ļ���ȡ��\n");	
			else
				LoadList(fp,List->L,filename);
			getchar();
			break;
		case 15:
			if (head.next == NULL)
				printf("û�пɲ����ı�");
			MultiListTrabverse(&head);
			getchar();	
			break;
		case 16:
			if (head.next == NULL)
			{
				printf("û�пɲ����ı�");
				getchar();	getchar();
				break;
			}
			if(MultiListTrabverse(&head)==NULL)
				break;
			List=ExList(&head);
			break;
		case 0:
			break;
		default:
			printf("����ѡ������Ч�����롣\n");
			getchar();
		}
		updata(&head);
	}
	printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
	getchar();	
}//end of main()
/******************
*�������ƣ�LoadList
*�����������ļ�ָ�룬���Ա�L,�ļ���filename[30] 
*�������ܣ����ݼ��أ�Ϊ���Ա�����Ԫ�ء�
*����ֵ�����سɹ�����OK������ʧ�ܷ���ERROR
******************/
status LoadList(FILE *fp,SqList *L,char filename[30])
{
	int e1,e;
	printf("������Ҫ�������ݵ��ļ���: ");
	gets(filename);
	if ((fp=fopen(filename, "r+")) == NULL)
	{
		printf("�ļ���ʧ�ܣ�\n");
		return ERROR; 
	}
	while (fscanf(fp, "%d", &e1) != EOF)
	{
		L->length = 0;
		printf("����%d\n",e1);
		for (int i = 0; i < e1; )
		{
			fscanf(fp, "%d ", &e);
			i++;
			printf("�����%d��Ԫ��%d...\n", i, e);
			ListInsert(L, i, e);
		}
	}
	printf("�������.");
	fclose(fp);
	return OK;
}
/******************
*�������ƣ�SaveList
*�����������ļ�ָ�룬���Ա�L,�ļ���filename[30] 
*�������ܣ���L�е����ݱ��浽fpָ��ָ����ļ���
*����ֵ��OK
******************/ 
status SaveList(FILE *fp,SqList L,char filename[30])
{
	printf("������Ҫд����ļ���: "); 
	gets(filename);
	if ((fp=fopen(filename, "w+"))== NULL)
	{
		printf("�ļ���ʧ�ܡ�");
		getchar();
		return ERROR;
	}
	for (int i = -1; i < L.length; i++)
	{
		if (i == -1)
		{
			fprintf(fp, "%d ", L.length);
			continue;
		}
		fprintf(fp, "%d ", *(L.elem + i));  
	}
	printf("�ļ�д��ɹ���");
	fclose(fp);	
	return OK;
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
	scanf("%d",&num);
	MultiList * List = head;
	for (int i = 0;i<num&&List!=NULL; i++)
		List = List->next;
	if(List==NULL)
	{
		printf("����ı��벻�Ϸ���\n");	
		getchar();getchar();
	}
	return List;
}
/******************
* �������ƣ�updata
* ������������
* �������ܣ����¶���е�ÿ�����Ӧ�ı�ţ������л��� 
* ����ֵ����
*******************/
void updata(MultiList *head)
{
	MultiList *p = head->next;
	int i = 0;
	while (p)
	{
		i++;
		p->num = i;
		p = p->next;
	}
}
/******************
* �������ƣ�show
* ������������
* �������ܣ���ʾα�˵�����
* ����ֵ����
*******************/
void show()
{
	system("cls");
	printf("\n\n");
	printf("      Menu for Linear Table On Sequence Structure \n");
	printf("-------------------------------------------------\n");
	printf("    	  1. IntiaList      9. NextElem\n");
	printf("    	  2. DestroyList    10.ListInsert\n");
	printf("    	  3. ClearList      11.ListDelete\n");
	printf("    	  4. ListEmpty      12.ListTrabverse\n");
	printf("    	  5. ListLength     13.SaveList\n");
	printf("    	  6. GetElem        14.LoadList\n");
	printf("	  7. LocateElem     15.MultiListTrabverse\n");
	printf("	  8. PriorElem      16.ExList\n");
	printf("    	  0. Exit\n");
	printf("-------------------------------------------------\n");
	printf("    ��ѡ����Ĳ���[0~16]:");
}

/******************
*��������:InitiaList
*��������:��ʼ����L������ָ��elem�����ñ�ΪL������󳤶�ΪLIST_INIT_SIZE
*�������:L���ָ��SqList��ָ��
*�������:����ʼ�����Lָ��
*������ֵ:�����ѱ���ʼ��ʱ����ERROR,
*		 �����ʼ����ɹ�����SUCCESS
*����˵��:��Ҫ��L��elem��Ա�ÿղ��ܳ�ʼ��L
******************/
status IntiaList(SqList *L)
{
	if(L->elem!=NULL)
		return ERROR; 
	L->elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (L->elem == NULL)//�����ڴ�ʧ�� 
		return ERROR;
	L->length = 0;//�ձ���Ϊ0 
	L->listsize = LIST_INIT_SIZE;//��ʼ�洢���� 
	return OK;
}

/******************
* �������ƣ�InitiaList2
* ����������MultiList��ͷָ��head������ָ��List
* �������ܣ�����һ���յ����Ա�
* ����ֵ���ɹ����췵��OK�����򷵻�ERROR
******************/
status InitiaList2(MultiList *head,MultiList **List)
{
	*List = head;
	MultiList *q = *List;
	while (*List)
	{
		q = *List;
		(*List) = (*List)->next;
	}
	q->next = (MultiList *)malloc(sizeof(MultiList));
	q->next->L= (SqList *)malloc(sizeof(SqList));
	
	*List = q->next;
	(*List)->L->elem = NULL;
	if (IntiaList((*List)->L) == ERROR)
		return ERROR;
	(*List)->next = NULL;
	return OK;
}

/******************
*��������:DestroyList
*��������:�ͷű�L��elemָ�룬ʹelemָ���ÿ�
*�������:L���ָ��SqList��ָ��
*�������:��
*������ֵ:������δ������ʱ����ERROR,�������ٳɹ�����OK
*����˵��:��
******************/
status DestroyList(SqList *L)
{
	if (L->elem == NULL)
		return ERROR;
	free(L->elem);
	free(L);
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
	DestroyList(p->L);
	free(p);
	*List = NULL;
	return OK;
}

/******************
*�������ƣ�ClearList
*�������������Ա�L�ĵ�ַ
*�������ܣ��������Ա�
*����ֵ���ɹ��ÿշ���OK�����򷵻�ERROR
******************/
status ClearList(SqList *L)
{
	if (L->elem)
	{
		free(L->elem); 
		L->length = 0;
		return OK;
	}
	return ERROR;
}

/******************
*�������ƣ�ListEmpty
*�������������Ա�L
*�������ܣ��ж����Ա��Ƿ�Ϊ��
*����ֵ����LΪ�ձ��򷵻�OK�����򷵻�ERROR
******************/
status ListEmpty(SqList L)
{
	if (L.elem)
	{
		if (L.length == 0)
		{
			printf("�ñ�Ϊ�ձ�\n");
			return OK;
		}
		else
		{
			printf("�ñ�Ϊ�ձ�\n");
			return ERROR;
		}
	}
	else
	{
		printf("�����ڻ��\n");
		return ERROR;
	}
}

/******************
*�������ƣ�ListLength
*�������������Ա�L
*�������ܣ��������Ա�L������Ԫ�ظ�����
*����ֵ���ɹ�����L������Ԫ�ظ�����ʧ�ܷ���ERROR
******************/
int ListLength(SqList L)
{
	if (L.elem)
		return L.length;
	return ERROR;
}

/******************
*�������ƣ�GetElem
*�������������Ա�L��eΪ��i�����ݵĵ�ַ��
*�������ܣ����Ҳ���ʾL�е�i��Ԫ�ص�ֵ��
*����ֵ���ɹ��򷵻ص�i��Ԫ�ص�ֵ�����򷵻�ERROR
******************/
status GetElem(SqList L, int i, ElemType *e)
{
	if (L.length == 0)
	{
		printf("�ñ�Ϊ�ձ�����ʧ�ܡ�\n");
		return ERROR;
	}
	if (i < 1 || i>L.length)
	{
		printf("iֵ���Ϸ���i��ȡֵ��ΧӦΪ1<=i<=%d��\n", ListLength(L));
		return ERROR;
	}
	*e = L.elem[i - 1];
	return *e;
}

/******************
*�������ƣ�LocateElem
*�������������Ա�L����Աȵ�Ԫ��ֵ��
*�������ܣ�����L����e��ͬ�������ڵ�λ��λ���1��ʼ
*����ֵ���ɹ��򷵻ص�һ����e��ͬ�����ݵ�λ�򣬲������򷵻�0�������������ERROR
******************/
status LocateElem(SqList L, ElemType e)
{
	int i = 0;
	if (L.length == 0)
		return ERROR;
	while (L.elem[i] != e&&i<L.length) {
		i++;
	}
	if (i >= L.length)
		return ERROR;
	else
		return i + 1;
}

/******************
*�������ƣ�PriorElem
*�������������Ա�L�����ҵ�����cur,ǰ��pre_e��
*�������ܣ�����L����cur��ͬ�ĵ�һ�����ݣ���������ǰ��
*����ֵ���ɹ��򷵻���cur��ͬ�ĵ�һ�����ݣ����������һ��ǰ��������ǰ���Լ���������򷵻�ERROR
******************/
status PriorElem(SqList L, ElemType cur, ElemType *pre_e)
{
	int i;
	i = LocateElem(L, cur);
	if(i==ERROR||i==0)
	{
		printf("%d ���ǻ���е�Ԫ��\n",cur);
		return ERROR;
	}
	else if (i>1) {
		*pre_e = L.elem[i - 2];
		return OK;
	}
	else if (i == 1)
	{
		printf("%d is the first letter has no prior_elem\n", cur);
		return ERROR;
	}

}

/******************
*�������ƣ�NextElem
*�������������Ա�L�����ҵ�����cur_e,����next_e��
*�������ܣ�����L����cur_e��ͬ�ĵ�һ�����ݣ������������
*����ֵ���ɹ��򷵻���cur_e��ͬ�ĵ�һ�����ݣ�����������������޺����Լ���������򷵻�ERROR
******************/
status NextElem(SqList L, ElemType cur, ElemType *next_e)
{
	int i;
	i = LocateElem(L, cur);
	if(i==ERROR||i==0)
	{
		printf("%d ���ǻ���е�Ԫ��\n",cur);
		return ERROR;
	}
	else if (i>0) {
		if (i < L.length) {
			*next_e = L.elem[i];
			return OK;
		}
		else if(i==L.length)
		{
			printf("%d is the last letter has no next_elem��\n", cur);
			return ERROR;
		}
	}
	else
		return ERROR;
}

/******************
*�������ƣ�ListInsert
*�������������Ա�L�ĵ�ַ�������λ��i�����������Ԫ��e��
*�������ܣ���L�ĵ�i��λ��֮ǰ�����µ�����Ԫ��e�����Ѳ��������շ����������������Ŀռ䡣
*����ֵ���ɹ����뷵��OK�����򷵻�ERROR
******************/
status ListInsert(SqList * L, int i, ElemType e)
{
	if (i<1 || i>L->length + 1)
	{
		printf("iֵ���Ϸ�������ʧ�ܡ�\n");
		return ERROR;
	}

	if (L->length >= L->listsize)
	{
		ElemType* newbase = (ElemType*)realloc(L->elem, (L->listsize + LISTINCREMENT));
		if (!newbase) return ERROR;
		L->elem = newbase;
		L->listsize = L->listsize + LISTINCREMENT;
	}
	ElemType*q = &(L->elem[i - 1]);
	ElemType*p = &(L->elem[L->length - 1]);
	for (; p >= q; p--)
		*(p + 1) = *p;
	*q = e;
	L->length++;
	return OK;
}

/******************
*�������ƣ�ListDelete
*�������������Ա�L�ĵ�ַ��ɾ����λ��i��ָ��e�ĵ�ַ��
*�������ܣ�ɾ��L�ĵ�i������Ԫ�أ���e������ֵ��
*����ֵ���ɹ�ɾ������OK�����򷵻�ERROR
******************/
status ListDelete(SqList * L, int i, ElemType * e)
{
	if (i<1 || i>L->length)
		return ERROR;
	ElemType *p;
	p = &L->elem[i - 1];
	*e = *p;
	ElemType * q;
	q = L->elem + L->length - 1;
	for (p++; p <= q; p++)
		*(p - 1) = *p;
	L->length--;
	return OK;
}

/******************
*�������ƣ�ListTrabverse
*�������������Ա�L
*�������ܣ�������ʾ���Ա��е�ÿ��Ԫ�ء�
*����ֵ���ɹ������������Ա�ĳ��ȣ����򷵻�ERROR
******************/
status ListTrabverse(SqList L) {
	int i;
	printf("-----------all elements -----------------------\n");
	for (i = 0; i<L.length; i++) printf("%3d ", L.elem[i]);
	printf("\n------------------ end ------------------------\n");
	if (L.length == 0)
	{
		printf("���Ա��ǿձ�\n");
		return ERROR;
	}
	return L.length;
}

/******************
*�������ƣ�MultiListTrabverse
*����������MultiListͷָ��head
*�������ܣ�������ʾÿһ�����Ա�ı��롢���Լ����Ա��е�ÿ��Ԫ�ء�
*����ֵ���ɹ������������Ա�ĳ��ȣ����򷵻�ERROR
******************/
status MultiListTrabverse(MultiList *head)
{
	MultiList *p = head->next;
	while (p)
	{
		printf("������%d\t���ȣ�%d\n", p->num, p->L->length);
		ListTrabverse(*p->L);
		p = p->next;
	}
	return OK;
}
