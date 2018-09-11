#define _CRT_SECURE_NO_DEPRECATE
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define OK 1
#define ERROR 0 


typedef struct TElemType {
	char id[20];								    //���֤��
	char name[20];							//����
	struct BSTNode *friends;				//���Ѽ�
	struct BSTNode *fan;					//��˿��
	struct BSTNode *concern;				//��ע�˼�
	struct BSTNode *hobby;				//��Ȥ���ü�
}TElemType;
typedef struct BSTNode {
	struct TElemType data;					//������Ϣ
	int BF;										//ƽ������
	struct BSTNode *lchild, *rchild;		//���Һ���ָ��
}BSTNode;
typedef struct Forest {
	char name[20];
	struct BSTNode *HeadNode;			 //������ͷ���
	struct Forest *next;
}Forest;

void show(Forest *head);	 //��ʾ�˵�
void show1();	//��ʾ���ϲ����˵�
int InitAVL(Forest *head, Forest **F);
int DestroyAVL(BSTNode*T);
int DestroyAVL1(Forest *head, Forest *F);
BSTNode*SearchAVL(BSTNode*T, char name[20],int choice);
int InsertAVL(BSTNode*T, TElemType data);
int DeleteAVL(BSTNode*T, char name[20]);

BSTNode *Balance(BSTNode *T);
int Depth(BSTNode *T);
BSTNode*Parent(BSTNode *T, char id[20]);
BSTNode*LL(BSTNode*root);
BSTNode*RR(BSTNode*root);
BSTNode*LR(BSTNode*root);
BSTNode*RL(BSTNode*root);

int set_size(BSTNode*T);
int set_member(BSTNode*T, char id[20]);

int set_intersection(BSTNode*T1, BSTNode*T2,BSTNode*T3);
int set_intersection1(BSTNode*T1, BSTNode*T2);

void copy(BSTNode*T1, BSTNode*T2);
int set_union(BSTNode*T1, BSTNode*T2);
int set_union1(BSTNode*T1, BSTNode*T2);

int set_diffrence(BSTNode*T1, BSTNode*T2, BSTNode*T3);
int set_diffrence1(BSTNode*T1, BSTNode*T2);

int set_subset(BSTNode*T1, BSTNode*T2);
int set_equal(BSTNode*T1, BSTNode*T2);

int search_common(BSTNode*T1, BSTNode*T2);
int second_friends(BSTNode*T1, BSTNode*T2);

BSTNode *aggregate(BSTNode *T, int choice);
int aggregate_init(BSTNode**T, int choice);
int aggregate_destroy(BSTNode*T, int choice);
int Delete(BSTNode*F, char id[20], int choice);
int aggregate_insert(BSTNode*T1, BSTNode*T, int choice, char id[20]);
int InsertAVL2(BSTNode*T1, int choice, TElemType data);
int aggregate_remove(BSTNode*T1, BSTNode*T, int choice, char id[20]);
int operate_aggregate(BSTNode*root, BSTNode*T, int choice);

void TraverseAVL(BSTNode*T);	//�������
void TraverseAVL2(BSTNode*T); //ǰ�����
void Traverse(Forest *head);	//��������ɭ��
Forest *ExAVL(Forest *head, char name[20]);//�л�AVL��

int SaveData(Forest*F);
int SaveData1(FILE *fp, BSTNode*T, int choice);
int SaveData2(FILE *fp, BSTNode*T);
int LoadData(Forest*F);
int random(BSTNode *T, int gross);
int random1(BSTNode *F,BSTNode *T, int gross,char hobby[60][20]);

int j=0;//��ʽ�����

int main()
{
	system("color F1");//�ı���ɫ
	Forest *head = (Forest*)malloc(sizeof(Forest));
	head->HeadNode = NULL; memset(head->name, '0', 20); head->next = NULL;

	Forest *F = head->next;
	BSTNode *T = (BSTNode*)malloc(sizeof(BSTNode));
	BSTNode *T1 = (BSTNode*)malloc(sizeof(BSTNode));
	BSTNode *agg1 = NULL, *agg2 = NULL;
	Forest *F1 = (Forest*)malloc(sizeof(Forest));

	int op = 1;
	int choice=0,choice2=0,choice3=0,re=0;
	char id[20], name[20]; char s[100];
	TElemType data; 

	while (op)
	{
		show(F);
		scanf("%d", &op); getchar();
		switch (op)
		{
		case 0:
			printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
			getchar(); break;
		case 1:case 7:
			if (InitAVL(head, &F) == OK)
				printf("����AVL���ɹ���\n");
			else
				printf("����AVL��ʧ�ܣ�\n");
			getchar();
			break;
		case 2:case 8:
			if (F == NULL)
				printf("��ǰû�л����\n");
			else if(DestroyAVL1(head, F) == OK)
			{
				F = NULL;
				printf("���ٵ�ǰAVL���ɹ���\n");
			}
			else
				printf("���ٵ�ǰAVL��ʧ�ܣ�\n");
			getchar();
			break;
		case 3:
			if (F == NULL)
				printf("��ǰû�л����\n");
			else  if (F->HeadNode->lchild == NULL)
				printf("�û��Ϊ����������ʧ�ܣ�");
			else
			{
				re = 0;
				while (re == 0)
				{
					printf("1�������Ʋ�ѯ\t2�������֤�Ų�ѯ\n"); scanf("%d", &choice3); getchar();
					switch (choice3)
					{
					case 1:re = 1; printf("������Ҫ���ҵĳ�Ա�����ƣ�"); scanf("%s", name); getchar(); break;
					case 2:re = 1; printf("������Ҫ���ҵĳ�Ա�����֤�ţ�"); scanf("%s", name); getchar();	break;
					default:printf("�������������ѡ��");
					}
				}
				T = SearchAVL(F->HeadNode->lchild, name,choice3);
				if (T != NULL)
				{
					printf("����Ϊ%s�Ľ����Ϣ���£�\n��", name);
					printf("\n���֤�ţ�%s", T->data.id);
					printf("\n\n���Ѽ���\n");
					j = 0;
					if (T->data.friends == NULL|| T->data.friends->lchild==NULL) printf("��");
					else TraverseAVL(T->data.friends->lchild);
					printf("\n\n��˿����\n");
					j = 0;
					if (T->data.fan == NULL|| T->data.fan->lchild == NULL) printf("��");
					else TraverseAVL(T->data.fan->lchild);
					printf("\n\n��ע�˼���\n");
					j = 0;
					if (T->data.concern == NULL|| T->data.concern->lchild == NULL) printf("��");
					else TraverseAVL(T->data.concern->lchild);
					printf("\n\n��Ȥ���ü���\n");
					j = 0;
					if (T->data.hobby == NULL|| T->data.hobby->lchild == NULL) printf("��");
					else TraverseAVL(T->data.hobby->lchild);
				}
				else
					printf("û���ҵ����������ĳ�Ա��");
			}
			getchar();
			break;
		case 4:case 9:
			if (F == NULL)
				printf("��ǰû�л����\n");
			else
			{
				printf("��������Ҫ����ĳ�Ա�����֤�ţ�"); scanf("%s", data.id);	getchar();
				printf("��������Ҫ����ĳ�Ա�����ƣ�"); scanf("%s", data.name); getchar();
				data.concern = NULL; data.fan = NULL; data.friends = NULL; data.hobby = NULL;
				if (InsertAVL(F->HeadNode, data) == OK)
					printf("����ɹ���");
				else
					printf("�����֤������Ѵ��ڣ�����ʧ�ܣ�");
			}
			getchar();
			break;
		case 5:case 10:
			if (F == NULL)
				printf("��ǰû�л����\n");
			else  if (F->HeadNode->lchild == NULL)
				printf("�û��Ϊ������ɾ��ʧ�ܣ�");
			else
			{
				printf("������Ҫɾ���ĳ�Ա�����֤�ţ������Ա���Կո�Ͽ�����"); fgets(s, 100, stdin);
				for (int i = 0, j = 0; i < 100; i++)
				{
					if (s[i] == ' ' || s[i] == '\n')
					{
						id[j] = '\0'; j = 0;
						T = SearchAVL(F->HeadNode->lchild, id, 2);
						if (DeleteAVL(F->HeadNode, id) == OK)
						{
							Delete(F->HeadNode->lchild, id, 1);
							Delete(F->HeadNode->lchild, id, 2);
							Delete(F->HeadNode->lchild, id, 3);
							printf("��Ա%sɾ���ɹ���\n", id);
						}
						else
							printf("û���ҵ���Ա%s��ɾ��ʧ�ܣ�\n",id);
					}
					else
					{
						id[j] = s[i];  j++;
					}
				}
			}
			getchar();
			break;
		case 6:
			if (F == NULL)
				printf("��ǰû�л����\n");
			else if (F->HeadNode->lchild == NULL)
				printf("��ǰ���Ϊ������\n");
			else
			{
				j = 0;
				printf("���������\n");
				TraverseAVL2(F->HeadNode->lchild);
				j = 0;
				printf("\n���������\n");
				TraverseAVL(F->HeadNode->lchild);
			}	
			getchar();
			break;
		case 11:
			if (F == NULL)
				printf("��ǰû�л����\n");
			else  if (F->HeadNode->lchild == NULL)
				printf("�û��Ϊ�������ж�ʧ�ܣ�");
			else
			{
				printf("��A�������ڳ�Ա��ĳһ���ϣ���\nA������Ա�����֤�ţ�"); scanf("%s", id);	getchar();
				T = SearchAVL(F->HeadNode->lchild, id, 2);
				if (T == NULL)
				{
					printf("û���ҵ���Ա%s��", id);
					getchar(); break;
				}
				re = 0;
				while (re == 0)
				{
					printf("AΪ�ý�����һ���ϣ�\n1.���Ѽ�\t2.��˿��\t3.��ע�˼�\t4.��Ȥ���ü�\n"); scanf("%d", &choice); getchar();
					switch (choice)
					{
					case 1:case 2:case 3:case 4:re = 1; agg1 = aggregate(T, choice); break;
					default:printf("�����������������");
					}
				}
				if (agg1 == NULL)
				{
					printf("����Aδ��ʼ�����޷����в�����");
					getchar();
					break;
				}
				printf("��B�������ڳ�Ա��ĳһ���ϣ���\nB������Ա�����֤�ţ�"); scanf("%s", id);	getchar();
				T1 = SearchAVL(F->HeadNode->lchild, id, 2);
				if (T1 == NULL)
				{
					printf("û���ҵ���Ա%s��", id);
					getchar(); break;
				}
				re = 0;
				while (re == 0)
				{
					printf("BΪ�ý�����һ���ϣ�\n1.���Ѽ�\t2.��˿��\t3.��ע�˼�\t4.��Ȥ���ü�\n"); scanf("%d", &choice2); getchar();
					switch (choice2)
					{
					case 1:case 2:case 3:case 4:re = 1; agg2 = aggregate(T1, choice2); break;
					default:printf("�����������������");
					}
				}
				if (agg2 == NULL)
				{
					printf("����Bδ��ʼ�����޷����в�����");
					getchar();
					break;
				}
				if (set_intersection1(agg1, agg2) == OK)
					printf("\n���������ɹ���");
			}
			getchar();
			break;
		case 12:
			if (F == NULL)
				printf("��ǰû�л����\n");
			else  if (F->HeadNode->lchild == NULL)
				printf("�û��Ϊ�������ж�ʧ�ܣ�");
			else
			{
				printf("��A�������ڳ�Ա��ĳһ���ϣ���\nA������Ա�����֤�ţ�"); scanf("%s", id); getchar();
				T = SearchAVL(F->HeadNode->lchild, id, 2);
				if (T == NULL)
				{
					printf("û���ҵ���Ա%s��", id);
					getchar(); break;
				}
				re = 0;
				while (re == 0)
				{
					printf("AΪ�ý�����һ���ϣ�\n1.���Ѽ�\t2.��˿��\t3.��ע�˼�\t4.��Ȥ���ü�\n"); scanf("%d", &choice); getchar();
					switch (choice)
					{
					case 1:case 2:case 3:case 4:re = 1; agg1 = aggregate(T, choice); break;
					default:printf("�����������������");
					}
				}

				printf("��B�������ڳ�Ա��ĳһ���ϣ���\nB������Ա�����֤�ţ�"); scanf("%s", id);	getchar();
				T1 = SearchAVL(F->HeadNode->lchild, id, 2);
				if (T1 == NULL)
				{
					printf("û���ҵ���Ա%s��", id);
					getchar(); break;
				}
				re = 0;
				while (re == 0)
				{
					printf("BΪ�ý�����һ���ϣ�\n1.���Ѽ�\t2.��˿��\t3.��ע�˼�\t4.��Ȥ���ü�\n"); scanf("%d", &choice2); getchar();
					switch (choice2)
					{
					case 1:case 2:case 3:case 4:re = 1; agg2 = aggregate(T1, choice2); break;
					default:printf("�����������������");
					}
				}

				if (agg1 == NULL)
					printf("����Aδ��ʼ�����޷������жϣ�");
				else if (agg2 == NULL)
					printf("����Bδ��ʼ�����޷������жϣ�");
				if (set_union1(agg1, agg2) == OK)
					printf("\n���������ɹ���");
			}
			getchar();
			break;
		case 13:
			if (F == NULL)
				printf("��ǰû�л����\n");
			else  if (F->HeadNode->lchild == NULL)
				printf("�û��Ϊ�������ж�ʧ�ܣ�");
			else
			{
				printf("��A�������ڳ�Ա��ĳһ���ϣ���\nA������Ա�����֤�ţ�"); scanf("%s", id);	getchar();
				T = SearchAVL(F->HeadNode->lchild, id, 2);
				if (T == NULL)
				{
					printf("û���ҵ���Ա%s��", id);
					getchar(); break;
				}
				re = 0;
				while (re == 0)
				{
					printf("AΪ�ý�����һ���ϣ�\n1.���Ѽ�\t2.��˿��\t3.��ע�˼�\t4.��Ȥ���ü�\n"); scanf("%d", &choice); getchar();
					switch (choice)
					{
					case 1:case 2:case 3:case 4:re = 1; agg1 = aggregate(T, choice); break;
					default:printf("�����������������");
					}
				}

				printf("��B�������ڳ�Ա��ĳһ���ϣ���\nB������Ա�����֤�ţ�"); scanf("%s", id);	getchar();
				T1 = SearchAVL(F->HeadNode->lchild, id, 2);
				if (T1 == NULL)
				{
					printf("û���ҵ���Ա%s��", id);
					getchar(); break;
				}
				re = 0;
				while (re == 0)
				{
					printf("BΪ�ý�����һ���ϣ�\n1.���Ѽ�\t2.��˿��\t3.��ע�˼�\t4.��Ȥ���ü�\n"); scanf("%d", &choice2); getchar();
					switch (choice2)
					{
					case 1:case 2:case 3:case 4:re = 1; agg2 = aggregate(T1, choice2); break;
					default:printf("�����������������");
					}
				}

				if (agg1 == NULL)
					printf("����Aδ��ʼ�����޷������жϣ�");
				else if (agg2 == NULL)
					printf("����Bδ��ʼ�����޷������жϣ�");
				if (set_diffrence1(agg1, agg2) == OK)
					printf("\n������ɹ���");
			}
			getchar();
			break;
		case 14:
			if (F == NULL)
				printf("��ǰû�л����\n");
			else  
				printf("�ü����г�Ա����Ϊ��%d��", set_size(F->HeadNode->lchild));
			getchar();
			break;
		case 15:
			if (F == NULL)
				printf("��ǰû�л����\n");
			else  if (F->HeadNode->lchild == NULL)
				printf("�û��Ϊ�������ж�ʧ�ܣ�");
			else
			{
				printf("��������Ҫ���ҵĳ�Ա�����֤�ţ�"); scanf("%s", id);	getchar();
				if (set_member(F->HeadNode->lchild, id) == OK)
					printf("��Ԫ���Ǹü��ϳ�Ա��");
				else
					printf("��Ԫ�ز��Ǹü��ϳ�Ա��");
			}
			getchar();
			break;
		case 16:
			if (F == NULL)
				printf("��ǰû�л����\n");
			else  if (F->HeadNode->lchild == NULL)
				printf("�û��Ϊ�������ж�ʧ�ܣ�");
			else
			{
				printf("����AΪB���Ӽ�����\nA������Ա�����֤�ţ�"); scanf("%s", id);	getchar();
				T = SearchAVL(F->HeadNode->lchild, id, 2);
				if (T == NULL)
				{
					printf("û���ҵ���Ա%s��", id);
					getchar(); break;
				}
				re = 0;
				while (re == 0)
				{
					printf("AΪ�ý�����һ���ϣ�\n1.���Ѽ�\t2.��˿��\t3.��ע�˼�\t4.��Ȥ���ü�\n"); scanf("%d", &choice); getchar();
					switch (choice)
					{
					case 1:case 2:case 3:case 4:re = 1; agg1 = aggregate(T, choice); break;
					default:printf("�����������������");
					}
				}

				printf("����AΪB���Ӽ�����\nB������Ա�����֤�ţ�"); scanf("%s", id);	getchar();
				T1 = SearchAVL(F->HeadNode->lchild, id, 2);
				if (T1 == NULL)
				{
					printf("û���ҵ���Ա%s��", id);
					getchar(); break;
				}
				re = 0;
				while (re == 0)
				{
					printf("BΪ�ý�����һ���ϣ�\n1.���Ѽ�\t2.��˿��\t3.��ע�˼�\t4.��Ȥ���ü�\n"); scanf("%d", &choice2); getchar();
					switch (choice2)
					{
					case 1:case 2:case 3:case 4:re = 1; agg2 = aggregate(T1, choice2); break;
					default:printf("�����������������");
					}
				}

				if (agg1 == NULL)
					printf("����Aδ��ʼ�����޷������жϣ�");
				else if (agg2 == NULL)
					printf("����Bδ��ʼ�����޷������жϣ�");
				if (set_subset(agg1->lchild, agg2->lchild) == OK)
					printf("�������A������B���ϵ��Ӽ���");
				else 
					printf("�������A���ϲ���B���ϵ��Ӽ���");
			}
			getchar();
			break;
		case 17:
			if (F == NULL)
				printf("��ǰû�л����\n");
			else  if (F->HeadNode->lchild == NULL)
				printf("�û��Ϊ�������ж�ʧ�ܣ�");
			else
			{
				printf("����A������B������ͬ����\nA������Ա�����֤�ţ�"); scanf("%s", id);	getchar();
				T = SearchAVL(F->HeadNode->lchild, id, 2);
				if (T == NULL)
				{
					printf("û���ҵ���Ա%s��", id);
					getchar(); break;
				}
				re = 0;
				while (re == 0)
				{
					printf("AΪ�ý�����һ���ϣ�\n1.���Ѽ�\t2.��˿��\t3.��ע�˼�\t4.��Ȥ���ü�\n"); scanf("%d", &choice); getchar();
					switch (choice)
					{
					case 1:case 2:case 3:case 4:re = 1;  agg1 = aggregate(T, choice); break;
					default:printf("�����������������");
					}
				}

				printf("����A������B������ͬ����\nB������Ա�����֤�ţ�"); scanf("%s", id);	getchar();
				T1 = SearchAVL(F->HeadNode->lchild, id, 2);
				if (T1 == NULL)
				{
					printf("û���ҵ���Ա%s��", id);
					getchar(); break;
				}
				re = 0;
				while (re == 0)
				{
					printf("BΪ�ý�����һ���ϣ�\n1.���Ѽ�\t2.��˿��\t3.��ע�˼�\t4.��Ȥ���ü�\n"); scanf("%d", &choice2); getchar();
					switch (choice2)
					{
					case 1:case 2:case 3:case 4:re = 1; agg2 = aggregate(T1, choice2); break;
					default:printf("�����������������");
					}
				}

				if (agg1 == NULL)
					printf("����Aδ��ʼ�����޷������жϣ�");
				else if (agg2 == NULL)
					printf("����Bδ��ʼ�����޷������жϣ�");
				if (set_equal(agg1->lchild, agg2->lchild) == OK)
					printf("�������A���Ϻ�B������ͬ��");
				else
					printf("�������A���Ϻ�B���ϲ���ͬ��");
			}
			getchar();
			break;
		case 18:
			if (F == NULL)
				printf("��ǰû�л����\n");
			else  if (F->HeadNode->lchild == NULL)
				printf("�û��Ϊ��������ʼ��ʧ�ܣ�");
			else
			{
				printf("��������Ҫ��ʼ���ĳ�Ա�����֤�ţ�"); scanf("%s", id); getchar();
				T = SearchAVL(F->HeadNode->lchild, id, 2);
				if (T == NULL)
					printf("û���ҵ���Ա%s��", id);
				else
				{
					re = 0;
					while (re == 0)
					{
						printf("ѡ����Ҫ�����Ķ���\n1.���Ѽ�\t2.��˿��\t3.��ע�˼�\t4.��Ȥ���ü�\n"); scanf("%d", &choice); getchar();
						switch (choice)
						{
						case 1:case 2:case 3:case 4:re = 1; break;
						default:printf("�������������");
						}
					}
					if (aggregate_init(&T, choice) == OK)
						printf("��ʼ�����ϳɹ���");
					else
						printf("��ʼ������ʧ�ܣ�");
				}
			}
			getchar();
			break;
		case 19:
			if (F == NULL)
				printf("��ǰû�л����\n");
			else  if (F->HeadNode->lchild == NULL)
				printf("�û��Ϊ�������ж�ʧ�ܣ�");
			else
			{
				printf("��������Ҫ�����ĳ�Ա�����֤�ţ�"); scanf("%s", id);	getchar();
				T = SearchAVL(F->HeadNode->lchild, id, 2);
				if (T == NULL)
				{
					printf("û���ҵ���Ա%s��", id);
					getchar(); break;
				}
				re = 0;
				while (re == 0)
				{
					printf("��������Ҫ�����ļ��ϣ�1.���Ѽ�  2.��˿��  3.��ע�˼�  4.��Ȥ���ü�  0.Exit\n"); scanf("%d", &choice); getchar();
					switch (choice)
					{
					case 1:case 2:case 3:case 4:
						agg1 = aggregate(T, choice);
						if (agg1 == NULL)
						{
							printf("����δ��ʼ�������ܽ��в�����");
							re = 1; break;
						}
						operate_aggregate(F->HeadNode->lchild,T, choice);
						break;
					case 0:re = 1;  printf("���˳��ɹ���"); break;
					default:printf("�������");
					}
				}
			}
			getchar();
			break;
		case 20:
			if (F == NULL)
				printf("��ǰû�л����\n");
			else  if (F->HeadNode->lchild == NULL)
				printf("�û��Ϊ�������ж�ʧ�ܣ�");
			else
			{
				printf("A���ϣ�������Ա�����֤�ţ�"); scanf("%s", id);	getchar();
				T = SearchAVL(F->HeadNode->lchild, id, 2);
				if (T == NULL)
				{
					printf("û���ҵ���Ա%s��",id);
					getchar(); break;
				}
				printf("B���ϣ�������Ա�����֤�ţ�"); scanf("%s", id);	getchar();
				T1 = SearchAVL(F->HeadNode->lchild, id, 2);
				if (T1 == NULL)
				{
					printf("û���ҵ���Ա%s��", id);
					getchar(); break;
				}
				re = 0;
				while (re == 0)
				{
					printf("��ѡ�������1. common_friends  2. common_fans  3. common_concerns  4.common_hobbies  0.exit\n"); scanf("%d", &choice); getchar();
					switch (choice)
					{
					case 1: case 2:case 3:case 4:
						agg1 = aggregate(T, choice); agg2 = aggregate(T1, choice);
						search_common(agg1, agg2); printf("\n");
						break;
					case 0:re = 1; printf("�ѳɹ��˳���"); break;
					default:printf("�������");
					}
				}
			}
			getchar();
			break;
		case 21:
			if (F == NULL)
				printf("��ǰû�л����\n");
			else  if (F->HeadNode->lchild == NULL)
				printf("�û��Ϊ�������ж�ʧ�ܣ�");
			else
			{
				printf("A���ϣ�������Ա�����֤�ţ�"); scanf("%s", id);	getchar();
				T = SearchAVL(F->HeadNode->lchild, id,2);
				if (T == NULL)
					printf("û���ҵ���Ա%s�����Ҷ��Ⱥ���ʧ�ܣ�",id);
				else if (T->data.friends == NULL)
					printf("���Ѽ���δ��ʼ�������Ҷ��Ⱥ���ʧ�ܣ�");
				else
				{
					second_friends(F->HeadNode->lchild, T);
					printf("\n������ϣ�");
				}
			}
			getchar();
			break;
		case 22:
			if (head == NULL)
				printf("��ǰû�л����\n");
			else
			{
				j = 0;
				Traverse(head);
				printf("������Ҫ�л���AVL�������֣�"); scanf("%s", name); getchar();
				F1 = ExAVL(head, name);
				if (F1 == NULL)
					printf("��������ֲ����ڣ��л�ʧ�ܣ�\n");
				else
				{
					F = F1;
					printf("�л��ɹ���");
				}
			}
			getchar();
			break;
		case 23:
			if (SaveData(F) == OK)
				printf("����д���ļ��ɹ���");
			else
				printf("����д���ļ�ʧ�ܣ�");
			getchar();
			break;
		case 24:
			if (F == NULL)
				printf("��ǰû�л����\n");
			else  if (F->HeadNode->lchild != NULL)
				printf("��ǰ������Ѵ������ݣ�����¼�����ݣ�");
			else if (LoadData(F) == OK)
				printf("¼�����ݳɹ���");
			else
				printf("¼������ʧ�ܣ�");
			getchar();
			break;
		case 25:
			if (F == NULL)
				printf("��ǰû�л����\n");
			else  if (F->HeadNode->lchild != NULL)
				printf("��ǰ������Ѵ������ݣ���������������ݣ�");
			else
			{
				printf("���������ݹ�ģ��"); scanf("%d", &choice); getchar();
				if (random(F->HeadNode, choice) == OK)
					printf("������ɳɹ���");
				else
					printf("�������ʧ�ܣ�");
			}
			getchar();
			break;
		default:
			printf("����ѡ������Ч�����룡\n");
			getchar();
			break;
		}
	}
	return 0;
}

/******************
�������ƣ�random
������������ǰAVL����ͷָ�룬���ݹ�ģgross
�������ܣ��������AVL���ĳ�Ա
����ֵ���ɹ�����OK��ʧ�ܷ���ERROR
*******************/
int random(BSTNode *T, int gross)
{
	srand(time(NULL));
	int i=0,id;
	TElemType data;
	FILE *fp=NULL;
	printf("��������������ݣ����Եȡ�����\n");
	char name[1000][20];//�洢���ļ�����������
	if ((fp = fopen("name.txt", "r")) == NULL)
	{
		printf("name.txt��ʧ�ܣ�");
		return ERROR;
	}
	while (!feof(fp))
	{
		fscanf(fp, "%s", name[i]);
		if (strcmp(name[i], "#") == 0)break;
		i++;
	}
	for (; i < 1000; i++) strcpy(name[i], "#");
	for (i = 1; i <= gross; i++)
	{
		id = rand() % gross + 1;
		sprintf(data.id, "%d", id);
		strcpy(data.name,name[i-1]);
		data.friends = data.concern= data.fan =data.hobby = NULL;
		if (InsertAVL(T, data) == ERROR)i--;
	} 
	i = 0;
	if ((fp = fopen("hobby.txt", "r")) == NULL)
	{
		printf("hobby.txt��ʧ�ܣ�");
		return ERROR;
	}
	char hobby[60][20];
	while (!feof(fp))
	{
		fscanf(fp, "%s", hobby[i]);
		if (strcmp(hobby[i], "#") == 0)break;
		i++;	if (i >= 60)break;
	}
	for (; i < 60; i++) strcpy(hobby[i], "#");
	random1(T, T->lchild, gross, hobby);
	fclose(fp);
	return OK;
}
/******************
�������ƣ�random1
������������ǰAVL���ı���ָ��F����ǰ���T�����ݹ�ģgross�����ü���hobby
�������ܣ��������AVL���ĳ�Ա
����ֵ���ɹ�����OK��ʧ�ܷ���ERROR
*******************/
int random1(BSTNode *F,BSTNode *T, int gross,char hobby[60][20])
{
	if (T == NULL)
		return OK;
	int j,k; char id[20];

	k = rand() % (gross/2);
	if (T->data.friends == NULL)
		aggregate_init(&T, 1);
	for (int i = 1; i <=k; i++)
	{
		j = rand() % gross + 1;
		sprintf(id, "%d", j);
		aggregate_insert(F->lchild,T->data.friends,1,id);
	}

	k = rand() % (gross/2);
	if (T->data.fan == NULL)
		aggregate_init(&T, 2);
	for (int i = 1; i <= k; i++)
	{
		j = rand() % gross + 1;
		sprintf(id, "%d", j);
		aggregate_insert(F->lchild, T->data.fan, 2, id);
	}

	k = rand() % (gross/2);
	if (T->data.concern == NULL)
		aggregate_init(&T, 3);
	for (int i = 1; i <= k; i++)
	{
		j = rand() % gross + 1;
		sprintf(id, "%d", j);
		aggregate_insert(F->lchild, T->data.concern, 3, id);
	}

	k = rand() % (gross/2);
	if (T->data.hobby == NULL)
		aggregate_init(&T, 4);
	if (k > 60)k= 60;
	for (int i = 1; i <= k; i++)
	{
		j = rand() % 60;
		strcpy(id, hobby[j]);
		aggregate_insert(F->lchild, T->data.hobby, 4, id);
	}
	random1(F,T->lchild, gross,hobby);
	random1(F,T->rchild, gross,hobby);
	return OK;
}
/******************
�������ƣ�LoadData
�����������ļ�ָ��fp����ǰAVL���ı���ָ��F
�������ܣ���ָ���ļ��е����ݶ��뵱ǰAVL����
����ֵ���ɹ�����OK��ʧ�ܷ���ERROR
*******************/
int LoadData(Forest*F)
{
	FILE*fp1 = NULL, *fp2 = NULL, *fp3 = NULL, *fp4 = NULL, *fp5 = NULL;
	printf("����¼��name���ݣ����Եȡ�����\n");
	if ((fp1 = fopen("newname.txt", "r")) == NULL)
	{
		printf("newname.txt��ʧ�ܣ�");
		return ERROR;
	}
	char id[20]; char name[20];
	fscanf(fp1, "%s", id);
	fscanf(fp1, "%s", name);
	while (!feof(fp1))
	{
		TElemType data;
		strcpy(data.name, name);strcpy(data.id, id);
		data.concern = data.fan = data.friends = data.hobby = NULL;
		InsertAVL(F->HeadNode, data);
		fscanf(fp1, "%s", id);
		fscanf(fp1, "%s", name);
	}
	fclose(fp1);
	int num = set_size(F->HeadNode->lchild);
	printf("����¼��friends���ݣ����Եȡ�����\n");
	if ((fp2 = fopen("newfriends.txt", "r")) == NULL)
	{
		printf("newfriends.txt��ʧ�ܣ�");
		return ERROR;
	}
	BSTNode*T = NULL;
	for (int i = 1; i <= num; i++)
	{
		fscanf(fp2, "%s", id);
		fscanf(fp2, "%s", name);
		T = SearchAVL(F->HeadNode->lchild, id,2);
		while (1)
		{
			fscanf(fp2, "%s", id);if(strcmp(id, "#") == 0)break;
			fscanf(fp2, "%s", name);
			aggregate_init(&T,1);
			aggregate_insert(F->HeadNode->lchild, T->data.friends, 1, id);
		}
	}
	fclose(fp2);
	printf("����¼��fan���ݣ����Եȡ�����\n");
	if ((fp3 = fopen("newfan.txt", "r")) == NULL)
	{
		printf("newfan.txt��ʧ�ܣ�");
		return ERROR;
	}
	for (int i = 1; i <= num; i++)
	{
		fscanf(fp3, "%s", id); 
		fscanf(fp3, "%s", name);
		T = SearchAVL(F->HeadNode->lchild, id, 2);
		while (1)
		{
			fscanf(fp3, "%s", id); if (strcmp(id, "#") == 0)break;
			fscanf(fp3, "%s", name);
			aggregate_init(&T,2);
			aggregate_insert(F->HeadNode->lchild, T->data.fan, 2, id);
		}
	}
	fclose(fp3);
	printf("����¼��concern���ݣ����Եȡ�����\n");
	if ((fp4 = fopen("newconcern.txt", "r")) == NULL)
	{
		printf("newconcern.txt��ʧ�ܣ�");
		return ERROR;
	}
	for (int i = 1; i <= num; i++)
	{
		fscanf(fp4, "%s", id);
		fscanf(fp4, "%s", name);
		T = SearchAVL(F->HeadNode->lchild, id, 2);
		while (1)
		{
			fscanf(fp4, "%s", id); if (strcmp(id, "#") == 0)break;
			fscanf(fp4, "%s", name);
			aggregate_init(&T,3);
			aggregate_insert(F->HeadNode->lchild, T->data.concern, 3, id);
		}
	}
	fclose(fp4);
	printf("����¼��hobby���ݣ����Եȡ�����\n");
	if ((fp5 = fopen("newhobby.txt", "r")) == NULL)
	{
		printf("newhobby.txt��ʧ�ܣ�");
		return ERROR;
	}
	for (int i = 1; i <= num; i++)
	{
		fscanf(fp5, "%s", id);
		fscanf(fp5, "%s", name);
		T = SearchAVL(F->HeadNode->lchild, id, 2);
		while (1)
		{
			fscanf(fp5, "%s", id);if (strcmp(id, "#") == 0)break;
			fscanf(fp5, "%s", name);
			aggregate_init(&T,4);
			aggregate_insert(F->HeadNode->lchild, T->data.hobby, 4, id);
		}
	}
	fclose(fp5);
	return OK;
}
/******************
�������ƣ�SaveData2
�����������ļ�ָ��fp����ǰAVL���Ľ��T
�������ܣ�����ǰAVL�������ݴ���ָ���ļ�
����ֵ���ɹ�����OK��ʧ�ܷ���ERROR
*******************/
int SaveData2(FILE *fp, BSTNode*T)
{
	if (T) {
		SaveData2(fp, T->lchild);

		fprintf(fp, "%s %s",T->data.id,T->data.name); 
		j++; if (j % 20 == 0)fprintf(fp, "\n");else fprintf(fp, " ");

		SaveData2(fp, T->rchild);
	}
	return OK;
}
/******************
�������ƣ�SaveData1
�����������ļ�ָ��fp����ǰAVL���Ľ��T������ѡ��choice
�������ܣ�����ǰAVL�������ݴ���ָ���ļ�
����ֵ���ɹ�����OK��ʧ�ܷ���ERROR
*******************/
int SaveData1(FILE *fp, BSTNode*T,int choice)
{
	if (T) 
	{
		SaveData1(fp, T->lchild, choice);

		fprintf(fp, "%s %s ", T->data.id, T->data.name);
		switch (choice)
		{
			case 1:j = 0;
				if (T->data.friends != NULL)
					SaveData2(fp, T->data.friends->lchild); 
				break;
			case 2:j = 0;
				if (T->data.fan != NULL)
					SaveData2(fp, T->data.fan->lchild);
				break;
			case 3:j = 0;
				if (T->data.concern != NULL)
					SaveData2(fp, T->data.concern->lchild);
				break;
			case 4:j = 0;
				if (T->data.hobby != NULL)
					SaveData2(fp, T->data.hobby->lchild);
				break;
		}
		fprintf(fp, "#\n");

		SaveData1(fp,T->rchild,choice);
	}
	return OK;
}
/******************
�������ƣ�SaveData
�����������ļ�ָ��fp����ǰAVL���ı���ָ��F
�������ܣ�����ǰAVL�������ݴ���ָ���ļ�
����ֵ���ɹ�����OK��ʧ�ܷ���ERROR
*******************/
int SaveData(Forest*F)
{
	FILE*fp1=NULL,*fp2=NULL, *fp3=NULL, *fp4=NULL, *fp5=NULL;
	BSTNode*T = NULL;
	printf("���ڱ���name���ݣ����Եȡ�����\n");
	j = 0;
	if ((fp1 = fopen("newname.txt", "w")) == NULL)
	{
		printf("newname.txt��ʧ�ܣ�");
		return ERROR;
	}
	if(F==NULL)fprintf(fp1, "");
	else
	{
		T = F->HeadNode->lchild;
		if (T == NULL)fprintf(fp1, "");
		else
		{
			if (SaveData2(fp1, T) == ERROR)
			{
				fclose(fp1);
				return ERROR;
			}
		}
	}
	fclose(fp1);
	printf("���ڱ���friends���ݣ����Եȡ�����\n");
	if ((fp2 = fopen("newfriends.txt", "w")) == NULL)
	{
		printf("newfriends.txt��ʧ�ܣ�");
		return ERROR;
	}
	if (F == NULL)fprintf(fp2, "");
	else
	{
		T = F->HeadNode->lchild;
		if (T == NULL)fprintf(fp2, "");
		else
		{
			if (SaveData1(fp2, T, 1) == ERROR)
			{
				fclose(fp2);
				return ERROR;
			}
		}
	}
	fclose(fp2);
	printf("���ڱ���fan���ݣ����Եȡ�����\n");
	if ((fp3 = fopen("newfan.txt", "w")) == NULL)
	{
		printf("newfan.txt��ʧ�ܣ�");
		return ERROR;
	}
	if (F == NULL)fprintf(fp2, "");
	else
	{
		T = F->HeadNode->lchild;
		if (T == NULL)fprintf(fp3, "");
		else
		{
			if (SaveData1(fp3, T, 2) == ERROR)
			{
				fclose(fp3);
				return ERROR;
			}
		}
	}
	fclose(fp3);
	printf("���ڱ���concern���ݣ����Եȡ�����\n");
	if ((fp4 = fopen("newconcern.txt", "w")) == NULL)
	{
		printf("newconcern.txt��ʧ�ܣ�");
		return ERROR;
	}
	if (F == NULL)fprintf(fp2, "");
	else
	{
		T = F->HeadNode->lchild;
		if (T == NULL)fprintf(fp4, "");
		else
		{
			if (SaveData1(fp4, T, 3) == ERROR)
			{
				fclose(fp4);
				return ERROR;
			}
		}
	}
	fclose(fp4);
	printf("���ڱ���hobby���ݣ����Եȡ�����\n");
	if ((fp5 = fopen("newhobby.txt", "w")) == NULL)
	{
		printf("newhobby.txt��ʧ�ܣ�");
		return ERROR;
	}
	if (F == NULL)fprintf(fp2, "");
	else
	{
		T = F->HeadNode->lchild;
		if (T == NULL)fprintf(fp5, "");
		else
		{
			if (SaveData1(fp5, T, 4) == ERROR)
			{
				fclose(fp5);
				return ERROR;
			}
		}
	}
	fclose(fp5);
	return OK;
}
/******************
�������ƣ�Traverse
����������ɭ�ֵ�ͷ���head
�������ܣ�������AVL���������������ͬʱ�����ź����ƣ�����1�����
����ֵ����
*******************/
void Traverse(Forest *head)
{
	Forest *p = head->next;
	if (p == NULL)
		printf("��ǰ�������ڣ�\n");
	while (p)
	{
		printf("�������֣�%s ���ĳ�Ա������%d\n", p->name, set_size(p->HeadNode->lchild));
		if (p->HeadNode->lchild == NULL)
			printf("����Ϊ������");
		else
			TraverseAVL(p->HeadNode->lchild);
		printf("\n\n");
		p = p->next;
	}
	printf("����������");
}
/******************
�������ƣ�ExAVL
����������ɭ�ֵ�ͷ���head������name
�������ܣ�������л�Ϊ����Ϊname��AVL��
����ֵ���ɹ�����ָ���л�������ı���ָ�룬ʧ�ܷ���NULL
*******************/
Forest *ExAVL(Forest *head, char name[20])
{
	Forest *q = head->next;
	while (q)
	{
		if (strcmp(q->name, name) == 0)
			break;
		q = q->next;
	}
	return q;
}

/******************
�������ƣ�operate_aggregate
����������AVL���ĸ����root�������������T������ѡ��choice
�������ܣ���ָ�����Ͻ������١�����ɾ�����޸ġ����ҡ�������ͳ�ƹ�ģ�Ĳ���
����ֵ������OK
*******************/
int operate_aggregate(BSTNode*root, BSTNode*T, int choice)
{
	BSTNode*node = NULL,*T1=NULL;
	char s[100];
	switch (choice)
	{
	case 1:T1 = T->data.friends; break;
	case 2:T1 = T->data.fan; break;
	case 3:T1 = T->data.concern; break;
	case 4:T1 = T->data.hobby; break;
	}
	int op = 1, re = 0; char id[20], id2[20];
	while (op)
	{
		show1();
		scanf("%d", &op); getchar();
		switch (op)
		{
		case 0:
			printf("���˳��Ե�ǰ���ϵĲ�����\n");
			break;
		case 1:
			if (DestroyAVL(T1->lchild) == OK)
			{
				switch (choice)
				{
				case 1:T->data.friends = NULL; break;
				case 2:T1 = T->data.fan = NULL; break;
				case 3:T1 = T->data.concern = NULL; break;
				case 4:T1 = T->data.hobby = NULL; break;
				}
				Delete(root, T->data.id, choice);
				printf("�������ٳɹ���\n");
			}
			else
				printf("����ʧ�ܣ�\n");
			break;
		case 2:
			printf("������Ҫ����ĳ�Ա�����֤�ţ������Ա���Կո�Ͽ�����");
			fgets(s, 100, stdin);
			for (int i = 0, j = 0; i < 100; i++)
			{
				if (s[i] == ' ' || s[i] == '\n')
				{
					id[j] = '\0'; j = 0;
					if (aggregate_insert(root, T1, choice, id) == OK)
						printf("��Ա%s����ɹ���\n", id);
					else
						printf("��Ա%s����ʧ�ܣ�\n", id);
				}
				else
				{
					id[j] = s[i];  j++;
				}
			}
			break;
		case 3:
			printf("������Ҫɾ���ĳ�Ա�����֤�ţ������Ա���Կո�Ͽ�����"); fgets(s, 100, stdin);
			for (int i = 0, j = 0; i < 100; i++)
			{
				if (s[i] == ' ' || s[i] == '\n')
				{
					id[j] = '\0'; j = 0;
					if (aggregate_remove(root, T1, choice, id) == OK)
						printf("��Ա%sɾ���ɹ���\n",id);
					else
						printf("��Ա%s�����ڣ�ɾ��ʧ�ܣ�\n",id);
				}
				else
				{
					id[j] = s[i];  j++;
				}
			}
			break;
		case 4:
			printf("�������޸�ǰ�ĳ�Ա�����֤�ţ�"); scanf("%s", id); getchar();
			if (SearchAVL(T1->lchild, id, 2) != NULL)
			{
				printf("�������޸ĺ�ĳ�Ա�����֤�ţ�"); scanf("%s", id2); getchar();
				if (SearchAVL(T1->lchild, id, 2) != NULL)
				{
					if (aggregate_remove(root, T1, choice, id) == OK)
					{
						aggregate_insert(root, T1, choice, id2);printf("�޸ĳɹ���\n");
					}
				}
				else
					printf("���������֤��Ϊ%s�ĳ�Ա���޸�ʧ�ܣ�\n", id2);
			}
			else
				printf("���������֤��Ϊ%s�ĳ�Ա���޸�ʧ�ܣ�\n", id);
			break;
		case 5:
			printf("������Ҫ���ҵĳ�Ա�����֤�ţ�"); scanf("%s", id); getchar();
			node = SearchAVL(T1->lchild, id, 2);
			if (node == NULL)
				printf("���������֤��Ϊ%s�ĳ�Ա������ʧ�ܣ�\n", id);
			else
				printf("���ҳɹ���\n���֤�ţ�%s  ���ƣ�%s\n", node->data.id, node->data.name);
			break;
		case 6:
			if (T1->lchild == NULL)
				printf("����Ϊ�ռ���");
			else
			{
				j = 0;
				printf("���������\n");
				TraverseAVL2(T1->lchild);
				j = 0;
				printf("\n���������\n");
				TraverseAVL(T1->lchild);
			}
			printf("\n");
			break;
		case 7:
			printf("�ü����г�Ա����Ϊ��%d��\n", set_size(T1->lchild)); 
			break;
		default:
			printf("����ѡ������Ч�����룡\n");
			break;
		}
	}
	return OK;
}
/******************
�������ƣ�show1
������������
�������ܣ���ʾ���ڼ��ϲ�����α�˵�����
����ֵ����
*******************/
void show1()
{
	printf("1. Destroy  2. Insert  3. Delete  4. Revise  5. Search  6. Traverse  7. Size 0. Exit\n");
}

/******************
�������ƣ�aggregate_remove
������������ǰAVL���ĸ����T����Ҫ����ɾ���ļ��������ڵĳ�Ա��㣬����ѡ��choice�����֤��id
�������ܣ�����Ӧ����ɾ��һ�����֤��id�ĳ�Ա
����ֵ���ɹ�����OK��ʧ�ܷ���ERROR
*******************/
int aggregate_remove(BSTNode*T1, BSTNode*T, int choice, char id[20])
{
	BSTNode*node = NULL;
	if (choice == 4)
		node = SearchAVL(T->lchild, id, 2);
	else
		node = SearchAVL(T1, id, 2);
	if (node == NULL)
	{
		printf("û���ҵ����������Ľ�㣬");
		return ERROR;
	}
	if (T == NULL)
	{
		printf("�ü���δ��ʼ����");
		return ERROR;
	}
	switch (choice)
	{
	case 1:
		if (DeleteAVL(T, id) == OK)
		{
			DeleteAVL(node->data.friends, T->data.id);
			return OK;
		}
		else return ERROR;
	case 2:
		if (DeleteAVL(T, id) == OK)
		{
			DeleteAVL(node->data.concern, T->data.id);
			return OK;
		}
		else return ERROR;
	case 3:
		if (DeleteAVL(T, id) == OK)
		{
			DeleteAVL(node->data.fan, T->data.id);
			return OK;
		}
		else return ERROR;
	case 4://ɾ��T�İ��ü��������֤��Ϊid�Ľ�㣬����Ҫ����ɾ��
		if (DeleteAVL(T, id) == OK)return OK;
	}
	return ERROR;
}
/******************
�������ƣ�aggregate_insert
����������AVL���ĸ���㣬��Ҫ���в���ļ��������ڵĳ�Ա��㣬����ѡ��choice�����֤��id
�������ܣ�����Ӧ���ϲ���һ�����֤��id�ĳ�Ա
����ֵ���ɹ�����OK��ʧ�ܷ���ERROR
*******************/
int aggregate_insert(BSTNode*T1, BSTNode*T, int choice, char id[20])
{
	if (strcmp(T->data.id, id) == 0)return ERROR;
	BSTNode*node = NULL;
	if (choice == 4)//��������ʱ���ü��ϣ���name��Ϊ0����id�д��밮��
	{
		node = (BSTNode*)malloc(sizeof(BSTNode));
		strcpy(node->data.id, id); strcpy(node->data.name, "0");
		node->data.concern = NULL; node->data.friends = NULL;
		node->data.fan = NULL; node->data.hobby = NULL;
		node->lchild = node->rchild = NULL;
	}
	else//������ǣ�����AVL���в��ҵ����֤��Ϊid�Ľ�㣬�Ա�ʵ�ַ������
	{
		node = SearchAVL(T1, id, 2);
		if (node == NULL)
		{
			printf("û���ҵ����������Ľ�㣬");
			return ERROR;
		}
	}
	if (T == NULL)
	{
		printf("�ü���δ��ʼ����");
		return ERROR;
	}
	else if (SearchAVL(T->lchild, id, 2) != NULL)
		return ERROR;
	//��T�ĺ��Ѽ����в���node.data����node�ĺ��Ѽ��ϲ���T.data
	if (InsertAVL(T, node->data) == OK&&InsertAVL2(node, choice, T->data) == OK)
		return OK;
	return ERROR;
}
/******************
�������ƣ�InsertAVL2
����������AVL����ͷ��㣬����ѡ��choice�����ݽṹdata
�������ܣ�����һ��������Ϊdata�Ľ�㣨���������Ƽ��ϣ����ڼ���δ��ʼ��ʱ�����г�ʼ�����ϣ�
����ֵ���ɹ�����OK��ʧ�ܷ���ERROR
*******************/
int InsertAVL2(BSTNode*T1, int choice, TElemType data)
{
	BSTNode*T = NULL;
	switch (choice)
	{
	case 1:
		if (T1->data.friends == NULL)//������û�г�ʼ�������ȳ�ʼ��
			aggregate_init(&T1, 1);
		T = T1->data.friends->lchild;
		if (T == NULL)
		{
			T = (struct BSTNode*)malloc(sizeof(struct BSTNode));
			T->BF = 0; T->data = data;
			T->lchild = NULL; T->rchild = NULL;
			T1->data.friends->lchild = T;
			return OK;
		}
		break;
	case 2:
		if (T1->data.concern == NULL)//������û�г�ʼ�������ȳ�ʼ��
			aggregate_init(&T1, 3);
		T = T1->data.concern->lchild;
		if (T == NULL)
		{
			T = (struct BSTNode*)malloc(sizeof(struct BSTNode));
			T->BF = 0; T->data = data;
			T->lchild = NULL; T->rchild = NULL;
			T1->data.concern->lchild = T;
			return OK;
		}
		break;
	case 3:
		if (T1->data.fan == NULL)//������û�г�ʼ�������ȳ�ʼ��
			aggregate_init(&T1, 2);
		T = T1->data.fan->lchild;
		if (T == NULL)
		{
			T = (struct BSTNode*)malloc(sizeof(struct BSTNode));
			T->BF = 0; T->data = data;
			T->lchild = NULL; T->rchild = NULL;
			T1->data.fan->lchild = T;
			return OK;
		}
		break;
	case 4:return OK;
	}

	BSTNode*pre = NULL, *current = T;
	while (current != NULL)
	{
		if (strcmp(current->data.id, data.id) == 0)
			return ERROR;
		pre = current;
		current = (strcmp(data.id, pre->data.id)>0) ? pre->rchild : pre->lchild;
	}
	current = (struct BSTNode*)malloc(sizeof(struct BSTNode)); current->BF = 0; current->data = data;
	current->lchild = NULL; current->rchild = NULL;
	if (strcmp(data.id, pre->data.id)>0)  pre->rchild = current;
	else pre->lchild = current;

	switch (choice)
	{
	case 1:
		T1->data.friends->lchild = Balance(T);
		if (T1->data.friends->lchild != NULL)
			return OK;
	case 2:
		T1->data.concern->lchild = Balance(T);
		if (T1->data.concern->lchild != NULL)
			return OK;
	case 3:
		T1->data.fan->lchild = Balance(T);
		if (T1->data.fan->lchild != NULL)
			return OK;
	}
	return ERROR;
}
/******************
�������ƣ�aggregate_destroy
������������ǰ���в����ļ��������ĳ�Ա��㣬����ѡ��choice
�������ܣ����ٵ�ǰAVL��
����ֵ���ɹ�����OK��ʧ�ܷ���ERROR
*******************/
int aggregate_destroy(BSTNode*T, int choice)
{
	switch (choice)
	{
	case 1:
		if (T->data.friends == NULL)
			return ERROR;
		DestroyAVL(T->data.friends->lchild);
		T->data.friends = NULL;
		break;
	case 2:
		if (T->data.fan == NULL)
			return ERROR;
		DestroyAVL(T->data.fan->lchild);
		T->data.fan = NULL;
		break;
	case 3:
		if (T->data.concern == NULL)
			return ERROR;
		DestroyAVL(T->data.concern->lchild);
		T->data.concern = NULL;
		break;
	case 4:
		if (T->data.hobby == NULL)
			return ERROR;
		DestroyAVL(T->data.hobby->lchild);
		T->data.hobby = NULL;
		break;
	}
	return OK;
}
/******************
�������ƣ�Delete
������������ǰ���в�����AVL���ĸ���㣬���������ĳ�Ա���֤�ţ�����ѡ��choice
�������ܣ�ɾ����ԭ�������������ٵ�
����ֵ���ɹ�����OK��ʧ�ܷ���ERROR
*******************/
int Delete(BSTNode*F, char id[20], int choice)
{
	if (F == NULL)
		return OK;
	BSTNode*node = NULL;
	switch (choice)
	{
	case 1://����ɾ��F�����Ѽ��е�idΪT.data.id�ĳ�Ա
		if (F->data.friends == NULL)return OK;
		DeleteAVL(F->data.friends, id);
		break;
	case 2://����ɾ��F����ע�˼��е�idΪT.data.id�ĳ�Ա
		if (F->data.concern == NULL)return OK;
		DeleteAVL(F->data.concern, id); break;
	case 3://����ɾ��F����˿���е�idΪT.data.id�ĳ�Ա
		if (F->data.fan == NULL)return OK;
		DeleteAVL(F->data.fan, id); break;
	case 4:return OK;//���ü��ϲ���Ҫ����ɾ��
	}
	Delete(F->lchild, id, choice); Delete(F->rchild, id, choice);
	return OK;
}
/******************
�������ƣ�aggregate_init
������������ǰ���в����ļ��������ĳ�Ա��㣬����ѡ��choice
�������ܣ���ʼ������
����ֵ���ɹ�����OK��ʧ�ܷ���ERROR
*******************/
int aggregate_init(BSTNode**T, int choice)
{
	switch (choice)
	{
	case 1:
		if ((*T)->data.friends == NULL)//��ʼ�����Ѽ���
		{
			(*T)->data.friends = (BSTNode*)malloc(sizeof(BSTNode));
			(*T)->data.friends->BF = 0; (*T)->data.friends->lchild = NULL; (*T)->data.friends->rchild = NULL;
			strcpy((*T)->data.friends->data.id, (*T)->data.id); strcpy((*T)->data.friends->data.name, (*T)->data.name);
			(*T)->data.friends->data.hobby = NULL; (*T)->data.friends->data.friends = NULL;
			(*T)->data.friends->data.fan = NULL; (*T)->data.friends->data.concern = NULL;
			return OK;
		}
	case 2:
		if ((*T)->data.fan == NULL)//��ʼ����˿����
		{
			(*T)->data.fan = (BSTNode*)malloc(sizeof(BSTNode));
			(*T)->data.fan->BF = 0; (*T)->data.fan->lchild = NULL; (*T)->data.fan->rchild = NULL;
			strcpy((*T)->data.fan->data.id, (*T)->data.id); strcpy((*T)->data.fan->data.name, (*T)->data.name);
			(*T)->data.fan->data.hobby = NULL; (*T)->data.fan->data.friends = NULL;
			(*T)->data.fan->data.fan = NULL; (*T)->data.fan->data.concern = NULL;
			return OK;
		}
	case 3:
		if ((*T)->data.concern == NULL)//��ʼ����ע�˼���
		{
			(*T)->data.concern = (BSTNode*)malloc(sizeof(BSTNode));
			(*T)->data.concern->BF = 0; (*T)->data.concern->lchild = NULL; (*T)->data.concern->rchild = NULL;
			strcpy((*T)->data.concern->data.id, (*T)->data.id); strcpy((*T)->data.concern->data.name, (*T)->data.name);
			(*T)->data.concern->data.hobby = NULL; (*T)->data.concern->data.friends = NULL;
			(*T)->data.concern->data.fan = NULL; (*T)->data.concern->data.concern = NULL;
			return OK;
		}
	case 4:
		if ((*T)->data.hobby == NULL)//��ʼ�����Ѽ���
		{
			(*T)->data.hobby = (BSTNode*)malloc(sizeof(BSTNode));
			(*T)->data.hobby->BF = 0; (*T)->data.hobby->lchild = NULL; (*T)->data.hobby->rchild = NULL;
			strcpy((*T)->data.hobby->data.id, (*T)->data.id); strcpy((*T)->data.hobby->data.name, (*T)->data.name);
			(*T)->data.hobby->data.hobby = NULL; (*T)->data.hobby->data.friends = NULL;
			(*T)->data.hobby->data.fan = NULL; (*T)->data.hobby->data.concern = NULL;
			return OK;
		}
	}
	return ERROR;
}

/******************
�������ƣ�aggregate
������������Ա���T�ͼ���ѡ��choice
�������ܣ��������輯�ϵ�ͷָ��
����ֵ�����輯�ϵ�ͷָ��
*******************/
BSTNode*aggregate(BSTNode *T, int choice)
{
	switch (choice)
	{
	case 1:return T->data.friends; break;
	case 2:return T->data.fan; break;
	case 3:return T->data.concern; break;
	case 4:return T->data.hobby; break;
	}
}
/******************
�������ƣ�search_common
�����������������ϵ�ͷָ��T1��T2
�������ܣ����T1��T2�Ľ���
����ֵ���ɹ�����OK��ʧ�ܷ���ERROR
*******************/
int search_common(BSTNode*T1, BSTNode*T2)
{
	if (T1 == NULL || T2 == NULL)
	{
		printf("�ռ���");
		return OK;
	}

	BSTNode*T = (struct BSTNode*)malloc(sizeof(struct BSTNode));
	T->BF = 0; T->lchild = NULL; T->rchild = NULL;
	//��T1��T2�ļ��ϵĽ�����������AVL����TΪAVL����ͷ���
	set_intersection(T, T1->lchild, T2->lchild);
	j = 0;
	if (T->lchild == NULL)
		printf("�ռ���");
	else//�����ϵĽ����ǿգ�������������T
		TraverseAVL(T->lchild);
	return OK;
}
/******************
�������ƣ�second_friends
��������������ָ��T1����Ҫ���ҵĽ��T
�������ܣ������T�Ƕ��Ⱥ��ѵĽ�����Ϣ
����ֵ���ɹ�����OK��ʧ�ܷ���ERROR
*******************/
int second_friends(BSTNode*T1, BSTNode*T)
{
	if (T1 == NULL)
		return OK;
	second_friends(T1->lchild, T);

	if (set_member(T->data.friends->lchild, T1->data.id));
	else if (T1->data.friends == NULL);
	else if (strcmp(T1->data.id, T->data.id) != 0)
	{
		BSTNode*node = (struct BSTNode*)malloc(sizeof(struct BSTNode));
		node->BF = 0; node->lchild = NULL; node->rchild = NULL;
		//��T1��T2�ĺ��Ѽ��ϵĽ�����������AVL����TΪAVL����ͷ���
		set_intersection(node, T->data.friends->lchild, T1->data.friends->lchild);
		j = 0;
		if (node->lchild != NULL)//���ǿ���T1ΪT�Ķ��Ⱥ��ѣ����T1�������Ϣ
			printf("���֤�ţ�%s ������%s\n", T1->data.id, T1->data.name);
	}

	second_friends(T1->rchild, T);
	return OK;
}

/******************
�������ƣ�set_subset
����������AVL���ĸ����T1��T2
�������ܣ�T1�Ƿ��T2��ͬ
����ֵ���Ƿ���OK�����Ƿ���ERROR
*******************/
int set_equal(BSTNode*T1, BSTNode*T2)
{
	//���T1��T2���Ӽ���T2��T1���Ӽ�����T1��T2��ͬ
	if (set_subset(T1, T2) == OK&&set_subset(T2, T1) == OK)
		return OK;
	else return ERROR;
}
/******************
�������ƣ�set_subset
����������AVL���ĸ����T1��T2
�������ܣ���T1�Ƿ���T2���Ӽ�
����ֵ���Ƿ���OK�����Ƿ���ERROR
*******************/
int set_subset(BSTNode*T1, BSTNode*T2)
{
	if (T1 == NULL)return OK;

	if (set_member(T2, T1->data.id)==OK)
	{
		if (!set_subset(T1->lchild, T2))return ERROR;
		if (!set_subset(T1->rchild, T2))return ERROR;
		return OK;
	}
	else return ERROR;
}
/******************
�������ƣ�set_member
����������AVL���ĸ����T�����֤��id
�������ܣ������֤��Ϊid�ĳ�Ա�Ƿ�������T��ĳ����
����ֵ���Ƿ���OK�����Ƿ���ERROR
*******************/
int set_member(BSTNode*T, char id[20])
{
	if(T==NULL)
		return ERROR;
	if (SearchAVL(T, id,2) != NULL)return OK;
	return ERROR;
}

/******************
�������ƣ�set_intersection
������������Ҫ���в������������������ڵ�������Ա���T1��T2��T3
�������ܣ���������T3�Ҵ�����T2�Ľ����ӵ�T1��
����ֵ���ɹ�����OK��ʧ�ܷ���ERROR
*******************/
int set_intersection(BSTNode*T1, BSTNode*T2, BSTNode*T3)
{
	if (T3 == NULL||T2==NULL)
		return OK;
	if (SearchAVL(T2, T3->data.id,2) != NULL)
	{
		TElemType data;
		strcpy(data.id,T3->data.id); strcpy(data.name, T3->data.name);
		data.concern = NULL; data.fan = NULL; data.friends = NULL; data.hobby = NULL;
		InsertAVL(T1, data);
	}
	set_intersection(T1, T2, T3->lchild);
	set_intersection(T1, T2, T3->rchild);
	return OK;
}
/******************
�������ƣ�set_intersection1
������������Ҫ���в�������������ͷָ��T1��T2
�������ܣ��������ϵĽ���
����ֵ���ɹ�����OK��ʧ�ܷ���ERROR
*******************/
int set_intersection1(BSTNode*T1, BSTNode*T2)
{
	BSTNode*T = (struct BSTNode*)malloc(sizeof(struct BSTNode));
	T->BF = 0; T->lchild = NULL; T->rchild = NULL;

	if (T1 == NULL || T2 == NULL)return ERROR;
	set_intersection(T, T1->lchild, T2->lchild);

	j = 0;
	if (T->lchild == NULL)
		printf("����Ϊ�ռ���");
	else
		TraverseAVL(T->lchild);
	return OK;
}
/******************
�������ƣ�set_union
������������Ҫ���в������������������ڵ�������Ա���T1��T2
�������ܣ���������T2����������T1�Ľ����ӵ�T1��
����ֵ���ɹ�����OK��ʧ�ܷ���ERROR
*******************/
int set_union(BSTNode*T1, BSTNode*T2)
{
	if (T2 == NULL)
		return OK;
	if (SearchAVL(T1, T2->data.id,2) == NULL)
	{
		TElemType data;
		strcpy(data.id, T2->data.id); strcpy(data.name, T2->data.name);
		data.concern = NULL; data.fan = NULL; data.friends = NULL; data.hobby = NULL;
		InsertAVL(T1, data);
	}
	set_union(T1, T2->lchild);
	set_union(T1, T2->rchild);
	return OK;
}
/******************
�������ƣ�copy
������������Ҫ���в������������������ڵ�������Ա���T1��T2
�������ܣ���������T2�Ľ����ӵ�T1��
����ֵ���ɹ�����OK��ʧ�ܷ���ERROR
*******************/
void copy(BSTNode*T1, BSTNode*T2)
{
	if (T2 == NULL)
		return;
	TElemType data;
	strcpy(data.id,T2->data.id); strcpy(data.name, T2->data.name);
	data.concern = NULL; data.fan = NULL; data.friends = NULL; data.hobby = NULL;
	InsertAVL(T1, data);

	copy(T1, T2->lchild);
	copy(T1, T2->rchild);
}
/******************
�������ƣ�set_union1
������������Ҫ���в�������������ͷָ��T1��T2
�������ܣ��������ϵĲ���
����ֵ���ɹ�����OK��ʧ�ܷ���ERROR
*******************/
int set_union1(BSTNode*T1, BSTNode*T2)
{
	BSTNode*T = (struct BSTNode*)malloc(sizeof(struct BSTNode));
	T->BF = 0; T->lchild = NULL; T->rchild = NULL;

	if (T1 == NULL || T2 == NULL)return ERROR;
	copy(T, T1->lchild);
	set_union(T, T2->lchild);

	j = 0;
	if (T->lchild == NULL)
		printf("����Ϊ�ռ���");
	else
		TraverseAVL(T->lchild);
	return OK;
}
/******************
�������ƣ�set_diffrence
������������Ҫ���в������������������ڵ�������Ա���T1��T2��T3
�������ܣ���������T3����������T2�Ľ����ӵ�T1��
����ֵ���ɹ�����OK��ʧ�ܷ���ERROR
*******************/
int set_diffrence(BSTNode*T1, BSTNode*T2, BSTNode*T3)
{
	if (T3 == NULL || T2 == NULL)
		return OK;
	if (SearchAVL(T2, T3->data.id,2) == NULL)
	{
		TElemType data;
		strcpy(data.id, T3->data.id); strcpy(data.name, T3->data.name);
		data.concern = NULL; data.fan = NULL; data.friends = NULL; data.hobby = NULL;
		InsertAVL(T1, data);//��data���뵽T1��
	}
	set_diffrence(T1, T2, T3->lchild);
	set_diffrence(T1, T2, T3->rchild);
	return OK;
}
/******************
�������ƣ�set_diffrence1
������������Ҫ���в������������ϵ�ͷָ��T1��T2
�������ܣ��������ϵĲ
����ֵ���ɹ�����OK��ʧ�ܷ���ERROR
*******************/
int set_diffrence1(BSTNode*T1, BSTNode*T2)
{
	BSTNode*T = (struct BSTNode*)malloc(sizeof(struct BSTNode));
	T->BF = 0; T->lchild = NULL; T->rchild = NULL;

	if (T1 == NULL || T2 == NULL)return ERROR;
	set_diffrence(T, T1->lchild, T2->lchild); set_diffrence(T, T2->lchild, T1->lchild);

	j = 0;
	if (T->lchild == NULL)
		printf("�Ϊ�ռ���");
	else
		TraverseAVL(T->lchild);
	return OK;
}
/******************
�������ƣ�set_size
������������ǰAVL���ĸ����
�������ܣ��󼯺ϵĹ�ģ
����ֵ���ɹ����ؼ��Ϲ�ģ
*******************/
int set_size(BSTNode*T)
{
	if (T == NULL)
		return 0;
	else
		return set_size(T->lchild) + set_size(T->rchild) + 1;
}

/******************
�������ƣ�TraverseAVL
����������AVL���ĸ����
�������ܣ��Ե�ǰAVL���������������ͬʱ�����ź����ƣ�����1�����
����ֵ����
*******************/
void TraverseAVL(BSTNode*T)
{
	if (T)
	{
		TraverseAVL(T->lchild);
		printf("%s��%s��", T->data.name, T->data.id);
		j++; if(j % 10 == 0)printf("\n"); else printf(" ");
		TraverseAVL(T->rchild);
	}
	return;
}
/******************
�������ƣ�TraverseAVL2
����������AVL���ĸ����
�������ܣ��Ե�ǰAVL���������������ͬʱ�����ź����ƣ�����1�����
����ֵ����
*******************/
void TraverseAVL2(BSTNode*T)
{
	if (T)
	{
		printf("%s��%s��", T->data.name, T->data.id);
		j++; if(j % 10 == 0 )printf("\n"); else printf(" ");
		TraverseAVL2(T->lchild);
		TraverseAVL2(T->rchild);
	}
	return;
}

/******************
�������ƣ�LL
����������AVL���ĸ����
�������ܣ�������ת�������ӵ�������������ʧ��������Ҫ����RR��ת
����ֵ����ת���µĸ����
*******************/
BSTNode*LL(BSTNode*root)
{
	BSTNode*newroot = root->lchild;
	root->lchild = newroot->rchild;
	newroot->rchild = root;
	if (newroot->BF == 1)
	{
		root->BF = 0;
		newroot->BF = 0;
	}
	else
	{
		root->BF = 1;
		newroot->BF = -1;
	}
	return newroot;
}
/******************
�������ƣ�RR
����������AVL���ĸ����
�������ܣ�������ת�����Һ��ӵ�������������ʧ��������Ҫ����RR��ת
����ֵ����ת���µĸ����
*******************/
BSTNode*RR(BSTNode*root)
{
	BSTNode*newroot = root->rchild;
	root->rchild = newroot->lchild;
	newroot->lchild = root;
	if (newroot->BF == -1)
	{
		root->BF = 0;
		newroot->BF = 0;
	}
	else
	{
		root->BF = -1;
		newroot->BF = 1;
	}
	return newroot;
}
/******************
�������ƣ�LR
����������AVL���ĸ����
�������ܣ�������ת�������ӵ�������������ʧ��������Ҫ����LR��ת
����ֵ����ת���µĸ����
*******************/
BSTNode*LR(BSTNode*root)
{
	BSTNode*root1 = root->lchild;
	BSTNode*newroot = root1->rchild;
	root->lchild = newroot->rchild;
	root1->rchild = newroot->lchild;
	newroot->lchild = root1;
	newroot->rchild = root;
	switch (newroot->BF) //�ı�ƽ������
	{
	case 0:
		root->BF = 0;
		root1->BF = 0;
		break;
	case 1:
		root->BF = -1;
		root1->BF = 0;
		break;
	case -1:
		root->BF = 0;
		root1->BF = 1;
		break;
	}
	newroot->BF = 0;
	return newroot;
}
/******************
�������ƣ�RL
����������AVL���ĸ����
�������ܣ�������ת�����Һ��ӵ�������������ʧ��������Ҫ����RL��ת
����ֵ����ת���µĸ����
*******************/
BSTNode*RL(BSTNode*root)
{
	BSTNode*root1 = root->rchild;
	BSTNode*newroot = root1->lchild;
	root->rchild = newroot->lchild;
	root1->lchild = newroot->rchild;
	newroot->rchild = root1;
	newroot->lchild = root;
	switch (newroot->BF)
	{
	case 0:
		root->BF = 0;
		root1->BF = 0;
		break;
	case 1:
		root->BF = 0;
		root1->BF = -1;
		break;
	case -1:
		root->BF = 1;
		root1->BF = 0;
		break;
	}
	newroot->BF = 0;
	return newroot;
}

/******************
�������ƣ�DeleteAVL
����������AVL����ͷ��㣬��Ҫɾ���Ľ������֤��
�������ܣ�ɾ������Ϊname�Ľ��
����ֵ���ɹ�����OK��ʧ�ܷ���ERROR
*******************/
int DeleteAVL(BSTNode*T1, char id[20])
{
	if (T1 == NULL)return ERROR;
	BSTNode*T = T1->lchild;		
	BSTNode*node = NULL;
	node = SearchAVL(T, id, 2); 
	if (node == NULL||T==NULL)//��Ҫ���ҵĽ�㲻���ڻ��ߵ�ǰAVL��Ϊ�����򷵻�ERROR
	{
		return ERROR;
	}
	BSTNode*temp1=NULL,*temp2=NULL;
	if (node->lchild != NULL&&node->rchild != NULL)
	{
		temp1 = node->lchild; temp2 = node;
		while (temp1->rchild != NULL)
		{
			temp2 = temp1;
			temp1 = temp1->rchild;
		}
		if (temp1->lchild == NULL)
		{
			if (temp2 != node)
			{
				temp1->lchild = node->lchild; temp1->rchild = node->rchild;
				temp2->rchild = NULL;
			}	
			else
				temp1->rchild = node->rchild;
		}
		if (node == T)//���Ҫɾ���Ľ��Ϊ����㣬�޸ĸ����
			T = temp1;
		else
		{
			BSTNode*prenode = Parent(T, node->data.id);//���ú�����prenode�洢��Ҫɾ������˫�׽��
			if (strcmp(temp1->data.id, prenode->data.id) > 0)
				prenode->rchild = temp1;
			else
				prenode->lchild = temp1;
		}	 
		node->lchild = NULL; node->rchild = NULL;
		free(node);
	}
	else if (node->lchild == NULL&&node->rchild == NULL)
	{
		if (node == T)
			T = NULL;
		else
		{
			BSTNode*prenode = Parent(T, node->data.id);
			if (strcmp(node->data.id, prenode->data.id) > 0)
				prenode->rchild = NULL;
			else
				prenode->lchild = NULL;
		}
	}
	else if (node->lchild == NULL&&node->rchild != NULL)
	{
		if (node == T)
			T = T->rchild;
		else
		{
			BSTNode*prenode = Parent(T, node->data.id);
			if (strcmp(node->data.id, prenode->data.id) > 0)
				prenode->rchild = node->rchild;
			else
				prenode->lchild = node->rchild;
		}
	}
	else if (node->lchild != NULL&&node->rchild == NULL)
	{
		if (node == T)
			T = T->lchild;
		else
		{
			BSTNode*prenode = Parent(T, node->data.id);
			if (strcmp(node->data.id, prenode->data.id) > 0)
				prenode->rchild = node->lchild;
			else
				prenode->lchild = node->lchild;
		}
	}
	
	T1->lchild=Balance(T);
	return OK;
}
/******************
�������ƣ�InsertAVL
����������AVL����ͷ��㣬���ݽṹdata
�������ܣ�����һ��������Ϊdata�Ľ��
����ֵ���ɹ�����OK��ʧ�ܷ���ERROR
*******************/
int InsertAVL(BSTNode*T1, TElemType data)
{
	if (T1 == NULL)
	{
		printf("δ��ʼ����");
		return ERROR;
	}
	BSTNode*T = T1->lchild;
	if (T == NULL)//����ǰΪ����
	{
		T = (struct BSTNode*)malloc(sizeof(struct BSTNode));
		T->BF = 0; T->data = data;
		T->lchild = NULL; T->rchild = NULL;
		T1->lchild = T;
		return OK;
	}
	BSTNode*pre = NULL, *current = T;
	while (current != NULL)//���ҵ���Ҫ�����λ�ã�����pre������Ҫ����λ�õ�˫�׽��
	{
		if (strcmp(current->data.id,data.id)==0)
			return ERROR;
		pre = current;
		current = (strcmp(data.id, pre->data.id)>0) ? pre->rchild : pre->lchild;
	}
	current = (struct BSTNode*)malloc(sizeof(struct BSTNode)); current->BF = 0; current->data = data; 
	current->lchild = NULL; current->rchild = NULL;
	if (strcmp(data.id,pre->data.id)>0)  pre->rchild = current;
	else pre->lchild = current;

	T1->lchild = Balance(T);
	if (T1->lchild != NULL)
		return OK;
	else return ERROR;
}
/******************
�������ƣ�Balance
����������AVL���ĸ����
�������ܣ��������½����AVL��������ƽ��
����ֵ���ɹ������µĸ����
*******************/
BSTNode *Balance(BSTNode *T)
{
	BSTNode *root = NULL;
	if (T == NULL)return T;
	T->lchild=Balance(T->lchild);//��T��������������AVL�� 
	T->rchild=Balance(T->rchild);//��T��������������AVL��
	T->BF = Depth(T->lchild) - Depth(T->rchild);//��ֵƽ������
	if (T->BF == 0 || T->BF == -1 || T->BF == 1)
		return T;
	if (T->BF == 2)
	{
		int BF = T->lchild->BF;
		if (BF == -1)
			root = LR(T);
		else if (BF == 1)
			root = LL(T);
		else  //ɾ��ʱѡ��
			root = LL(T);
	}
	else if (T->BF == -2)
	{
		int BF = T->rchild->BF;
		if (BF == -1)
			root = RR(T);
		else if (BF == 1)
			root = RL(T);
		else	 //ɾ��ʱѡ��
			root = RR(T);
	}
	return root;
}
/******************
�������ƣ�Depth
����������AVL���ĸ����
�������ܣ�����AVL�������
����ֵ������AVL�������
*******************/
int Depth(BSTNode *T)
{
	int deep = 0;
	if (T)
	{
		int leftdeep = Depth(T->lchild);
		int rightdeep = Depth(T->rchild);
		deep = leftdeep >= rightdeep ? leftdeep + 1 : rightdeep + 1;
	}
	return deep;
}
/******************
�������ƣ�Parent
����������AVL���ĸ���㣬���id
�������ܣ�Ѱ��˫�׽��
����ֵ��������ҵ����ؽ��ָ�룬���򷵻�NULL
*******************/
BSTNode*Parent(BSTNode *T, char id[20])
{
	if (T == NULL)return NULL;
	if ((T->lchild != NULL && strcmp(id, T->lchild->data.id) == 0) || (T->rchild != NULL && strcmp(id, T->rchild->data.id) == 0))
		return T;
	else {
		BSTNode * temp = NULL;
		if (strcmp(id, T->data.id)>0)
			temp = Parent(T->rchild, id);
		if (strcmp(id, T->data.id)<0)
			temp = Parent(T->lchild, id);
		return temp;
	}
}
/******************
�������ƣ�SearchAVL
������������ǰAVL���ĸ���㣬��Ҫ���ҵĽ������ƣ�����ѡ��choice
�������ܣ���������Ϊname�Ľ������֤��Ϊname�Ľ��
����ֵ���ɹ����ؽ��ָ�룬ʧ�ܷ���NULL
*******************/
BSTNode*SearchAVL(BSTNode*T, char name[20],int choice)
{
	if (T == NULL)
		return NULL;
	if (choice == 2 && strcmp(T->data.id,name) == 0)//����ID���ң�Ψһȷ��
		return T;
	if (choice == 1 && strcmp(T->data.name, name) == 0)//����name���ң���Ψһȷ��
	{
		printf("������Ҫ���в�������IDΪ��%s���û���\n", T->data.id);
		printf("Y or N?��ѡ��N�󽫼������в��ң�");
		char c; scanf("%c", &c); getchar(); int re = 0;
		while (re == 0)
		{
			switch (c)
			{
			case 'Y':case 'y':
				re = 1;return T; break;
			case 'N':case 'n':
				re = 1;break;
			default:
				re = 0;
				printf("�������������ѡ��Y or N?��ѡ��N�󽫼������в��ң�"); scanf("%c", &c); getchar();
			}
		}
	}
	BSTNode * temp=NULL;
	temp = SearchAVL(T->rchild, name,choice);
	if (temp==NULL)
		temp = SearchAVL(T->lchild, name,choice);
	return temp;
}
/******************
�������ƣ�DestroyAVL
������������ǰAVL���ĸ����
�������ܣ��ݹ����ٵ�ǰAVL��
����ֵ���ɹ�����OK��ʧ�ܷ���ERROR
*******************/
int DestroyAVL(BSTNode*T)
{
	if (T == NULL) {
		return OK;
	}
	DestroyAVL(T->lchild);
	DestroyAVL(T->rchild);
	free(T);	T = NULL;
	return OK;
}
/******************
�������ƣ�DestroyAVL1
��������������ɭ��ͷָ��head������ָ��F
�������ܣ����ٵ�ǰF��ָ���AVL��
����ֵ���ɹ�����OK��ʧ�ܷ���ERROR
*******************/
int DestroyAVL1(Forest *head, Forest *F)
{
	Forest *p = head;
	Forest *q = p;
	while (p != F)
	{
		q = p;
		p = p->next;
	}
	q->next = p->next;
	if (DestroyAVL(p->HeadNode->lchild) == ERROR)//�ݹ�����AVL��
		return ERROR;
	free(p->HeadNode);
	p->HeadNode = NULL;
	free(p);
	F = NULL;
	return OK;
}
/******************
�������ƣ�InitAVL
��������������ɭ��ͷָ��head������ָ��F
�������ܣ���ʼ��һ�ſյ�AVL��
����ֵ���ɹ�����OK��ʧ�ܷ���ERROR
*******************/
int InitAVL(Forest *head, Forest **F)
{
	Forest *q = head;
	char name[20];
	printf("�������AVL�������֣�20���ַ����ڣ���"); scanf("%s", name); getchar();
	while (q->next)
	{
		q = q->next;
		if (strcmp(q->name, name) == 0)
			break;
	}
	if (strcmp(q->name, name) == 0)
	{
		printf("�������ѱ�ʹ�ã�");
		return ERROR;
	}
	q->next = (Forest *)malloc(sizeof(Forest));
	(*F) = q->next;
	strcpy((*F)->name, name);
	(*F)->HeadNode = (BSTNode*)malloc(sizeof(BSTNode));//�Ե�ǰָ��F���г�ʼ��������ͷ�������ӽ��ΪAVL���ĸ���㣬�Һ���ʼ��ָ��NULL
	(*F)->HeadNode->BF = 0; (*F)->HeadNode->lchild = NULL; (*F)->HeadNode->rchild = NULL;
	memset((*F)->HeadNode->data.id, '0', 20); memset((*F)->HeadNode->data.name, '0', 20);
	(*F)->HeadNode->data.hobby = NULL; (*F)->HeadNode->data.friends = NULL;
	(*F)->HeadNode->data.fan = NULL; (*F)->HeadNode->data.concern = NULL;
	(*F)->next = NULL;
	return OK;
}

/******************
�������ƣ�show
��������������ָ��F
�������ܣ���ʾα�˵�����
����ֵ����
*******************/
void show(Forest *F)
{
	system("cls");
	printf("\n\n");
	printf("\t\t\t\tMenu for Self-balancing Binary Search Tree\n");
	printf("-----------------------------------------------------------------------------------------------------------------------\n");
	printf("\t\t\t\t1. InitAVL\t\t2. DestroyAVL\n");
	printf("\t\t\t\t3. SearchAVL\t\t4. InsertAVL\n");
	printf("\t\t\t\t5. DeleteAVL\t\t6. TraverseAVL\n");

	printf("\t\t\t\t7. set_init\t\t8. set_destroy\n");
	printf("\t\t\t\t9. set_insert\t\t10. set_remove\n");
	printf("\t\t\t\t11. set_intersection\t12. set_union\n");
	printf("\t\t\t\t13. set_diffrence\t14. set_size\n");
	printf("\t\t\t\t15. set_member\t\t16. set_subset\n");
	printf("\t\t\t\t17. set_equal\t\t18. init_aggregate\n");
	printf("\t\t\t\t19. operate_aggregate\t20. search_common\n");
	printf("\t\t\t\t21. second_friends\t22. ExAVL\n");
	printf("\t\t\t\t23. SaveData\t\t24. LoadData\n");
	printf("\t\t\t\t25. Random\t\t0. Exit\n");
	if (F == NULL)
		printf("----------------------------------------------��ǰû�л��-----------------------------------------------------------");
	else
		printf("----------------------------------------------��ǰ���� %s ���в���---------------------------------------------", F->name);
	printf("\n��ѡ����Ĳ���[0~25]:");
}