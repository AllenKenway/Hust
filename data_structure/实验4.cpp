//---------------------------------------�����ڽӱ������ͼ��ز���--------------------------------------// 
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>

#define FALSE -1 
#define OK 1
#define ERROR -2 
#define TRUE 1
#define INFEASTABLE -1
#define OVERFLOW -2

#define MAX_VERTICE_NUM 20

typedef enum { DG, DN, UDG, UND }GraphKind; //����ͼ,������,����ͼ,������
typedef int status;
typedef char VertexType;
typedef struct ArcNode {
	int adjvex; 				//�û���ָ��Ķ����λ�� 
	struct ArcNode *nextarc; 	//ָ����һ������ָ�� 
}ArcNode;
typedef struct VNode{
	VertexType data; 			//������Ϣ
	ArcNode *firstarc; 			//��һ������ĵ�ַ,ָ���һ�������ö���Ļ���ָ��
}VNode;

typedef struct ALGraph {
	VNode vertices[MAX_VERTICE_NUM];
	int vexnum, arcnum; //ͼ�ĵ�ǰ�������ͻ���
	char name[20];				//ͼ������
	ALGraph *next;			//ָ����һ��ͼ��ָ��
}ALGraph;
int visited[MAX_VERTICE_NUM];
//---------------------------------------���еĶ���ͻ������������ڹ�����ȱ���ͼ---------------------------------------// 
struct LinkQueueNode {
	VNode*data;
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
void EnQueue(LKQueue*LQ, VNode*T)
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
VNode *GetHead(LKQueue *LQ)
{
	LinkQueueNode *p;
	VNode *T = NULL;
	if (EmptyQueue(LQ))
		return T;
	else
	{
		p = LQ->front->next;
		return p->data;
	}
}

//---------------------------------------���ܺ���������---------------------------------------// 
void show(ALGraph *G);
ALGraph *CreateGraph(ALGraph *Head, char V[MAX_VERTICE_NUM],char VR[MAX_VERTICE_NUM][MAX_VERTICE_NUM]);
status DestroyGraph(ALGraph *G);
status LocateVex(ALGraph*G, VertexType e);
VertexType GetVex(ALGraph*G, int i);
status PutVex(ALGraph*G, int i, VertexType e);
status FirstAdjVex(ALGraph*G, int i);
status NextAdjVex(ALGraph* G, int i,int j);
status InsertVex(ALGraph* G, VertexType e);
status DeleteVex(ALGraph* G, int i);
status InsertArc(ALGraph* G, int i, int j);
status DeleteArc(ALGraph* G, int i, int j);
status DFSTraverse(ALGraph* G);
void DFS(ALGraph* G, int v);
status BFSTraverse(ALGraph* G);
status SaveData(FILE *fp, ALGraph *G, char filename[30]);
status LoadData(FILE *fp, ALGraph *G, char filename[30]);
ALGraph* ExGraph(ALGraph*Head, char name[20]);

int main() {
	int op = 1;
	VertexType e = 0;
	status a,i,j;
	ALGraph *Head,*G,*G1;
	Head = (ALGraph*)malloc(sizeof(ALGraph));
	Head->arcnum = 0; Head->name[20] = {'\0'}; Head->vertices[0]= {'\0'}; Head->vexnum = 0;
	Head->next = NULL;G = Head->next;

	FILE*fp=NULL; char filename[30];
	char name[20];
	char V[MAX_VERTICE_NUM], VR[MAX_VERTICE_NUM][MAX_VERTICE_NUM];

	while (op) {
		show(G);
		scanf("%d", &op); getchar();
		switch (op) 
		{
			case 1:
				printf("�������ͼ�����֣�20���ַ����ڣ���"); scanf("%s", name, 20); getchar();
				G1 = Head->next;
				while (G1)
				{
					if (strcmp(G1->name, name) == 0) break;
					G1 = G1->next;
				}
				if (G1!= NULL)
				{
					printf("�����Ѵ��ڣ�����ʧ�ܣ�");
					getchar();
					break;
				}

				G1= (ALGraph*)malloc(sizeof(ALGraph));
				G1->next = NULL;
				strcpy(G1->name,name);
				printf("����������ͼ�Ķ������ͱ���(��ʽ��x y�Ҷ�����������20)��"); scanf("%d %d", &((*G1).vexnum), &((*G1).arcnum)); getchar();
				if ((*G1).vexnum > MAX_VERTICE_NUM)
				{
					printf("�����������涨����󶥵���������ͼʧ�ܣ�");
					getchar();break;
				}
				if ((*G1).vexnum == 0)
				{
					if ((*G1).arcnum == 0)
					{
						G1->vertices[0] = { '\0' };
						G = Head;
						while (G->next)
							G = G->next;
						G->next = G1;
						G = G1;
						printf("����ͼ�ɹ���");
						getchar(); break;
					}
					else
					{
						printf("������Ϊ0��������Ϊ0������ʧ�ܣ�");
						getchar(); break;
					}
				}
				printf("������������ͼ�ж��������(һ������Ϊһ��char���͵ĵ��ַ�)��"); scanf("%s", V, 20); getchar();

				j = 0;
				for (i = 0; (*G1).arcnum != 0&&i < (*G1).vexnum; i++)
				{
					printf("�����������붥��%c�ڽӵĶ�������ݣ���������0����", V[i]); scanf("%s", VR[i], 20); getchar();
					if (VR[i][0] == '0')
						VR[i][0] = '\0';
					else
						j = j + strlen(VR[i]);
				}
				for (; i < MAX_VERTICE_NUM; i++)
					*VR[i] = {'\0'};
				if (j != (*G1).arcnum)
				{
					printf("����������ı�������ͬ������ʧ�ܣ�");
					getchar();break;
				}

				if ((G1 = CreateGraph(G1,V,VR)) != NULL)
				{
					G = Head;
					while (G->next)
						G = G->next;
					G->next = G1;
					G = G1;
					printf("����ͼ�ɹ���");
				}
				else
					printf("����ͼʧ�ܣ�");
				getchar();break;
			case 2:
				if (DestroyGraph(G) == OK)
				{
					printf("ͼ���ٳɹ���\n");
					G1 = Head;
					for (; G1->next != G; G1 = G1->next);
					G1->next = G1->next->next;
					free(G);
					G->next = NULL;
					G = NULL;
				}
				else 
					printf("ͼ����ʧ�ܣ�\n");
				getchar();break;
			case 3:
				printf("��������Ҫ���ҵĶ����VertexType���ݣ�");scanf("%c", &e); getchar();
				if ((a = LocateVex(G, e)) != ERROR)
					printf("����%c��ͼ�е����Ϊ��%d��", e, a);
				else
					printf("ͼ�в����ڸö��㣡");
				getchar();break;
			case 4:
				printf("��������Ҫ���ҵĶ������ţ�"); scanf("%d", &i); getchar();
				if ((e = GetVex(G, i)) != ERROR)
					printf("���Ϊ%d�Ķ����ֵΪΪ��%c��", i, e);
				else
					printf("ͼ�в����ڸö��㣡");
				getchar();break;
			case 5:
				printf("��������Ҫ�޸ĵĶ������ţ�"); scanf("%d", &i); getchar();
				printf("�������޸ĺ�����ݣ�"); scanf("%c", &e); getchar();
				if ((PutVex(G,i,e)) != ERROR)
					printf("�޸ĳɹ���");
				else
					printf("�޸�ʧ�ܣ�");
				getchar();break;
			case 6:
				printf("��������Ҫ���ҵĶ������ţ�"); scanf("%d", &i); getchar();
				if ((a = FirstAdjVex(G, i)) == ERROR)
					printf("ͼ�в����ڸö��㣡");
				else if (a != -1)
					printf("���Ϊ%d�Ķ���ĵ�һ�ڽӵ�����Ϊ��%d   ֵΪ��%c��", i, a, G->vertices[a].data);
				else
					printf("���Ϊ%d�Ķ������ڽӵ㡣", i);
				getchar();break;
			case 7:
				printf("��������Ҫ���ҵĶ������ţ�"); scanf("%d", &i); getchar();
				printf("������ö����һ�ڽӶ������ţ�"); scanf("%d", &j); getchar();
				if ((a = NextAdjVex(G, i, j)) == ERROR)
					printf("ͼ�в����ڸö��㣡");
				else if (a == -1)
					printf("���Ϊ%d�Ķ���û�����Ϊ%d���ڽӵ㡣", i, j);
				else if(a==-3)
					printf("���Ϊ%d�Ķ�������һ�ٽӵ㡣", i);
				else
					printf("���Ϊ%d�Ķ������һ�ٽ������Ϊ��%d   ֵΪ��%c��", i, a, G->vertices[a].data);
				getchar();break;
			case 8:
				printf("��������Ҫ����Ķ��������Ϊ��"); scanf("%c", &e); getchar();
				if ((InsertVex(G, e))== OK)
					printf("����ɹ���");
				else
					printf("����ʧ�ܣ�");
				getchar();break;
			case 9:
				printf("��������Ҫɾ���Ķ�������Ϊ��"); scanf("%d", &i); getchar();
				if (DeleteVex(G, i) == OK)
					printf("ɾ���ɹ���");
				else
					printf("ɾ��ʧ�ܣ�");
				getchar();break;
			case 10:
				printf("��������뻡�Ļ�β������źͻ�ͷ�������(��ʽ��x y)��"); scanf("%d %d", &i, &j); getchar();
				if (InsertArc(G, i, j) == OK)
					printf("����ɹ���");
				else
					printf("����ʧ�ܣ�");
				getchar();break;
			case 11:
				printf("������ɾ�����Ļ�β������źͻ�ͷ�������(��ʽ��x y)��"); scanf("%d %d", &i, &j); getchar();
				if (DeleteArc(G, i, j) == OK)
					printf("ɾ���ɹ���");
				else
					printf("ɾ��ʧ�ܣ�");
				getchar();break;
			case 12:
				if (DFSTraverse(G) == OK)
					printf("\n�����ɹ���");
				else
					printf("����ʧ�ܣ�");
				getchar();break;
			case 13:
				if (BFSTraverse(G) == OK)
					printf("\n�����ɹ���");
				else
					printf("����ʧ�ܣ�");
				getchar();break;
			case 14:
				if (SaveData(fp, G, filename) == OK)
					printf("����д���ļ��ɹ���");
				else
					printf("����д���ļ�ʧ�ܣ�");
				getchar();break;
			case 15:
				if (LoadData(fp, G, filename) == OK)
					printf("���ݼ��سɹ���");
				else
					printf("���ݼ���ʧ�ܣ�");
				getchar();break;
			case 16:
				if (G == NULL)
				{
					printf("��ǰû��ͼ���л�ʧ�ܣ�");
					getchar(); break;
				}
				G1 = Head->next;
				while (G1)
				{
					printf("ͼ�����֣�%s\n�������ȱ�������Ϊ��", G1->name);
					BFSTraverse(G1);
					printf("\n\n");
					G1 = G1->next;
				}
				printf("�������л����ͼ�����֣�"); scanf("%s", name,20); getchar();
				G1 = ExGraph(Head, name);
				if (G1 == NULL)
					printf("��������ֲ��Ϸ����л�ʧ�ܣ�");
				else
				{
					G = G1;
					printf("�л��ɹ�����ǰ���Ϊ%s��",G->name);
				}
				getchar();break;
			case 0:
				printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
				getchar();break;
			default:
			{
				printf("����ѡ������Ч�����룡\n");
				getchar();
			}
		}
	}
	return 0;
}
/******************
�������ƣ�LoadData
�����������ļ�ָ��fp���ͼָ�룬�ļ�����filename
�������ܣ����ļ��е���Ϣ���ص��ͼ��
����ֵ���ɹ�����OK��ʧ�ܷ���ERROR
*******************/
status LoadData(FILE *fp, ALGraph*G, char filename[30])
{
	if (G == NULL)
	{
		printf("��ǰ�޻ͼ��");
		return ERROR;
	}
	printf("������Ҫ�������ݵ��ļ���: "); scanf("%s", filename, 30); getchar();
	if ((fp = fopen(filename, "r")) == NULL)
	{
		printf("�ļ���ʧ�ܣ�");
		return ERROR;
	}
	for (int i = 0; i<(*G).vexnum; i++)
	{
		ArcNode *p, *q;
		p = (*G).vertices[i].firstarc;
		while (p) {
			q = p->nextarc;
			free(p);
			p = q;
		}
	}
	(*G).vexnum = 0; (*G).arcnum = 0;
	(*G).vertices[MAX_VERTICE_NUM] = { '\0' };
	
	char V[MAX_VERTICE_NUM], VR[MAX_VERTICE_NUM][MAX_VERTICE_NUM];
	fscanf(fp, "%d %d", &((*G).vexnum), &((*G).arcnum)); 
	fscanf(fp, "%s", V);
	int i;
	for (i = 0; i < (*G).vexnum; i++)
		fscanf(fp, "%s", VR[i]);
	for (;i < MAX_VERTICE_NUM; i++)
		*VR[i] = {'\0'};
	for (int i = 0; i < (*G).vexnum; i++)
		for(int j=0;j<MAX_VERTICE_NUM;j++)
		{
			if(VR[i][j]=='0')
			{
				VR[i][j]='\0';
				break;
			}	
		}
	 G=CreateGraph(G,V,VR);
	 return OK;
}
/******************
�������ƣ�SaveData
�����������ļ�ָ��fp���ͼ��㣬�ļ�����filename
�������ܣ�����ͼ����Ϣ
����ֵ���ɹ�����OK��ʧ�ܷ���ERROR
*******************/
status SaveData(FILE *fp, ALGraph *G, char filename[30])
{
	if (G == NULL)
	{
		printf("��ǰ�޻ͼ��");
		return ERROR;
	}
	printf("������Ҫд����ļ���: "); scanf("%s", filename,30); getchar();
	if ((fp = fopen(filename, "w")) == NULL)
	{
		printf("�ļ���ʧ�ܣ�");
		return ERROR;
	}
	fprintf(fp,"%d %d\n",(*G).vexnum,(*G).arcnum);
	for (int i = 0; i < (*G).vexnum; i++)
		fprintf(fp, "%c", GetVex(G,i));
	fprintf(fp, "\n");
	for (int i = 0; i < (*G).vexnum; i++)
	{
		ArcNode *p = (*G).vertices[i].firstarc;
		if(p==NULL) fprintf(fp,"0");
		while (p)
		{
			fprintf(fp, "%c", GetVex(G, p->adjvex));
			p = p->nextarc;
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
	return OK;
}
/******************
�������ƣ�ExGraph
������������ͼͷָ�룬ͼ������name
�������ܣ��л��ͼ
����ֵ���ɹ���������Ϊname��ͼ�Ľṹ��ʧ�ܷ���NULL
*******************/
ALGraph* ExGraph(ALGraph*Head, char name[20])
{
	ALGraph*L = Head->next;
	while (L)
	{
		if (strcmp(L->name, name) == 0)
			break;
		L = L->next;
	}
	return L;
}
/******************
�������ƣ�BFSTraverse
������������ǰ�ͼG
�������ܣ������������ͼ
����ֵ���ɹ�����OK��ʧ�ܷ���ERROR
*******************/
status BFSTraverse(ALGraph* G)
{
	if (G == NULL)
	{
		printf("��ǰ�޻ͼ��");
		return ERROR;
	}
	for (int v = 0; v < (*G).vexnum; v++)
		visited[v] = 0;
	LKQueue *Q=(LKQueue *)malloc(sizeof(LKQueue));
	InitQueue(Q);
	for (int v = 0; v < (*G).vexnum; v++)
	{
		if (!visited[v])
		{
			printf("%c", (*G).vertices[v].data);
			visited[v] = 1;
			EnQueue(Q, &(*G).vertices[v]);
			while (!EmptyQueue(Q))
			{
				int u = LocateVex(G, GetHead(Q)->data);
				OutQueue(Q);
				for (int w = FirstAdjVex(G, u); w >= 0; w = NextAdjVex(G, u, w))
					if (!visited[w])
					{
						printf("%c", (*G).vertices[w].data);
						visited[w] = 1;
						EnQueue(Q, &(*G).vertices[w]);
					}
			}
		}
	}
	return OK;
}
/******************
�������ƣ�DFSTraverse
������������ǰ�ͼG,Ҫ���v
�������ܣ������������ͼ
����ֵ����
*******************/
void DFS(ALGraph* G, int v)
{
	ArcNode *p;
	printf("%c", (*G).vertices[v].data);
	visited[v] = 1;
	p = (*G).vertices[v].firstarc;
	while (p)
	{
		if (!visited[p->adjvex])
			DFS(G, p->adjvex);
		p = p->nextarc;
	}
}
/******************
�������ƣ�DFSTraverse
������������ǰ�ͼG
�������ܣ������������ͼ
����ֵ���ɹ�����OK��ʧ�ܷ���ERROR
*******************/
status DFSTraverse(ALGraph* G)
{
	if (G == NULL)
	{
		printf("��ǰ�޻ͼ��");
		return ERROR;
	}
	for (int v = 0; v < (*G).vexnum; v++)
		visited[v] = 0;
	for (int v = 0; v < (*G).vexnum; v++)
	{
		if (!visited[v])
			DFS(G, v);
	}
	return OK;
}
/******************
�������ƣ�DeleteArc
������������ǰ�ͼG��ɾ�����Ļ�βi�ͻ�ͷj
�������ܣ�ɾ����
����ֵ���ɹ�����OK��ʧ�ܷ���ERROR
*******************/
status DeleteArc(ALGraph* G, int i, int j)
{
	VertexType a = GetVex(G, i);
	if (a == ERROR)
		return ERROR;
	a = GetVex(G, j);
	if (a == ERROR)
		return ERROR;
	ArcNode*p=(*G).vertices[i].firstarc;
	if (p == NULL)
	{
		printf("��ͷ�������Ϊ%d�һ�β�������Ϊ%d�Ļ������ڣ�", i, j);
		return ERROR;
	}
	if (p->adjvex == j)
	{
		(*G).vertices[i].firstarc = p->nextarc;
		free(p);
		p = (*G).vertices[i].firstarc;
		(*G).arcnum--;
		return OK;
	}
	status flag = 0;
	ArcNode*q;
	while (p)												   
	{
		q = p;
		p = p->nextarc;
		if (p->adjvex == j)
		{
			q->nextarc = p->nextarc;
			free(p);
			flag = 1;
			break;
		}
	}
	if (flag == 0)
	{
		printf("��ͷ�������Ϊ%d�һ�β�������Ϊ%d�Ļ������ڣ�",i,j);
		return ERROR;
	}
	(*G).arcnum--;
	return OK;
}
/******************
�������ƣ�InsertArc
������������ǰ�ͼG�����뻡�Ļ�βi�ͻ�ͷj
�������ܣ����뻡
����ֵ���ɹ�����OK��ʧ�ܷ���ERROR
*******************/
status InsertArc(ALGraph* G, int i, int j)
{
	VertexType a = GetVex(G, i);
	if (a == ERROR)
		return ERROR;
	a = GetVex(G, j);
	if (a == ERROR)
		return ERROR;
	ArcNode*p,*q;
	p = (ArcNode*)malloc(sizeof(ArcNode));
	p->adjvex = j;
	p->nextarc= NULL;
	q = (*G).vertices[i].firstarc;
	if(q==NULL)
		(*G).vertices[i].firstarc=p; 
	else
	{
		while (q->nextarc)
			q = q->nextarc;
		q->nextarc = p;
	}
	(*G).arcnum++;
	return OK;
}
/******************
�������ƣ�DeleteVex
������������ǰ�ͼG����Ҫɾ����������i
�������ܣ�ɾ������
����ֵ���ɹ�����OK��ʧ�ܷ���ERROR
*******************/
status DeleteVex(ALGraph* G, int i)
{
	VertexType a = GetVex(G, i);
	if (a == ERROR)
		return ERROR;
	ArcNode *p, *q=NULL;
	p = (*G).vertices[i].firstarc; 
	while (p) 
	{
		q = p;
		p = p->nextarc;
		free(q);
		(*G).arcnum--; 
	}
	int j;
	for (j = i; j<(*G).vexnum; j++) 
		(*G).vertices[j] = (*G).vertices[j + 1];
	(*G).vexnum--;
	for (j = 0; j<(*G).vexnum; j++) 
	{
		p = (*G).vertices[j].firstarc; 
		while (p)
		{		
			if (p->adjvex == i) 
			{
				if (p == (*G).vertices[j].firstarc) 
				{
					(*G).vertices[j].firstarc = p->nextarc;
					free(p);
					p = (*G).vertices[j].firstarc;
				}
				else {
					q->nextarc = p->nextarc;
					free(p);
					p = q->nextarc;
				}
				(*G).arcnum--;
			}
			else 
			{
				if (p->adjvex>i)
					p->adjvex--;
				q = p;
				p = p->nextarc;
			}
		}
	}
	return OK;
}
/******************
�������ƣ�InsertVex
������������ǰ�ͼG����Ҫ���붥�������e
�������ܣ����붥��
����ֵ���ɹ�����OK��ʧ�ܷ���ERROR
*******************/
status InsertVex(ALGraph* G, VertexType e)
{
	if (G == NULL)
	{
		printf("��ǰ�޻ͼ��");
		return ERROR;
	}
	if (G->vexnum == MAX_VERTICE_NUM)
	{
		printf("��ǰͼ�Ķ������Ѵﵽ�涨�����ֵ��");
		return ERROR;
	}
	int j=G->vexnum;
	G->vertices[j].data= e;
	G->vertices[j].firstarc = NULL;
	G->vexnum++;
	return OK;
}
/******************
�������ƣ�NextAdjVex
������������ǰ�ͼG����Ҫ���ҵĶ�������i�����ڽӽ��j
�������ܣ������һ�ڽӶ���
����ֵ���ɹ����ض���λ�ã�ʧ�ܷ���NULL
*******************/
status NextAdjVex(ALGraph* G, int i, int j)
{
	VertexType a = GetVex(G, i);
	if (a == ERROR)
		return ERROR;
	ArcNode *p;
	p = (G->vertices[i]).firstarc;
	while (p != NULL&&p->adjvex != j)
		p = p->nextarc;
	if (p == NULL)
		return -1;
	if (p->nextarc == NULL)
		return -3;
	return p->nextarc->adjvex;
}
/******************
�������ƣ�FirstAdjVex
������������ǰ�ͼG����Ҫ���ҵĶ�������i
�������ܣ������һ�ڽӶ���
����ֵ���ɹ����ض���λ�ã�ʧ�ܷ���NULL
*******************/
status FirstAdjVex(ALGraph* G, int i)
{
	VertexType a = GetVex(G, i);
	if (a == ERROR)
		return ERROR;
	if ((G->vertices[i]).firstarc == NULL)
		return -1;
	return (G->vertices[i]).firstarc->adjvex;
}
/******************
�������ƣ�PutVex
������������ǰ�ͼG����Ҫ�޸ĵĶ�������i�Լ��޸ĺ������e
�������ܣ��ڵ㸳ֵ
����ֵ���ɹ�����OK��ʧ�ܷ���ERROR
*******************/
status PutVex(ALGraph* G, int i, VertexType e)
{
	VertexType a = GetVex(G, i);
	if (a == ERROR)
		return ERROR;
	G->vertices[i].data = e;
	return OK;
}
/******************
�������ƣ�GetVex
������������ǰ�ͼG���Լ���Ҫ���ҵĶ�������i
�������ܣ����Ҷ���ֵ
����ֵ���ҵ��򷵻ض���ֵ��δ�ҵ�����ERROR
*******************/
VertexType GetVex(ALGraph*G, int i)
{
	if (G == NULL)
	{
		printf("��ǰ�޻ͼ��");
		return ERROR;
	}
	int j = G->vexnum;
	if (j == 0)
	{
		printf("��ͼ���㼯Ϊ�գ�");
		return ERROR;
	}
	if(i>j-1||i<0)
	{
		printf("�������Ų��Ϸ���");
		return ERROR;
	}
	return G->vertices[i].data;
}
/******************
�������ƣ�LocateVex
������������ǰ�ͼG���Լ���Ҫ���ҵĶ����VertexType����e
�������ܣ����Ҷ���
����ֵ���ҵ��򷵻�λ��i��δ�ҵ�����ERROR
*******************/
status LocateVex(ALGraph*G, VertexType e)
{
	if(G == NULL)
	{
		printf("��ǰ�޻ͼ��");
		return ERROR;
	}
	int i;
	for (i = 0; i < (*G).vexnum; i++)
	{
		if (e == (*G).vertices[i].data)
			return i;
	}
	return ERROR;
}
/******************
�������ƣ�DestroyGraph
��������������ָ��G
�������ܣ�����ͼ
����ֵ���ɹ�ΪOK��ʧ��ΪERROR
*******************/
status DestroyGraph(ALGraph *G)
{
	if (G == NULL)
	{
		printf("��ǰ�޻ͼ��");
		return ERROR;
	}
	int i;
	for (i = 0; i<(*G).vexnum; i++) 
	{
		ArcNode *p, *q;
		p = (*G).vertices[i].firstarc;
		while (p) {
			q = p->nextarc;
			free(p);
			p = q;
		}
	}
	(*G).vexnum = 0;
	(*G).arcnum = 0;
	(*G).name[20] = {'\0'};
	(*G).vertices[MAX_VERTICE_NUM] = { '\0' };
	return OK;
}
/******************
�������ƣ�CreateCraph
������������ͼ��ͷָ��Head
�������ܣ�����ͼ
����ֵ����ǰͼ�Ľ��
*******************/
ALGraph *CreateGraph(ALGraph *G, char V[MAX_VERTICE_NUM], char VR[MAX_VERTICE_NUM][MAX_VERTICE_NUM])
{
	int i, j = 0;
	for (i = 0; i<(*G).vexnum; i++)
	{
		(*G).vertices[i].data = V[i];
		(*G).vertices[i].firstarc = NULL;
	}
	for (i = 0; i<(*G).vexnum; i++)
	{
		for (j = 0; VR[i][j] != '\0'; j++)
		{
			int a = LocateVex(G, VR[i][j]);
			if (a == ERROR)
			{
				printf("����Ϊ%c�Ķ�����G�в����ڣ�", VR[i][j]);
				return NULL;
			}
			ArcNode*p = (ArcNode*)malloc(sizeof(ArcNode));
			p->adjvex = a; p->nextarc = NULL;
			ArcNode*q = (*G).vertices[i].firstarc;
			if (q == NULL)
				(*G).vertices[i].firstarc = p;
			else
			{
				while (q->nextarc)  q = q->nextarc;
				q->nextarc = p;
			}
		}
	}
	for (; i < MAX_VERTICE_NUM; i++)
	{
		(*G).vertices[i].data = 0;
		(*G).vertices[i].firstarc = NULL;
	}
	return G;
}
/******************
�������ƣ�show
��������������ָ��G
�������ܣ���ʾα�˵�����
����ֵ����
*******************/
void show(ALGraph* G)
{
	system("cls");
	printf("\n\n");
	printf("------------------Menu for Graph------------------\n\n");
	printf("\t1. CreateGraph\t\t9.  DeleteVex\n");
	printf("\t2. DestroyGraph\t\t10. InsertArc\n");
	printf("\t3. LocateVex\t\t11. DeleteArc\n");
	printf("\t4. GetVex\t\t12. DfsTraverse\n");
	printf("\t5. PutVex\t\t13. BFSTraverse\n");
	printf("\t6. FirstAdjVex\t\t14. SaveData\n");
	printf("\t7. NextAdjVex\t\t15. LoadData\n");
	printf("\t8. InsertVex\t\t16. ExGraph\n");
	printf("\t0. Exit\n\n");
	if (G == NULL)
		printf("-----------------��ǰû�лͼ-----------------\n");
	else
	{
		printf("\n--------------��ǰ��ͼ %s ���в���--------------\n\n", G->name);
		for (int i = 1; i <= G->vexnum; i++)
		{
			printf("λ�ã�%d  ���ݣ�%c\t", i-1, G->vertices[i-1].data);
			if (i % 4 == 0)printf("\n");
			if(i==G->vexnum&&i%4!=0)printf("\n\n");
		}
	}
	printf("    ��ѡ����Ĳ���[0~16]:");
}
