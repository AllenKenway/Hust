#include<stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include<string.h>

#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
#define FALSE -1 
#define OK 1
#define ERROR -2 
#define TRUE 1
#define INFEASTABLE -1
#define OVERFLOW -2

typedef int Key;				//����ؼ�������Ϊint 
typedef struct TElemType {
	Key i;						//�ؼ��֣���ϵͳ������ȫ�������ж�Ӧ��λ�� 
	char c;						//�ַ������� 
}TElemType;
typedef struct BiTNode {
	TElemType data;				//����������е������� 
	BiTNode *lchild, *rchild;	//���Һ���ָ��
}BiTNode;
typedef struct BiTree { 
	char name[20];				//������������ 
	BiTNode* HeadNode; 			//�����������
}BiTree;
typedef struct Forest {
	BiTree *elem;				//������ 
	int length;					//�������ĸ��� 
	int listsize;				 
}Forest;

//---------------------------------------���еĶ���ͻ������������ڲ�α���������---------------------------------------// 
struct LinkQueueNode {
	BiTNode *data;
	struct LinkQueueNode *next;
};
struct LKQueue {
	LinkQueueNode*front, *rear;
};
/******************
�������ƣ�InitQueue
��������������LQ
�������ܣ���ʼ��һ������ 
����ֵ����
*******************/
void InitQueue(LKQueue *LQ)
{
	LinkQueueNode*p;
	p = (LinkQueueNode*)malloc(sizeof(LinkQueueNode));
	LQ->front = p;
	LQ->rear = p;
	LQ->front->next = NULL;
}
/******************
�������ƣ�EmptyQueue
��������������LQ
�������ܣ��ж϶����Ƿ�Ϊ�� 
����ֵ��������Ϊ�շ���1�����򷵻�0 
*******************/
int EmptyQueue(LKQueue*LQ)
{
	if (LQ->front == LQ->rear)
		return 1;
	else
		return 0;
}
/******************
�������ƣ�EnQueue
��������������LQ�����T 
�������ܣ���T���������β�� 
����ֵ����
*******************/
void EnQueue(LKQueue*LQ, BiTNode*T)
{
	LinkQueueNode *p;
	p = (LinkQueueNode *)malloc(sizeof(LinkQueueNode));
	p->data = T;
	p->next = NULL;
	LQ->rear->next = p;
	LQ->rear = p;
} 
/******************
�������ƣ�OutQueue
��������������LQ 
�������ܣ������е�һ��Ԫ�س��� 
����ֵ���ɹ�����1��ʧ�ܼ�������Ϊ��ʱ����0 
*******************/
int OutQueue(LKQueue*LQ)
{
	LinkQueueNode *p;
	if (EmptyQueue(LQ))
	{
		return 0;
	}
	else
	{
		p = LQ->front->next;
		LQ->front->next = p->next;
		if (p->next == NULL)
			LQ->rear = LQ->front;
		free(p);
		return 1;
	}
}
/******************
�������ƣ�GetHead
��������������LQ 
�������ܣ����ض��е�һ��Ԫ��
����ֵ�����ص�һ��Ԫ�أ�������Ϊ���򷵻�NULL 
*******************/
BiTNode *GetHead(LKQueue *LQ)
{
	LinkQueueNode *p;
	BiTNode *T=NULL;
	if (EmptyQueue(LQ))
		return T;
	else
	{
		p = LQ->front->next;
		return p->data;
	}
}

//---------------------------------------���ܺ���������---------------------------------------// 
void show(BiTree*F);//��ʾα�˵� 
void updata(BiTNode *F);//����Ӧ��λ�ø�ֵ���ؼ��� 
int InitBiTree(Forest *L);//��ʼ��һ���ն����� 
int DestroyBiTree(Forest L,BiTree *F);//���ٶ����� 
int DestroyBiTree2(BiTNode *T);

BiTNode *CreateBiTree(char*definition);//��definition���������ɶ����� 
int PreCreateBiTree(BiTNode **T,char*definition,int *i);

int ClearBiTree(BiTNode *T);//��ն����� 
int BiTreeEmpty(BiTNode T);//�ж϶������Ƿ�Ϊ�� 
int BiTreeDepth(BiTNode *T);//���ض���������� 
BiTNode* Root(BiTNode *T);//���ض������ĸ���� 
BiTNode* Value(BiTNode *T,Key e);//���عؼ���Ϊe�Ľ�� 
int Assign(BiTNode *T,Key e,char c);//�޸Ĺؼ���Ϊe�Ľ�� 

BiTNode* Parent(BiTNode *T,Key e);//���عؼ���Ϊe�Ľ���˫�׽�� 
BiTNode* LeftChild(BiTNode*T,Key e);//���عؼ���Ϊe�Ľ������ӽ�� 
BiTNode* RightChild(BiTNode*T,Key e);//���عؼ���Ϊe�Ľ����Һ��ӽ�� 
BiTNode* LeftSibling(BiTNode*T,Key e);//���عؼ���Ϊe�Ľ������ֵܽ�� 
BiTNode* RightSibling(BiTNode*T,Key e);//���عؼ���Ϊe�Ľ������ֵܽ�� 

int InsertChild(BiTNode*T, Key e, int LR,BiTNode*p);//�������� 
void change(BiTNode *T);//��������������Ĺ��򽫶�������Ϊ������Ϊ�յĶ����� 
int DeleteChild(BiTNode*T, Key e, int LR);//ɾ������ 

int PreOrderTraverse(BiTNode *T);//������� 
int InOrderTraverse(BiTNode *T);//������� 
int PostOrderTraverse(BiTNode *T);//������� 
int LevelOrderTraverse(BiTNode *T);//��α��� 

int SaveData(FILE *fp, BiTNode*T, char filename[30]);//�������� 
int SaveData1(FILE *fp, BiTNode*T, char filename[30]);
int LoadData(FILE *fp, BiTNode**T, char filename[30]);//�������� 
int ForestTraverse(Forest L);//����ɭ�� 
BiTree *ExBiTree(Forest L, char name[20]);//�л��� 

int main()
{
	Forest L;
	L.elem = (BiTree *)malloc(LIST_INIT_SIZE * sizeof(BiTree));  
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
	
	BiTree *F=NULL,*F1;//FΪ����ָ�룬F1���ڽ��շ��ص������ 
	BiTNode *T;//���ڽ��շ��صĶ��������ָ�� 
	
	FILE  *fp = NULL;//�ļ�ָ�� 
	char filename[30];//�洢�ļ���

	int op = 1;//����ѡ�� 
	char s[100];//�洢¼����ַ����������ɶ������������ڴ洢����Ķ��������� 
	Key e;char a;//��������ʱ���� 
	int LR;//����ҵ�ѡ�� 

	while (op)
	{
		show(F);
		scanf("%d", &op); getchar();
		switch (op)
		{
			case 0:
				printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
				getchar();	
				break;
			case 1:
				if (InitBiTree(&L)== OK)
				{
					F=&(L.elem[L.length-1]);
					printf("����һ���ն������ɹ���\n");					
				}
				else
					printf("����һ���ն�����ʧ�ܣ�\n");
				getchar();
				break;
			case 2:
				if (DestroyBiTree(L,F)== OK)
				{
					F=NULL;
					printf("���ٶ������ɹ���\n");					
				}
				else
					printf("���ٶ�����ʧ�ܣ�\n");
				getchar();
				break;
			case 3:
				if (F == NULL)
					printf("��ǰû�л����\n");
				else
				{
					if (F->HeadNode->lchild != NULL)
						printf("��ǰ������������ݣ������������ɣ�");
					else
					{
						printf("����������������У�ÿһ��Ԫ�ض�Ϊchar����,��Ϊ��������#����\n");
						fgets(s, 100, stdin);
						F->HeadNode->lchild = CreateBiTree(s);
						if (s[0] != ' '&&s[0]!='#'&&F->HeadNode->lchild == NULL)
							printf("����������ʧ�ܣ���ȷ������������Ƿ���һ����ȷ������������У�");
						else
							printf("�����������ɹ���");
					}
				}
				getchar();
				break;
			case 4:
				if (F == NULL)
					printf("��ǰû�л����\n");
				else if (ClearBiTree(F->HeadNode) == OK)
					printf("��������ճɹ���");
				else
					printf("���������ʧ�ܣ�");
				getchar();
				break;
			case 5:
				if (F == NULL)
					printf("��ǰû�л����\n");
				else if (BiTreeEmpty(*(F->HeadNode)) == OK)
					printf("��ǰ���Ϊ�ն�������");
				else
					printf("��ǰ������ǿն�������");
				getchar();
				break;
			case 6:
				if (F == NULL)
					printf("��ǰû�л����\n");
				else
					printf("�����������Ϊ%d��",BiTreeDepth(F->HeadNode->lchild));
				getchar();
				break;
			case 7:
				if (F == NULL)
					printf("��ǰû�л����\n");
				else if (F->HeadNode->lchild == NULL)
					printf("�����Ϊ�գ��û��Ϊ�ն�������");
				else
					printf("�����Ĵ�ŵ�����Ϊ��%c��", Root(F->HeadNode)->data.c);
				getchar();
				break;
			case 8:
				if (F == NULL)
					printf("��ǰû�л����\n");
				else  if (F->HeadNode->lchild == NULL)
					printf("�û��Ϊ�ն����������ܽ��в��ң�");
				else
				{
					printf("������Ҫ���ҵ����ݵĹؼ���:");scanf("%d", &e);getchar();
					T = Value(F->HeadNode->lchild, e);
					if (T!=NULL)
						printf("�ؼ���Ϊ%d������Ϊ%c��", e, T->data.c);
					else
						printf("û���ҵ����иùؼ��ֵĽ�㣡");
				}	
				getchar(); 
				break;
			case 9:
				if (F == NULL)
					printf("��ǰû�л����\n");
				else  if(F->HeadNode->lchild==NULL)
					printf("�û��Ϊ�ն��������޷������޸ģ�");
				else
				{
					printf("������Ҫ�޸ĵ����ݵĹؼ���:");scanf("%d", &e);getchar();
					printf("������Ҫ�޸ĺ������:");scanf("%c", &a);getchar();
					if (Assign(F->HeadNode->lchild, e, a) == OK)
						printf("�޸ĳɹ���");
					else
						printf("û���ҵ����иùؼ��ֵĽ�㣡");	 
				}
				getchar();
				break;
			case 10:
				if (F == NULL)
					printf("��ǰû�л����\n");
				else  if(F->HeadNode->lchild==NULL)
					printf("�û��Ϊ�ն��������޷����в��ң�");
				else
				{
					printf("������Ҫ���ҵ����ݵĹؼ���:"); scanf("%d", &e);	getchar(); 
					if (e == 1)
						printf("�ùؼ��ֶ�Ӧ���ݽ��Ϊ���ڵ㣬��˫�׽�㣡");
					else
					{
						T = Parent(F->HeadNode->lchild, e);
						if (T != NULL)
							printf("�ؼ���Ϊ%d�����ݵ�˫�׽��Ĺؼ��֣�%d    ���ݣ�%c��", e, T->data.i, T->data.c);
						else
							printf("û���ҵ����иùؼ��ֵĽ��,����ʧ�ܣ�");
					}
				}
				getchar();
				break;
			case 11:
				if (F == NULL)
					printf("��ǰû�л����\n");
				else  if(F->HeadNode->lchild==NULL)
					printf("�û��Ϊ�ն��������޷����в��ң�");
				else
				{
					printf("������Ҫ���ҵ����ݵĹؼ���:"); scanf("%d", &e);	getchar();
					T=LeftChild(F->HeadNode->lchild, e);
					if (T == NULL)
						printf("û���ҵ����иùؼ��ֵĽ����Ǻ��иùؼ��ֵĽ��û�����ӽ�㣡");
					else
						printf("�ؼ���Ϊ%d�Ľ������ӽ��Ĺؼ��֣�%d    ���ݣ�%c��", e,T->data.i,T->data.c);
				}
				getchar();
				break;
			case 12:
				if (F == NULL)
					printf("��ǰû�л����\n");
				else  if(F->HeadNode->lchild==NULL)
					printf("�û��Ϊ�ն��������޷����в��ң�");
				else
				{
					printf("������Ҫ���ҵ����ݵĹؼ���:"); scanf("%d", &e);	getchar();
					T = RightChild(F->HeadNode->lchild, e);
					if (T == NULL)
						printf("û���ҵ����иùؼ��ֵĽ����Ǻ��иùؼ��ֵĽ��û���Һ��ӽ�㣡");
					else
						printf("�ؼ���Ϊ%d�Ľ����Һ��ӽ��Ĺؼ��֣�%d    ���ݣ�%c��", e, T->data.i, T->data.c);
				}
				getchar();
				break;
			case 13:
				if (F == NULL)
					printf("��ǰû�л����\n");
				else  if(F->HeadNode->lchild==NULL)
					printf("�û��Ϊ�ն��������޷����в��ң�");
				else
				{
					printf("������Ҫ���ҵ����ݵĹؼ���:"); scanf("%d", &e);	getchar();
					if (e == 1)printf("�ùؼ��ֶ�Ӧ���ݽ��Ϊ���ڵ㣬�����ֵܽ�㣡");
					else
					{
						T = LeftSibling(F->HeadNode->lchild, e);
						if (T == NULL)
							printf("û���ҵ����иùؼ��ֵĽ�㣡");
						else if (T->data.i == e)
							printf("���иùؼ��ֵĽ��Ϊĳһ�������ӽ�㣬�����ֵܽ�㣡");
						else
							printf("�ؼ���Ϊ%d�����ݵ����ֵܽ��Ĺؼ��֣�%d    ���ݣ�%c��", e, T->data.i, T->data.c);
					}
				}
				getchar();
				break;
			case 14:
				if (F == NULL)
					printf("��ǰû�л����\n");
				else  if(F->HeadNode->lchild==NULL)
					printf("�û��Ϊ�ն��������޷����в��ң�");
				else
				{
					printf("������Ҫ���ҵ����ݵĹؼ���:"); scanf("%d", &e);	getchar();
					if (e == 1)printf("�ùؼ��ֶ�Ӧ���ݽ��Ϊ���ڵ㣬�����ֵܽ�㣡");
					else
					{
						T = RightSibling(F->HeadNode->lchild, e);
						if (T == NULL)
							printf("û���ҵ����иùؼ��ֵĽ�㣡");
						else if (T->data.i == e)
							printf("���иùؼ��ֵĽ��Ϊĳһ�����Һ��ӽ�㣬�����ֵܽ�㣡");
						else
							printf("�ؼ���Ϊ%d�����ݵ����ֵܽ��Ĺؼ��֣�%d    ���ݣ�%c��", e, T->data.i, T->data.c);
					}
				}
				getchar();
				break;
			case 15:
				if (F == NULL)
					printf("��ǰû�л����\n");
				else
				{
					printf("����������������������У�ÿһ��Ԫ�ض�Ϊchar����,��Ϊ��������#����\n");
					fgets(s, 30, stdin);
					if (s[0] == '\n')
						printf("δ���������ַ�������������ʧ�ܣ�");
					else if(s[0]=='#')
					{
						F->HeadNode->lchild == NULL;
						printf("�����������ɹ�������Ϊ����,�޷����в��룡");	
					}
					else
					{
						T = CreateBiTree(s);
						if (s[0] != ' '&&T == NULL)
							printf("����������ʧ�ܣ���ȷ������������Ƿ���һ����ȷ������������У�");
						else
						{
							printf("�����������ɹ���\n");
							printf("��������Ҫ����λ�õ�˫�׽��Ĺؼ���(������˫�׽�㶨��Ϊ��ͷ���)��"); scanf("%d", &e);	getchar();
							if(e!=0)
							{
								printf("��0���������������1���������������������LR��ֵ��"); scanf("%d", &LR); getchar();
							}	
							if(InsertChild(F->HeadNode, e,LR,T)==OK)
								printf("����ɹ���");
							else
								printf("����ʧ�ܣ�");							
						}
					}
				}
				getchar();
				break;
			case 16:
				if (F == NULL)
					printf("��ǰû�л����\n");
				else if (DeleteChild(F->HeadNode, e, LR) == OK)
					printf("ɾ���ɹ���");
				else
					printf("ɾ��ʧ�ܣ�");
				getchar();
				break;
			case 17:
				if (F == NULL)
					printf("��ǰû�л����");
				else if (F->HeadNode->lchild == NULL)
					printf("����Ϊ�ն�������");
				else
					PreOrderTraverse(F->HeadNode->lchild);
				getchar(); 
				break;
			case 18:
				if (F == NULL)
					printf("��ǰû�л����");
				else if (F->HeadNode->lchild == NULL)
					printf("����Ϊ�ն�������");
				else
					InOrderTraverse(F->HeadNode->lchild);
				getchar(); 
				break;
			case 19:
				if (F == NULL)
					printf("��ǰû�л����");
				else if (F->HeadNode->lchild == NULL)
					printf("����Ϊ�ն�������");
				else
					PostOrderTraverse(F->HeadNode->lchild);
				getchar();
				break;
			case 20:
				if (F == NULL)
					printf("��ǰû�л����");
				else if (F->HeadNode->lchild == NULL)
					printf("����Ϊ�ն�������");
				else
					LevelOrderTraverse(F->HeadNode->lchild);
				getchar();
				break;
			case 21:
				if (F == NULL)
					printf("��ǰû�л����\n");
				else if (SaveData(fp,F->HeadNode->lchild,filename)== OK)
					printf("����д���ļ��ɹ���");
				else
					printf("����д���ļ�ʧ�ܣ�");
				getchar();
				break;
			case 22:
				if (F == NULL)
					printf("��ǰû�л����\n");
				else if (LoadData(fp, &(F->HeadNode->lchild), filename) == OK)
					printf("¼�����ݳɹ���");
				else
					printf("¼������ʧ�ܣ�");
				getchar();
				break;
			case 23:
				if (L.elem == NULL)
					printf("��ǰû�л����\n");
				else	
				{
					ForestTraverse(L);
					printf("������Ҫ�л��ı�����֣�"); scanf("%s", &s); getchar();
					F1=ExBiTree(L, s);
					if (F1 == NULL)
						printf("��������ֲ����ڣ�\n");
					else
					{
						F=F1;
						printf("�л��ɹ���");	
					}
				}
				getchar();
				break;
			default:
				printf("����ѡ������Ч�����룡\n");
				getchar();
		}
		if(F!=NULL)
			if(F->HeadNode!=NULL)
				updata(F->HeadNode->lchild);
	}
	return 0;
}
					    
/******************
�������ƣ�ForestTraverse
�������������ɭ�ֵ�˳��� 
�������ܣ�����ȫ������
����ֵ���ɹ�����OK�����򷵻�ERROR
*******************/
int ForestTraverse(Forest L)
{
	int i;
	for (i = 0;i < L.length;i++) 
	{
		printf("�������֣�%s\n", L.elem[i].name);
		if(L.elem[i].HeadNode->lchild==NULL)
			printf("����Ϊ������");
		else
			PreOrderTraverse(L.elem[i].HeadNode->lchild);
		printf("\n\n"); 		
	}
	printf("����������");
	return OK;
}
/******************
�������ƣ�ExBiTree
�������������ɭ�ֵ�˳��� ��Ҫ�л����������� 
�������ܣ��л�������
����ֵ���л��ɹ��򷵻��л���ɭ�ֽṹ�Ľ�㣬���򷵻�NULL
*******************/
BiTree *ExBiTree(Forest L, char name[20])
{
	int i;
	for (i = 0;i < L.length;i++) 
	{
		if (strcmp(L.elem[i].name,name) == 0) 
			break;
	}
	if (i+1>L.length) 
	{
		printf("�����������ڣ�");
		return NULL;
	}
	else
		return &(L.elem[i]);
}
/******************
�������ƣ�LoadData
�����������ļ�ָ�룬�������ı�ͷ���T,�ļ���filename[30]
�������ܣ���������
����ֵ���ɹ�����OK��ʧ�ܷ���ERROR
*******************/
int LoadData(FILE *fp, BiTNode**T, char filename[30])
{
	printf("������Ҫ�������ݵ��ļ���: ");
	scanf("%s", filename);getchar();
	if ((fp=fopen(filename, "r+")) == NULL)
	{
		printf("�ļ���ʧ�ܣ�\n");
		return ERROR;
	}
	char *temp;
	fgets(temp, 1024, fp);
	if (*T == NULL)
	{
		*T=CreateBiTree(temp);
		if((*T==NULL&&temp=='\0')||temp!='\0'&&*T!=NULL)
		{
			printf("������ϣ�");
			fclose(fp);
			return OK;		
		}
	}
	if (ClearBiTree((*T)) == ERROR)
		return ERROR;
	*T=CreateBiTree(temp);
	if((*T==NULL&&temp=='\0')||temp!='\0'&&*T!=NULL)
	{
		printf("������ϣ�");
		fclose(fp);
		return OK;		
	}
	fclose(fp);
	return ERROR;
}
/******************
�������ƣ�SaveData
�����������ļ�ָ�룬�������ı�ͷ���T,�ļ���filename[30]
�������ܣ���������
����ֵ���ɹ�����OK��ʧ�ܷ���ERROR
*******************/
int SaveData(FILE *fp, BiTNode*T, char filename[30])
{
	printf("������Ҫд����ļ���: "); scanf("%s", filename);getchar();
	if ((fp=fopen(filename, "w")) ==NULL)
	{
		printf("�ļ���ʧ�ܣ�");
		return ERROR;
	}
	if (SaveData1(fp, T, filename) == OK)
	{
		fclose(fp);
		return OK;
	}
	fclose(fp);
	return ERROR;
}
/******************
�������ƣ�SaveData1
�����������ļ�ָ�룬�������ı�ͷ���T,�ļ���filename[30]
�������ܣ�����������������ļ�filename������д�����ݵĹؼ��ֺ��ַ�
����ֵ���ɹ�����OK��ʧ�ܷ���ERROR
*******************/
int SaveData1(FILE *fp, BiTNode*T, char filename[30])
{
	if (T) {
		fprintf(fp, "%c",T->data.c);
		SaveData1(fp, T->lchild, filename);
		SaveData1(fp, T->rchild, filename);
	}
	else
		fprintf(fp, "%c",'#');
	return OK;
}	  
/******************
�������ƣ�LevelOrderTraverse
����������ָ��������ĸ�����ָ��F->HeadNode->lchild
�������ܣ��������������
����ֵ���ɹ�����OK��ʧ�ܷ���ERROR
*******************/	
int LevelOrderTraverse(BiTNode *T)
{
	LKQueue*Q;
	BiTNode *p;
	InitQueue(Q);
	if (T!= NULL)
	{
		EnQueue(Q, T);
		while (!EmptyQueue(Q))
		{
			p = GetHead(Q);
			OutQueue(Q);
			if(p==NULL)
				putchar('#');
			else
				printf("%c",p->data.c);
			if (p->lchild != NULL)
				EnQueue(Q, p->lchild);
			if (p->rchild != NULL)
				EnQueue(Q, p->rchild);
		}
	}
}
/******************
�������ƣ�PostOrderTraverse
����������ָ��������ĸ�����ָ��F->HeadNode->lchild
�������ܣ��������������
����ֵ���ɹ�����OK��ʧ�ܷ���ERROR
*******************/
int PostOrderTraverse(BiTNode *T)
{
	if (T)
	{
		PostOrderTraverse(T->lchild);
		PostOrderTraverse(T->rchild);
		printf("%c", T->data.c);
	}
	else
		putchar('#');
	return OK;
}
/******************
�������ƣ�InOrderTraverse
����������ָ��������ĸ�����ָ��F->HeadNode->lchild
�������ܣ��������������
����ֵ���ɹ�����OK��ʧ�ܷ���ERROR
*******************/
int InOrderTraverse(BiTNode *T)
{
	if (T)
	{
		InOrderTraverse(T->lchild);
		printf("%c", T->data.c);
		InOrderTraverse(T->rchild);
	}
	else
		putchar('#');
	return OK;
}
/******************
�������ƣ�PreOrderTraverse
����������ָ��������ĸ�����ָ��F->HeadNode->lchild
�������ܣ�ǰ�����������
����ֵ���ɹ�����OK��ʧ�ܷ���ERROR
*******************/
int PreOrderTraverse(BiTNode *T)
{
	if (T) {
		printf("%c", T->data.c);
		PreOrderTraverse(T->lchild);
		PreOrderTraverse(T->rchild);
	}
	else
		putchar('#');
	return OK;
}
/******************
�������ƣ�DeleteChild
�����������������ĸ���㣬�ؼ���e ���жϱ�־LR
�������ܣ�ɾ������
����ֵ���ɹ����뷵��OK�����򷵻�ERROR
*******************/
int DeleteChild(BiTNode*T, Key e, int LR)
{
	if(T==NULL) 
	{ 
		printf("�û��Ϊ�ն�������");
		return ERROR;
	}
	printf("��������Ҫɾ��������˫�׽��Ĺؼ���(������˫�׽�㶨��Ϊ��ͷ���)��"); scanf("%d", &e); getchar();
	if(e==0)
	{
		DestroyBiTree2(T->lchild);
		T->lchild=NULL;
		return OK;
	}
	BiTNode*p = Value(T->lchild, e);
	if (p == NULL)
	{
		printf("���иùؼ��ֵĽ�㲻���ڣ�");
		return ERROR; 
	}	
	else
	{
		printf("��0����ɾ����������1����ɾ����������������LR��ֵ��"); scanf("%d", &LR); getchar();
		BiTNode*temp;
		if (LR == 0)
		{
			temp = p->lchild;
			p->lchild = NULL;
			if (DestroyBiTree2(temp) == OK)
				return OK;
		}
		else if (LR == 1)
		{
			temp = p->rchild;
			p->rchild = NULL;
			if (DestroyBiTree2(temp) == OK)
				return OK;
		}
		else
		{
			printf("�����LRֵ���Ϸ���");
			return ERROR;
		}
	}
}
/******************
�������ƣ�change
�����������������ĸ����
�������ܣ�ͨ������������ķ�ʽ��Ҫ���������ת��Ϊû������������
����ֵ����
*******************/
void change(BiTNode*T)
{	
	if(T==NULL)
		return ;
	change(T->lchild);
	change(T->rchild);
	if(T->lchild==NULL)
		T->lchild=T->rchild;
	else
		T->lchild->rchild=T->rchild;
	T->rchild=NULL;
	return ;
}
/******************
�������ƣ�get_nums_bitree
�����������������ĸ����
�������ܣ�ͳ�ƶ������Ľ���� 
����ֵ�����ض������Ľ���� 
*******************/
int get_nums_bitree(BiTNode *T) 
{
	if (T==NULL) 
		return 0;
	else 
		return get_nums_bitree(T->lchild) + get_nums_bitree(T->rchild) + 1;
}
/******************
�������ƣ�InsertChild
�����������������ĸ���㣬�ؼ���e ���жϱ�־LR�� �����������ַ���s
�������ܣ���������
����ֵ���ɹ����뷵��OK�����򷵻�ERROR
*******************/
int InsertChild(BiTNode*T, Key e, int LR, BiTNode*p)  
{
    change(p);
	if(e==0)
	{
		p->rchild=T->lchild;
		T->lchild=p;
		return OK;
	}
	BiTNode*q=Value(T->lchild,e);
	if(q==NULL)
	{
		printf("eֵ���Ϸ���");
		return ERROR;
	}				
	if(LR==0)
	{
		p->rchild=q->lchild;
		q->lchild=p;
	}
	else if(LR==1)
	{
		p->rchild=q->rchild;
		q->rchild=p;		
	} 
	else
	{
		printf("LRֵ���Ϸ���");
		return ERROR;		
	}
	return OK;
}
/******************
�������ƣ�RightSibling
�����������������ĸ���㣬�ؼ���e
�������ܣ�Ѱ�����ֵܽ��
����ֵ��������ҵ����ؽ��ָ�룬���򷵻�NULL
*******************/
BiTNode *RightSibling(BiTNode*T, Key e)
{
	BiTNode*temp = Parent(T, e);
	if (temp == NULL)
		return NULL;
	else
		return temp->rchild;
}
/******************
�������ƣ�LeftSibling
�����������������ĸ���㣬�ؼ���e
�������ܣ�Ѱ�����ֵܽ��
����ֵ��������ҵ����ؽ��ָ�룬���򷵻�NULL
*******************/
BiTNode *LeftSibling(BiTNode*T, Key e)
{
	BiTNode*temp = Parent(T,e);
	if (temp == NULL)
		return NULL;
	else
		return temp->lchild;
}
/******************
�������ƣ�RightChild
�����������������ĸ���㣬�ؼ���e
�������ܣ�Ѱ���Һ��ӽ��
����ֵ��������ҵ����ؽ��ָ�룬���򷵻�NULL
*******************/
BiTNode * RightChild(BiTNode*T, Key e)
{
	BiTNode *temp = Value(T, e);
	if (temp == NULL)
		return NULL;
	return temp->rchild;
}
/******************
�������ƣ�LeftChild
�����������������ĸ���㣬�ؼ���e
�������ܣ�Ѱ�����ӽ��
����ֵ��������ҵ����ؽ��ָ�룬���򷵻�NULL
*******************/
BiTNode * LeftChild(BiTNode*T, Key e)
{
	BiTNode *temp=Value(T, e);
	if (temp == NULL)
		return NULL;
	return temp->lchild;
}
/******************
�������ƣ�Parent
�����������������ĸ���㣬�ؼ���e
�������ܣ�Ѱ��˫�׽��
����ֵ��������ҵ��ͷ��ؽ��ָ�룬���򷵻�NULL
*******************/
BiTNode * Parent(BiTNode *T, Key e)
{												
	if ((T->lchild != NULL && e == T->lchild->data.i)
		|| (T->rchild != NULL && e == T->rchild->data.i)) {
		return T;
	}
	else {
		BiTNode*temp=NULL;
		if(T->lchild != NULL)
			temp=Parent(T->lchild,e);
		if(temp==NULL&&T->rchild != NULL)
			temp= Parent(T->rchild, e);
		return temp;
	}
}
/******************
�������ƣ�Assign
�����������������ĸ���㣬�ؼ���e������c
�������ܣ����ؼ���Ϊe�Ľ������ݸ�Ϊc
����ֵ��������ҵ����ͷ���OK�����򷵻�ERROR
*******************/
int Assign(BiTNode *T, Key e, char c)
{
	BiTNode *temp;
	if ((temp = Value(T, e) )== NULL)
		return ERROR;
	temp->data.c = c;
	return OK;
}
/******************
�������ƣ�Value
�����������������ĸ���㣬�ؼ���e
�������ܣ����ض�������Ӧ����������
����ֵ��������ھͷ��ض�������Ӧ��㣬���򷵻�NULL
*******************/
BiTNode * Value(BiTNode *T, Key e)
{
	if (T == NULL)
		return NULL;
	if (T->data.i == e)
		return T;
	BiTNode * temp;
	temp = Value(T->lchild, e);
	if (temp == NULL)
	{
		temp= (BiTNode*)malloc(sizeof(BiTNode));
		temp = Value(T->rchild, e);
	}
	return temp;
}
/******************
�������ƣ�Root
�����������������ı�ͷ���
�������ܣ����ض��������ڵ�
����ֵ�����������ڵ�
*******************/
BiTNode *Root(BiTNode *T)
{
	return T->lchild;
}
/******************
�������ƣ�BiTreeDepth
�����������������ĸ�����ָ�� 
�������ܣ����ض����������
����ֵ�����ض����������
*******************/
int BiTreeDepth(BiTNode *T)
{
	int deep = 0;
	if (T)
	{
		int leftdeep = BiTreeDepth(T->lchild);
		int rightdeep = BiTreeDepth(T->rchild);
		deep = leftdeep >= rightdeep ? leftdeep + 1 : rightdeep + 1;
	}
	return deep;
}
/******************
�������ƣ�BiTreeEmpty
�����������������ı�ͷ���
�������ܣ��ж϶������Ƿ�Ϊ��
����ֵ���Ƿ���OK�����Ƿ���ERROR
*******************/
int BiTreeEmpty(BiTNode T)
{
	if ((&T)->lchild == NULL)
		return OK;
	else
		return ERROR;
}
/******************
�������ƣ�ClearBiTre
����������ָ��������ı�ͷ����ָ��F->HeadNode
�������ܣ���ն�����
����ֵ���ɹ�����OK��ʧ�ܷ���ERROR
*******************/
int ClearBiTree(BiTNode *T)
{
	if(T==NULL)
		return OK;
	if (DestroyBiTree2(T->lchild) == ERROR)
		return ERROR;
	T->lchild = NULL;
	return OK;
}
/******************
�������ƣ�PreCreateBiTree
�����������������ĸ����T�ĵ�ַ��������ַ���s�����ڶ�λ�ַ���Ԫ�ص�i
�������ܣ��õݹ����ɶ����� 
����ֵ���ɹ�����OK��ʧ�ܷ���ERROR
*******************/
int PreCreateBiTree(BiTNode **T, char*s, int *i)
{
	if (s[*i] == '#') *T = NULL;
	else if (s[*i] == '\n'|| s[*i] == ' ') return ERROR;
	else
	{
		if (!((*T) = ((BiTNode*)malloc(sizeof(BiTNode))))) return ERROR;
		(*T)->data.c = s[*i];
		if ((PreCreateBiTree(&((*T)->lchild), s, &(++(*i))) == ERROR))
			return ERROR;
		if ((PreCreateBiTree(&((*T)->rchild), s, &(++(*i)))) == ERROR)
			return ERROR;
	}
	return OK;
}
/******************
�������ƣ�CreateBiTree
�����������ַ���definition
�������ܣ����������definition�������ɶ����� 
����ֵ���ɹ�����root��ʧ�ܷ���NULL
*******************/
BiTNode * CreateBiTree(char*definition)
{
	if (definition[0] == '\n')
	{
		printf("δ���������ַ���");	
		return NULL;
	}
	else if(definition[0]=='#')
	{
		printf("����Ϊ������");	
		return NULL;
	} 
	int i = 0;
	BiTNode *root = (BiTNode*)malloc(sizeof(BiTNode));
	if (PreCreateBiTree(&root, definition, &i) == ERROR)
		return NULL;
	root->data.i = 1;
	return root;
}
/******************
�������ƣ�DestroyBiTree2
����������ָ��Forest��ͷ���L�ͱ���ָ��F
�������ܣ�����ɭ�ֽṹ��F��Ӧ��㣬�ҽ���ʹFָ��NULL�� 
����ֵ���ɹ�����OK��ʧ�ܷ���ERROR
*******************/
int DestroyBiTree(Forest L,BiTree *F) 
{
	int i;
	for (i = 0;i < L.length;i++) 
	{
		if (strcmp(L.elem[i].name,F->name) == 0) 
			break;
	}
	if (i+1>L.length) 
	{
		printf("��ǰû�л����");
		return ERROR;
	}
	DestroyBiTree2(L.elem[i].HeadNode->lchild);
	free(L.elem[i].HeadNode);
	for (;i<L.length;i++) 
	{  
		strcpy(L.elem[i].name, L.elem[i+1].name);
		L.elem[i].HeadNode = L.elem[i+1].HeadNode;
	}
	L.elem[L.length].HeadNode=NULL;
	L.length--;
	return OK;
}
/******************
�������ƣ�DestroyBiTree2 
��������������� 
�������ܣ����ٶ�����T
����ֵ���ɹ�����OK��ʧ�ܷ���ERROR
*******************/
int DestroyBiTree2(BiTNode *T)
{
	if (T == NULL) {
		return OK;
	}
	DestroyBiTree2(T->lchild);
	DestroyBiTree2(T->rchild);
	free(T);
	return OK;
}
/******************
�������ƣ�InitBiTree
����������Forest��ͷָ��
�������ܣ�����ն�����T
����ֵ���ɹ�����OK��ʧ�ܷ���ERROR
*******************/
int InitBiTree(Forest *L)
{
	int i;
	char name[20];
	printf("��������������֣�20���ַ����ڣ���");scanf("%s",name);getchar();
	for (i = 1;i <= L->length;i++) 
	{
		if (strcmp(L->elem[i - 1].name, name) == 0) break;   
	}
	if (i <= L->length) 
	{
		printf("�����Ѵ��ڣ�");  
		return ERROR;
	}
	BiTree *newbase;
	if (L->length >= L->listsize) {
		newbase = (BiTree *)realloc(L->elem, (L->listsize + LISTINCREMENT)*sizeof(BiTree));  
		if (!newbase) 
		{
			printf("�����ڴ�ʧ�ܣ�");
			return ERROR;
		}    
		L->listsize += LISTINCREMENT;
		L->elem = newbase;
	}
	strcpy(L->elem[L->length].name, name);
	L->elem[L->length].HeadNode = (BiTNode*)malloc(sizeof(BiTNode));  
	L->elem[L->length].HeadNode->data.i= 0;
	L->elem[L->length].HeadNode->data.c= 0; 
	L->elem[L->length].HeadNode->lchild = L->elem[L->length].HeadNode->rchild = NULL;
	(L->length)++; 
	return OK;
}
/******************
�������ƣ�show
��������������ָ��F
�������ܣ���ʾα�˵�����
����ֵ����
*******************/
void show(BiTree* F)
{
	system("cls");
	printf("\n\n");
	printf("         Menu for BiTree On Chain Structure  \n");
	printf("-------------------------------------------------\n");
	printf("    	  1. InitBiTree           13. LeftSibling\n");
	printf("    	  2. DestroyBiTree        14. RightSibling\n");
	printf("    	  3. CreateBiTree         15. InsertChild\n");
	printf("    	  4. ClearBiTree          16. DeleteChild\n");
	printf("    	  5. BiTreeEmpty          17. PreOrderTraverse\n");
	printf("    	  6. BiTreeDepth          18. InOrderTraverse\n");
	printf("	  7. Root                 19. PostOrderTraverse\n");
	printf("	  8. Value                20. LevelOrderTraverse\n");
	printf("	  9. Assign		  21. SaveData\n");
	printf("	  10. Parent		  22. LoadData\n");		
	printf("	  11. LeftChild		  23. ExBiTree\n");
	printf("	  12. RightChild	  0. Exit\n");
	printf("-------------------------------------------------\n");
	if (F == NULL)
		printf("\n-----------��ǰû�л��-----------\n");
	else
		printf("\n-----------��ǰ���� %s ���в���-----------\n", F->name);
	printf("    ��ѡ����Ĳ���[0~23]:");
}
/******************
�������ƣ�updata
��������������� 
�������ܣ����������λ�õĸ�ֵ������������key
����ֵ����
*******************/
void updata(BiTNode *T)
{
	if (T == NULL)return;
	if (T->lchild)
	{
		T->lchild->data.i = 2 * T->data.i;
		updata(T->lchild);
	}
	if (T->rchild)
	{
		T->rchild->data.i = 2 * T->data.i + 1;
		updata(T->rchild);
	}
}
