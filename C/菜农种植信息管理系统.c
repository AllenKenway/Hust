#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <wincon.h>
#include <conio.h>
#include <string.h>
#include <io.h>
#include <fcntl.h>
#include <sys\stat.h>
#include <ctype.h>
#include <time.h>

#ifndef TYPE_H_INCLUDED
#define TYPE_H_INCLUDED

#define SCR_ROW 25                                  /*��Ļ����*/
#define SCR_COL 80                                  /*��Ļ����*/

/*��ũ��ֲ��Ϣ�����ṹ*/
typedef struct ve_p_info {
	int n;                                          /*�߲���ֲ��Ϣ���*/
	int num;                                        /*�߲˻�����Ϣ�е��߲˱��*/
	char type;                                      /*�߲˷������*/
	int area;                                       /*��ֲ���*/
	float h;                                        /*�ջ�����*/
	char name[20];                                  /*�߲�����*/
	char year[5];                                   /*��ֲ���*/
	struct ve_p_info *next;                         /*ָ����һ����ָ��*/
}P;

/*�߲˻�����Ϣ���з�֧����Ӫ���ɷ���Ϣ�����ṹ*/
typedef struct ve_b_nutri_info{
    char type;                                      /*�߲˷������*/
    char n[20];                                     /*Ӫ���ɷֵ�����*/
    int num;                                        /*�߲˻�����Ϣ�е��߲˱��*/
    struct ve_b_nutri_info *next;                   /*ָ����һ����ָ��*/
}N;

/*�߲˻�����Ϣ�����ṹ*/
typedef struct ve_b_info {
	char type;                                      /*�߲˷������*/
	int num;                                        /*�߲˱��*/
	char name[20];                                  /*�߲�����*/
	struct ve_b_info *next;                         /*ָ����һ����ָ��*/
    struct ve_b_nutri_info *snext;                  /*ָ��Ӫ���ɷ�֧����ָ��*/
	struct ve_p_info *cnext;                        /*ָ����ֲ��Ϣ֧����ָ��*/
}B;

/*�߲�������Ϣ�����ṹ*/
typedef struct ve_t_info {
	char type;                                      /*�������*/
	char name[8];                                   /*��������*/
	struct ve_t_info *next;                         /*ָ����һ����ָ��*/
	struct ve_b_info *snext;                        /*ָ�������Ϣ֧����ָ��*/
}T;

/*ĳ����ֲ�����߲���ֲ��Ϣ�����ṹ*/
struct y_p{
    char name[20];                                  /*�߲�����*/
	char type;                                      /*�������*/
	int area;                                       /*��ֲ���*/
	float h;                                        /*�ջ�����*/
	struct y_p *next;                               /*ָ����һ����ָ��*/
};

/*��ֹ���������߲���ֲ��Ϣ*/
struct s_e_t{
    char name[20];                                  /*�߲�����*/
	char type;                                      /*�������*/
    int area;                                       /*��ֲ���*/
    float h;                                        /*�ջ�����*/
    struct s_e_t *next;                             /*ָ����һ����ָ��*/
};

/*��ֹ��ݼ��߲���ֲ��Ϣ�����ṹ*/
struct s_e_p {
	char ve_name[20];                               /*�߲�����*/
	char t_name[20];                                /*��������*/
	int area;                                       /*��ֲ���*/
	float h;                                        /*�ջ�����*/
	struct s_e_p *next;                             /*ָ����һ����ָ��*/
};

/*�߲�����������Ϣ�����ṹ*/
struct v_count {
	char name[8];                                   /*��������*/
	char type;                                      /*�������*/
	float h;                                        /*�ջ�����*/
	struct v_count *next;                           /*ָ����һ����ָ��*/
};

/*��Ļ������Ϣ�������ṹ*/
typedef struct layer_node {
    char LayerNo;                                   /*�������ڲ���*/
    SMALL_RECT rcArea;                              /*����������������*/
    CHAR_INFO *pContent;                            /*�������������ַ���Ԫԭ��Ϣ�洢������*/
    char *pScrAtt;                                  /*�������������ַ���Ԫԭ����ֵ�洢������*/
    struct layer_node *next;                        /*ָ����һ����ָ��*/
} LAYER_NODE;

/*��ǩ���ṹ*/
typedef struct labe1_bundle {
    char **ppLabel;                                 /*��ǩ�ַ��������׵�ַ*/
    COORD *pLoc;                                    /*��ǩ��λ�����׵�ַ*/
    int num;                                        /*��ǩ����*/
} LABEL_BUNDLE;

/*�����ṹ*/
typedef struct hot_area {
    SMALL_RECT *pArea;                              /*������λ�����׵�ַ*/
    char *pSort;                                    /*�������(�������ı���ѡ���)�����׵�ַ*/
    char *pTag;                                     /*������������׵�ַ*/
    int num;                                        /*��������*/
} HOT_AREA;

LAYER_NODE *gp_top_layer = NULL;                    /*����������Ϣ����ͷ*/
T *gp_head = NULL;                                  /*����ͷָ��*/

char *gp_sys_name = "��ũ��ֲ��Ϣ����ϵͳ";         /*ϵͳ����*/
char *gp_ve_p_info_filename = "ve_plant.dat";       /*��ũ��ֲ��Ϣ�����ļ�*/
char *gp_ve_b_info_filename = "ve_info.dat";        /*�߲˻�����Ϣ�����ļ�*/
char *gp_ve_b_nutri_info_filename = "ve_nutri.dat"; /*�߲˻�����Ϣ��Ӫ���ɷ���Ϣ�������ļ�*/
char *gp_ve_t_info_filename = "ve_type.dat";        /*�߲�������Ϣ�����ļ�*/

char *ga_main_menu[] = { "�ļ�(F)",                 /*ϵͳ���˵���*/
                         "����ά��(M)",
                         "���ݲ�ѯ(Q)",
                         "����ͳ��(S)",
                         "����(H)"
                       };

char *ga_sub_menu[] = { "[S] ���ݱ���",             /*ϵͳ�Ӳ˵���*/
                        "[B] ���ݱ���",
                        "[R] ���ݻָ�",
                        "[X] �˳�    Alt+X",

                        "[T] �߲�������Ϣ",
                        "[B] �߲˻�����Ϣ",
                        "[P] �߲���ֲ��Ϣ",

                        "[T] �߲�������Ϣ",
                        "[B] �߲˻�����Ϣ",
                        "[P] ��ũ��ֲ��Ϣ",

                        "[Y] ĳ��������߲���ֲ��Ϣ",
                        "[S] ��ֹ���������߲���ֲ��Ϣ",
                        "[T] ��ֹ�����߲���ֲ��Ϣ",
                        "[C] �߲���������",
                        "[V] ����ĳ��Ӫ�����߲�",

                        "[H] ��������",
                        "[A] ����..."
                      };
int ga_sub_menu_count[] = { 4, 3, 3, 5, 2 };        /*�����˵������Ӳ˵��ĸ���*/
int gi_sel_menu = 1;                                /*��ѡ�е����˵����,��ʼΪ1*/
int gi_sel_sub_menu = 0;                            /*��ѡ�е��Ӳ˵����,��ʼΪ0,��ʾδѡ��*/

CHAR_INFO *gp_buff_menubar_info = NULL;             /*��Ų˵�����Ļ���ַ���Ϣ�Ļ�����*/

char *gp_scr_att = NULL;                            /*�����Ļ���ַ���Ԫ����ֵ�Ļ�����*/
char gc_sys_state = '\0';                           /*��������ϵͳ״̬���ַ�*/

HANDLE gh_std_out;                                  /*��׼����豸���*/
HANDLE gh_std_in;                                   /*��׼�����豸���*/

BOOL LoadData(void);                                /*���ݼ���*/
int CreatList(T **pphead);                          /*���������ʼ��*/
void InitInterface(void);                           /*ϵͳ�����ʼ��*/
void ClearScreen(void);                             /*����*/
void ShowMenu(void);                                /*��ʾ�˵���*/
void PopMenu(int num);                              /*��ʾ�����˵�*/
void PopPrompt(int num);                            /*��ʾ��������*/
void PopUp(SMALL_RECT *, WORD, LABEL_BUNDLE *, HOT_AREA *);  /*����������Ļ��Ϣά��*/
void PopOff(void);                                  /*�رն��㵯������*/
void DrawBox(SMALL_RECT *parea);                    /*���Ʊ߿�*/
void LocSubMenu(int num, SMALL_RECT *parea);        /*���˵������˵���λ*/
void TagMainMenu(int num);                          /*��Ǳ�ѡ�е����˵���*/
void TagSubMenu(int num);                           /*��Ǳ�ѡ�е��Ӳ˵���*/
int DealConInput(HOT_AREA *phot_area, int *pihot_num);  /*����̨���봦��*/
int DealInput(HOT_AREA *pHotArea, int *piHot);
void SetHotPoint(HOT_AREA *phot_area, int hot_num); /*��������*/
void RunSys(T **pphd);                              /*ϵͳ����ģ���ѡ�������*/
BOOL ExeFunction(int main_menu_num, int sub_menu_num);  /*����ģ��ĵ���*/
void CloseSys(T *phd);                              /*�˳�ϵͳ*/

BOOL ShowModule(char **pString, int n);             /*������������ʾ��������*/
int ShowModule2(char **pString, int n);             /*���������������ݷ���ֵ���ù��ܺ���*/
int ShowModule3(char **pString, int n);             /*���������������ݷ���ֵ���ù��ܺ���*/
int ShowModule4(char **pString, int n);             /*���������������ݷ���ֵ���ù��ܺ���*/
int ShowModule5(char **pString, int n);             /*���������������ݷ���ֵ���ù��ܺ���*/

void Update(void);                                  /*�����߲˱��*/
void UpdateNum(void);                               /*������ֲ��Ϣ���*/

BOOL SaveData(void);                                /*��ʾ���ݱ��洰��*/
BOOL SaveSysData(T *hd);                            /*����ϵͳ����*/
BOOL BackupData(void);                              /*��ʾ���ݱ��ݴ���*/
BOOL BackupSysData(T *hd,char* filename);           /*����ϵͳ����*/
BOOL RestoreData(void);                             /*��ʾ���ݻָ�����*/
BOOL RestoreSysData(T **hd,char* filename);         /*�ָ�ϵͳ����*/
BOOL ExitSys(void);                                 /*�˳�ϵͳ*/
BOOL SaveData2(void);                               /*�˳�ʱ�����Ƿ񱣴������ļ�*/

BOOL MaintainTypeInfo(void);                        /*���߲�������Ϣ��������ά��*/
void InsertTypeInfo(T *hd);                         /*¼���߲�������Ϣ*/
void ModifTypeInfo(T *hd);                          /*�޸��߲�������Ϣ*/
void DelTypeInfo(T* hd);                            /*ɾ���߲�������Ϣ*/

BOOL MaintainBasicInfo(void);                       /*���߲˻�����Ϣ��������ά��*/
void InsertBasicInfo(T *hd);                        /*¼���߲˻�����Ϣ*/
void ModifBasicInfo(T *hd);                         /*�޸��߲˻�����Ϣ*/
BOOL ModifName(T *ptype,B *pbasic);                 /*�޸��߲�����*/
BOOL ModifType(T *ptype,B *pbasic1,B *pbasic2);     /*�޸��߲˷�����*/
BOOL InsertNutri(T *ptype,B *pbasic);               /*¼���µ�Ӫ���ɷ�*/
BOOL ModifNutri(T *ptype,B *pbasic);                /*�޸����е�Ӫ���ɷ�*/
BOOL DelNutri(T *ptype,B *pbasic);                  /*ɾ�����е�Ӫ���ɷ�*/
void DelBasicInfo(T* hd);                           /*ɾ���߲˻�����Ϣ*/

BOOL MaintainPlantInfo(void);                       /*���߲���ֲ��Ϣ��������ά��*/
void InsertPlantInfo(T *hd);                        /*¼���ũ��ֲ��Ϣ*/
void ModifPlantInfo(T *hd);                         /*�޸Ĳ�ũ��ֲ��Ϣ*/
void DelPlantInfo(T* hd);                           /*ɾ����ũ��ֲ��Ϣ*/
void SortPlantInfo(P *head,int len);                /*���߲���ֲ��Ϣ����ֲ�����������*/

BOOL QueryTypeInfo(void);                           /*�����߲�������Ϣ*/

BOOL QueryBasicInfo(void);                          /*�����߲˻�����Ϣ*/
BOOL QueryBasicInfo1(void);                         /*���߲����������ַ��Ӵ�Ϊ������ѯ*/
BOOL QueryBasicInfo2(void);                         /*�Է������Ӫ���ɷ�Ϊ������ѯ*/

BOOL QueryPlantInfo(void);                          /*�����߲���ֲ��Ϣ*/
BOOL QueryPlantInfo1(void);                         /*���߲˲������ƺ���ֲ���Ϊ������ѯ*/
BOOL QueryPlantInfo2(void);                         /*���߲�����Ϊ������ѯ*/

BOOL StatVePlant(void);                             /*ͳ��ĳ������߲���ֲ���*/
BOOL SortVePlant(struct y_p* head,int len);         /*��ĳ���߲���ֲ�����ͳ�ƽ�����ջ�������������*/

BOOL StatTypeVePlant(void);                         /*��ֹ���������߲���ֲ��Ϣ*/
BOOL SortTypeVePlant(struct s_e_t *head,int len);   /*����ֹ���������߲���ֲ�����ͳ�ƽ�����ջ�������������*/

BOOL StatVePlantTotal(void);                        /*ͳ����ֹ����߲���ֲ���*/
BOOL SortVePlantTotal(struct s_e_p* head,int len);  /*����ֹ����߲���ֲ�����ͳ�ƽ�����ջ�������������*/

BOOL StatCount(void);                               /*ͳ���߲���������*/
BOOL SortCount(struct v_count*head,int len);        /*���߲�����������ͳ�ƽ��������������������*/

BOOL StatVeNutri(void);                             /*ͳ�ƺ���ĳ��Ӫ���ɷֵ��߲�*/

BOOL HelpTopic(void);                               /*��������*/
BOOL AboutDorm(void);                               /*���ڳ���*/

void location(int x,int y)                          /*ȷ�����λ��*/
{
    COORD pos;
    pos.X=x-1;
    pos.Y=y-1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}
#endif /**< TYPE_H_INCLUDED*/
unsigned long ul;

/********
�������ƣ�ExeFunction
�������ܣ�ִ�������˵��ź��Ӳ˵���ȷ���Ĺ��ܺ���
���������mΪ���˵���ţ�sΪ�Ӳ˵����
�����������
�� �� ֵ��BOOL���ͣ�TRUE��FALSE
           ����ִ�к���ExitSysʱ���ſ��ܷ���FALSE��������������Ƿ���TRUE
����˵����Ϊ���ܹ���ͳһ�ķ�ʽ���ø����ܺ���������Щ���ܺ�����ԭ����Ϊһ�£�
           ���޲����ҷ���ֵΪBOOL������ֵΪFALSEʱ��������������
********/
BOOL ExeFunction(int m, int s)
{
    BOOL bRet = TRUE;
    /*����ָ�����飬����������й��ܺ�������ڵ�ַ*/
    BOOL (*pFunction[ga_sub_menu_count[0]+ga_sub_menu_count[1]+ga_sub_menu_count[2]+ga_sub_menu_count[3]+ga_sub_menu_count[4]])(void);
    int i, loc;

    /*�����ܺ�����ڵ�ַ�����빦�ܺ����������˵��ź��Ӳ˵��Ŷ�Ӧ�±������Ԫ��*/
    pFunction[0] = SaveData;
    pFunction[1] = BackupData;
    pFunction[2] = RestoreData;
    pFunction[3] = ExitSys;

    pFunction[4] = MaintainTypeInfo;
    pFunction[5] = MaintainBasicInfo;
    pFunction[6] = MaintainPlantInfo;

    pFunction[7] = QueryTypeInfo;
    pFunction[8] = QueryBasicInfo;
    pFunction[9] = QueryPlantInfo;

    pFunction[10] = StatVePlant;
    pFunction[11] = StatTypeVePlant;
    pFunction[12] = StatVePlantTotal;
    pFunction[13] = StatCount;
    pFunction[14] = StatVeNutri;

    pFunction[15] = HelpTopic;
    pFunction[16] = AboutDorm;

    for (i=1,loc=0; i<m; i++)                       /*�������˵��ź��Ӳ˵��ż����Ӧ�±�*/
    {
        loc += ga_sub_menu_count[i-1];
    }
    loc += s - 1;

    if (pFunction[loc] != NULL)
    {
        bRet = (*pFunction[loc])();                 /*�ú���ָ�������ָ��Ĺ��ܺ���*/
    }

    return bRet;
}

/********
�������ƣ�SaveData
�������ܣ���ʾ���ݱ��洰��
�����������
�����������
�� �� ֵ��BOOL���ͣ����Ƿ���TRUE
����˵������
********/
BOOL SaveData(void)
{
    BOOL bRet = TRUE;
    char *plabel_name1[] = {"���˵���ļ�",
                           "�Ӳ˵�����ݱ���",
                           "ȷ��"
                          };

    ShowModule(plabel_name1, 3);

    SaveSysData(gp_head);                           /*����ϵͳ����*/

    char *plabel_name2[] = {"���ݱ���ɹ���",
                           "ȷ��"
                          };
    ShowModule(plabel_name2, 2);

    return bRet;
}

/********
�������ƣ�SaveSysData
�������ܣ�����ϵͳ����
���������hdΪ����ͷ���ָ��
�����������
�� �� ֵ��BOOL���ͣ����Ƿ���TRUE
����˵������
********/
BOOL SaveSysData(T *hd)
{
    T *pType;
    B *pBasic;
    P *pPlant;
    N *pNutri;
    FILE *pfout;

    pfout = fopen(gp_ve_t_info_filename, "wb");
    for(pType = hd; pType!= NULL; pType = pType->next)/*�����߲�������Ϣ*/
    {
        fwrite(pType, sizeof(T), 1, pfout);
    }
    fclose(pfout);

    pfout = fopen(gp_ve_b_info_filename, "wb");
    for(pType = hd; pType != NULL; pType = pType->next)/*�����߲˻�����Ϣ*/
    {
        pBasic = pType->snext;
        while(pBasic != NULL)
        {
            fwrite(pBasic, sizeof(B), 1, pfout);
            pBasic = pBasic->next;
        }
    }
    fclose(pfout);

    pfout = fopen(gp_ve_b_nutri_info_filename, "wb");
    for(pType = hd; pType != NULL; pType = pType->next)/*�����߲˻�����Ϣ�е�Ӫ���ɷ�*/
    {
        pBasic = pType->snext;
        while(pBasic != NULL)
        {
            pNutri=pBasic->snext;
            while(pNutri!=NULL)
            {
                fwrite(pNutri,sizeof(N),1,pfout);
                pNutri=pNutri->next;
            }
            pBasic = pBasic->next;
        }
    }
    fclose(pfout);

    pfout = fopen(gp_ve_p_info_filename, "wb");
    for(pType = hd; pType != NULL; pType = pType->next)/*�����߲���ֲ��Ϣ*/
    {
        pBasic = pType->snext;
        while(pBasic != NULL)
        {
            pPlant = pBasic->cnext;
            while(pPlant != NULL)
            {
                fwrite(pPlant, sizeof(P), 1, pfout);
                pPlant = pPlant->next;
            }
            pBasic = pBasic->next;
        }
    }
    fclose(pfout);

    return TRUE;
}

/********
�������ƣ�BackupData
�������ܣ���ʾ���ݱ��ݴ���
�����������
�����������
�� �� ֵ��BOOL���ͣ����Ƿ���TRUE
����˵������
********/
BOOL BackupData(void)
{
    BOOL bRet = TRUE;
    char *plabel_name1[] = {"���˵���ļ�",
                           "�Ӳ˵�����ݱ���",
                           "ȷ��"
                          };
    ShowModule(plabel_name1, 3);

    BackupSysData(gp_head,"Backup.dat");            /*����ϵͳ����*/

    char *plabel_name2[] = {"���ݱ��ݳɹ���",
                           "ȷ��"
                          };
    ShowModule(plabel_name2, 2);

    ClearScreen();
    ShowMenu();

    return bRet;
}

/********
�������ƣ�BackupSysData
�������ܣ�����ϵͳ����
���������hdΪ����ͷ���ָ�룬filenameΪ�����ļ���
�����������
�� �� ֵ��BOOL���ͣ����Ƿ���TRUE
����˵������
********/
BOOL BackupSysData(T *hd,char* filename)
{
    T *pType;
    B *pBasic;
    N *pNutri;
    P *pPlant;
	unsigned long Type_num = 0;
	unsigned long Basic_num = 0;
	unsigned long Nutri_num = 0;
	unsigned long Plant_num = 0;

	/* ����ʮ�������ֱ�ͳ�����ֻ�����Ϣ�ļ�¼���� */
    for(pType = hd; pType != NULL; pType = pType->next)
    {
        Type_num++;
        pBasic = pType->snext;
        while(pBasic != NULL)
        {
            Basic_num++;

            pNutri=pBasic->snext;
            while(pNutri!=NULL)
            {
                Nutri_num++;
                pNutri=pNutri->next;
            }

            pPlant = pBasic->cnext;
            while(pPlant != NULL)
            {
                Plant_num++;
                pPlant = pPlant->next;
            }
            pBasic = pBasic->next;
        }
    }

    int handle;
    if((handle=open(filename,O_WRONLY|O_BINARY))==-1)
    {

        handle=open(filename,O_CREAT|O_BINARY,S_IWRITE);
    }

    /*��������������ݵļ�¼����*/
    write(handle, (char *)&Type_num, sizeof(Type_num));
    write(handle, (char *)&Basic_num, sizeof(Basic_num));
    write(handle, (char *)&Nutri_num, sizeof(Nutri_num));
    write(handle, (char *)&Plant_num, sizeof(Plant_num));

    /*�����߲�������Ϣ*/
    for(pType=hd;pType!=NULL;pType=pType->next)
    {
        write(handle,(char*)pType,sizeof(T));
    }

    /*�����߲˻�����Ϣ*/
    for(pType = hd; pType != NULL; pType = pType->next)
    {
        pBasic = pType->snext;
        while(pBasic != NULL)
        {
            write(handle, (char *)pBasic, sizeof(B));
            pBasic= pBasic->next;
        }
    }

    /*�����߲˻�����Ϣ�е�Ӫ���ɷ��Լ��߲���ֲ��Ϣ*/
    for(pType = hd; pType != NULL; pType = pType->next)
    {
        pBasic = pType->snext;
        while(pBasic != NULL)
        {
            pNutri=pBasic->snext;
            while(pNutri!=NULL)
            {
                write(handle,(char*)pNutri,sizeof(N));
                pNutri=pNutri->next;
            }

            pPlant = pBasic->cnext;
            while(pPlant != NULL)
            {
                write(handle, (char*)pPlant, sizeof(P));
                pPlant = pPlant->next;
            }

            pBasic = pBasic->next;
        }
    }
    close(handle);
    return TRUE;
}

/********
�������ƣ�RestoreData
�������ܣ���ʾ���ݻָ�����
�����������
�����������
�� �� ֵ��BOOL���ͣ����Ƿ���TRUE
����˵������
********/
BOOL RestoreData(void)
{
    char *plabel_name1[] = {"���˵���ļ�",
                           "�Ӳ˵�����ݻָ�",
                           "ȷ��"
                          };
    ShowModule(plabel_name1, 3);
    char *plabel_name2[] = {"��ǰ���ݽ������ǡ�����ִ�У�",
                            "ȷ��","ȡ��"
                           };
    char *plabel_name3[] = {"���ݻָ��ɹ���",
                            "ȷ��"
                           };
    int x=ShowModule5(plabel_name2, 3);             /*��ѡ�С�ȷ�ϡ�����1����ѡ�С�ȡ��������2*/
    switch(x)
    {
        case 1:
            RestoreSysData(&gp_head, "Backup.dat"); /*�ָ�ϵͳ����*/
            ShowModule(plabel_name3, 2);
            break;
        case 2:
            break;
    }
    return TRUE;
}

/********
�������ƣ�RestoreSysData
�������ܣ���ָ�������ļ��лָ������������
���������phead����ͷ���ָ��ĵ�ַ��filename��ű������ݵ������ļ���
�����������
�� �� ֵ��BOOL���ͣ����Ƿ���TRUE
����˵������
********/
BOOL RestoreSysData(T **phead,CHAR* filename)
{
    T *hd = NULL;
    T *pType;
    B *pBasic;
    N *pNutri;
    P *pPlant;
    unsigned long Type_num = 0;
    unsigned long Basic_num = 0;
    unsigned long Nutri_num = 0;
    unsigned long Plant_num = 0;
    unsigned long ulloop;
    int handle;
    int find;

	if((handle = open(filename,O_CREAT | O_BINARY)) == -1)
	{
		handle = open(filename,O_CREAT | O_BINARY,S_IREAD);
	}

    read(handle, (char *)&Type_num, sizeof(Type_num));
    read(handle, (char *)&Basic_num, sizeof(Basic_num));
    read(handle, (char *)&Nutri_num, sizeof(Nutri_num));
    read(handle, (char *)&Plant_num, sizeof(Plant_num));

    /*��ȡ�߲˷�����Ϣ������ʮ������*/
    for(ulloop = 1; ulloop <= Type_num; ulloop++)
    {
        pType = (T *)malloc(sizeof(T));
        read(handle, (char *)pType, sizeof(T));
        pType->snext = NULL;
        pType->next = hd;
        hd = pType;
    }
    *phead = hd;

    /*��ȡ�߲˻�����Ϣ�������߲���Ϣ֧��*/
    for(ulloop = 1; ulloop <= Basic_num; ulloop++)
    {
        pBasic = (B *)malloc(sizeof(B));
        read(handle, (char *)pBasic, sizeof(B));
        pBasic->snext=NULL;
        pBasic->cnext = NULL;
        pType = hd;
        while(pType != NULL&& (pType->type != pBasic->type))
        {
            pType= pType->next;
        }

        if(pType != NULL)
        {
            pBasic->next = pType->snext;
            pType->snext = pBasic;
        }
        else
        {
            free(pBasic);
        }
    }

    /*��ȡ�߲�Ӫ���ɷ���Ϣ������Ӫ���ɷ���Ϣ����*/
    for(ulloop = 1; ulloop <= Nutri_num; ulloop++)
    {
        pNutri = (N *)malloc(sizeof(N));
        read(handle, (char *)pNutri, sizeof(N));
        pType = hd;
        find = 0;

        while(pType != NULL && find == 0)
        {
            pBasic = pType -> snext;
            while(pBasic != NULL && find == 0)
            {
                if(pBasic -> num == pNutri -> num)
                {
                    find = 1;
                    break;
                }
                pBasic = pBasic -> next;
            }
            pType = pType -> next;
        }

        if(find)
        {
            pNutri -> next = pBasic-> snext;
            pBasic -> snext = pNutri;
        }
        else
        {
            free(pNutri);
        }
    }

    /*��ȡ�߲���ֲ��Ϣ�������߲���ֲ��Ϣ֧������*/
    for(ulloop = 1; ulloop <= Plant_num; ulloop++)
    {
        pPlant = (P *)malloc(sizeof(P));
        read(handle, (char *)pPlant, sizeof(P));
        pType = hd;
        find = 0;

        while(pType != NULL && find == 0)
        {
            pBasic = pType -> snext;
            while(pBasic != NULL && find == 0)
            {
                if(pBasic -> num == pPlant -> num)
                {
                    find = 1;
                    break;
                }
                pBasic = pBasic -> next;
            }
            pType = pType -> next;
        }

        if(find)
        {
            pPlant -> next = pBasic-> cnext;
            pBasic -> cnext = pPlant;
        }
        else
        {
            free(pPlant);
        }
    }

    close(handle);
    SaveSysData(hd);                                /*���ڴ������ݱ��浽�����ļ�*/

    return TRUE;
}

/********
�������ƣ�ExitSys
�������ܣ��˳�ϵͳ
�����������
�����������
�� �� ֵ��BOOL���ͣ�����ѡ���˳�ϵͳ����FALSE��������������Ƿ���TRUE
����˵������
********/
BOOL ExitSys(void)
{
    char *plabel_name1[] = {"      ȷ���˳�ϵͳ��      ",
                           "ȷ��","ȡ��"
                          };
    char *plabel_name2[] = {"      �Ƿ���Ҫ�������ݣ�      ",
                           "ȷ��","ȡ��"
                          };
    int x=ShowModule5(plabel_name1,3);              /*����ѡ��ȷ�ϡ�����1,����ѡ��ȡ��������2*/
    int y;
    switch(x)
    {
        case 1:
            y=ShowModule5(plabel_name2,3);          /*����ѡ��ȷ�ϡ�����1,����ѡ��ȡ��������2*/
            switch(y)
            {
                case 1:
                     SaveData2();                   /*��ʾ���ݱ���*/
                     break;
                case 2:
                    break;
            }
            return FALSE;
        case 2:
            return TRUE;
    }
}

/********
�������ƣ�SaveData2
�������ܣ����˳�ϵͳ����ʾ����ϵͳ����
�����������
�����������
�� �� ֵ��BOOL���ͣ����Ƿ���TRUE
����˵������
********/
BOOL SaveData2(void)
{
    char *plabel_name1[] = {"   ���ݱ���   ",
                           "ȷ��"
                          };

    ShowModule(plabel_name1, 2);

    SaveSysData(gp_head);

    char *plabel_name2[] = {"  ���ݱ���ɹ��� ",
                           "ȷ��"
                          };
    ShowModule(plabel_name2, 2);

    return TRUE;
}

/********
�������ƣ�MaintainTypeInfo
�������ܣ����߲�������Ϣ��������ά��
�����������
�����������
�� �� ֵ��BOOL���ͣ����Ƿ���TRUE
����˵������
********/
BOOL MaintainTypeInfo(void)
{
    char *plabel_name[] = {"���˵������ά��",
                           "�Ӳ˵���߲�������Ϣ",
                           "¼��","�޸�","ɾ��"
                          };

    int x=ShowModule2(plabel_name, 5);              /*ѡ��¼�롱����1��ѡ���޸ġ�����2��ѡ��ɾ��������3*/
    switch(x)
    {
        case 1:
              InsertTypeInfo(gp_head);              /*¼���߲�������Ϣ*/
              break;
        case 2:
              ModifTypeInfo(gp_head);               /*�޸��߲�������Ϣ*/
              break;
        case 3:
              DelTypeInfo(gp_head);                 /*ɾ���߲�������Ϣ*/
              break;
    }
    Update();                                       /*���¸�֧�������߲�������Ϣ��Ӧ����Ϣ*/
    return TRUE;
}

/********
�������ƣ�InsertTypeInfo
�������ܣ�¼���߲�������Ϣ
���������hdΪ����ͷ���ָ��
�����������
�� �� ֵ��void���ͣ��޷���ֵ
����˵������
********/
void InsertTypeInfo(T *hd)
{
    T *pType,*p=hd;
    pType=(T*)malloc(sizeof(T));                    /*�½���Ϣ���*/
    location(25,10);printf("��������Ҫ¼����߲�������Ϣ��");
    location(30,12);printf("������룺");
    location(40,12);scanf("%c",&pType->type);

    if(pType->type=='\n')                           /*�ж�������߲˷�������Ƿ�Ϊ��*/
    {
            char *notice4[] = {"   δ���������롣",
                              "¼���߲�������Ϣʧ�ܡ�",
                              "ȷ��"
                             };

            ClearScreen();
            ShowMenu();
            ShowModule(notice4, 3);
            free(pType);
            return;
    }
    location(30,14);printf("�������ƣ�");
    location(40,14);scanf("%s",&pType->name);
    getchar();
    ClearScreen();
    ShowMenu();
    if(strlen(pType->name)>8)                       /*�ж��߲����������ַ����Ƿ����*/
    {
        char *notice1[] = {"�������ƹ�����",
                            "¼���߲�������Ϣʧ�ܡ�",
                            "ȷ��"
                          };
        ShowModule(notice1, 3);
        free(pType);
        return;
    }

    while(p != NULL)                                /*����������Ϣ�������������ƻ�������Ƿ��ѱ�ʹ��*/
    {
        if(pType->type == p->type)
        {
            char *notice2[] = {" �˷������ѱ�ʹ�á�",
                              "¼���߲�������Ϣʧ�ܡ�",
                              "ȷ��"
                             };
            ShowModule(notice2, 3);
            free(pType);
            return;
        }
        else if(strcmp(pType->name,p->name) == 0)
        {
            char *notice3[] = {" �˷��������ѱ�ʹ�á�",
                            "¼���߲�������Ϣʧ�ܡ�",
                            "ȷ��"
                            };
            ShowModule(notice3, 3);
            free(pType);
            return;
        }
        p = p->next;
    }
    /*���½�����Ϣ�����Ϊ�µ�������ͷ���*/
    pType->snext=NULL;
    pType->next=hd;
    gp_head=pType;
    char *notice[] = {"¼���߲�������Ϣ�ɹ���",
                    "ȷ��"
                    };
    ShowModule(notice, 2);
    return;
}

/********
�������ƣ�ModifTypeInfo
�������ܣ��޸��߲�������Ϣ
���������hdΪ����ͷ���ָ��
�����������
�� �� ֵ��void���ͣ��޷���ֵ
����˵������
********/
void ModifTypeInfo(T *hd)
{
    T *pType=hd,*p=NULL;
    B *pBasic=NULL;
    char type;
    char name[20];
    location(25,6);printf("��������Ҫ�޸ĵ��߲˷������ƣ�");
    location(35,8);scanf("%s",name);
    getchar();
    ClearScreen();
    ShowMenu();

    while(pType!=NULL)                              /*����������Ϣ���������Ƿ������Ҫ�޸ĵķ�������*/
    {
        if(strcmp(name,pType->name)==0)
        {
            break;
        }
        pType=pType->next;
    }
    if(pType==NULL)
    {
        char *notice1[] = {"    �÷��಻����!","�޸��߲�������Ϣʧ��!",
                    "ȷ��"
                    };
        ShowModule(notice1, 3);
        free(p);
        return;
    }

    char *pString[] = {"�޸ķ�����",
                       "�޸ķ�������",
                       "����"
                      };
    int x=ShowModule3(pString,3);
    switch(x)
    {
        case 1:
            location(25,10);printf("��ǰ���߲˷�����ϸ��Ϣ���£�");
            location(30,12);printf("������룺");
            location(40,12);printf("%-8c",pType->type);
            location(30,14);printf("�������ƣ�");
            location(40,14);printf("%-10s",pType->name);
            location(25,16);printf(" �µķ�����룺");
            location(40,16);scanf("%c",&type);
            getchar();
            ClearScreen();
            ShowMenu();

            p=hd;                                   /*����������Ϣ������ѯ�÷�������Ƿ��ѱ�ʹ��*/
            while(p!=NULL)
            {
                if(p->type==type)break;
                p=p->next;
            }
            if(p!=NULL)
            {
                char *notice2[] = { " �÷������ѱ�ʹ��!",
                                    "�޸��߲�������Ϣʧ��!",
                                    "ȷ��"
                                  };
                ShowModule(notice2, 3);
            }
            else
            {
                pType->type=type;
                for(pBasic=pType->snext;pBasic!=NULL;pBasic=pBasic->next)
                    pBasic->type=type;
                char *notice[] = {"�޸��߲˷�����Ϣ�ɹ�!",
                                  "ȷ��"
                                 };
                ShowModule(notice, 2);
            }
            break;
        case 2:
            location(25,10);printf("��ǰ���߲˷�����ϸ��Ϣ���£�");
            location(30,12);printf("������룺");
            location(40,12);printf("%-8c",pType->type);
            location(30,14);printf("�������ƣ�");
            location(40,14);printf("%-10s",pType->name);
            location(25,16);printf("�µķ������ƣ�");
            location(40,16);scanf("%s",name);
            getchar();
            ClearScreen();
            ShowMenu();

            if(strlen(name)>8)                      /*�ж�����ķ��������ַ����Ƿ����*/
            {
                char *notice3[] = {"   �������ƹ���!",
                                   "�޸��߲�������Ϣʧ��!",
                                   "ȷ��"
                                  };
                ShowModule(notice3, 3);
            }

            p=hd;                                   /*����������Ϣ������ѯ�÷��������Ƿ��ѱ�ʹ��*/
            while(p!=NULL)
            {
                if(strcmp(p->name,name)==0)break;
                p=p->next;
            }
            if(p!=NULL)
            {
                char *notice4[] = {"    �÷��������ѱ�ʹ��!",
                                   "�޸��߲�������Ϣʧ��!",
                                   "ȷ��"
                                  };
                ShowModule(notice4, 3);
            }
            else                                    /*�޸ĸ÷���ķ�������*/
            {
                strcpy(pType->name,name);
                char *notice[] = {"�޸��߲˷�����Ϣ�ɹ�!",
                                  "ȷ��"
                                 };
                ShowModule(notice, 2);
            }
            break;
        case 3:
            break;
        }
    return;
}

/********
�������ƣ�DelTypeInfo
�������ܣ�ɾ���߲�������Ϣ
���������hdΪ����ͷ���ָ��
�����������
�� �� ֵ��void���ͣ��޷���ֵ
����˵������
********/
void DelTypeInfo(T *hd)
{
    T *pType=hd,*p=NULL;
    B *pBasic1,*pBasic2;
    N *pNutri1,*pNutri2;
    P *pPlant1,*pPlant2;
    char name[8];

    location(25,6);printf("��������Ҫɾ�����߲˷������ƣ�");
    location(35,8);scanf("%s",name);
    getchar();
    ClearScreen();
    ShowMenu();
    for(;pType!=NULL&&strcmp(name,pType->name);p=pType,pType=pType->next);
    if(pType==NULL)
    {
        char *notice1[] = {"    �÷��಻����!",
                           "ɾ���߲�������Ϣʧ��!",
                           "ȷ��"
                          };
        ShowModule(notice1, 3);
        return;
    }
    else if(pType==gp_head)
    {
        gp_head=pType->next;
    }
    else
    {
        p->next=pType->next;
    }

    pBasic1=pType->snext;
    while(pBasic1!=NULL)
    {
        pBasic2=pBasic1->next;
        pNutri1=pBasic1->snext;
        while(pNutri1!=NULL)
        {
            pNutri2=pNutri1->next;
            free(pNutri1);
            pNutri1=pNutri2;
        }
        pPlant1=pBasic1->cnext;
        while(pPlant1!=NULL)
        {
            pPlant2=pPlant1->next;
            free(pPlant1);
            pPlant1=pPlant2;
        }
        free(pBasic1);
        pBasic1=pBasic2;
    }
    free(pType);
    char *notice2[] = {"ɾ��������Ϣ�ɹ�!",
                       "ȷ��"
                      };
    ShowModule(notice2, 2);
    return;
}

/********
�������ƣ�MaintainBasicInfo
�������ܣ����߲˻�����Ϣ��������ά��
�����������
�����������
�� �� ֵ��BOOL���ͣ����Ƿ���TRUE
����˵������
********/
BOOL MaintainBasicInfo(void)
{
    char *plabel_name[] = {"���˵������ά��",
                           "�Ӳ˵���߲˻�����Ϣ",
                           "¼��","�޸�","ɾ��"
                          };

    int x=ShowModule2(plabel_name, 5);
    switch(x)
    {
        case 1:
              InsertBasicInfo(gp_head);
              break;
        case 2:
              ModifBasicInfo(gp_head);
              break;
        case 3:
              DelBasicInfo(gp_head);
              break;
    }
    Update();                                       /*���¸�֧�������߲�������Ϣ��Ӧ����Ϣ*/
    return TRUE;
}

/********
�������ƣ�InsertBasicInfo
�������ܣ�¼���߲˻�����Ϣ
���������hdΪ����ͷ���ָ��
�����������
�� �� ֵ��void���ͣ��޷���ֵ
����˵������
********/
void InsertBasicInfo(T *hd)/******************************************************************************************Ӧ�û�������****/
{
    T *pType1=hd,*pType2=hd;
    B *pBasic1,*p=(B*)malloc(sizeof(B)),*p1;
    N *pNutri1,*pNutri2;
    P *pplant;
    int num;
    char name[30];
    char type;
    location(25,6);printf("��������Ҫ¼����߲˻�����Ϣ��");
    location(30,8);printf("������룺");
    location(40,8);scanf("%c",&type);
    getchar();

    for(;pType1!=NULL&&(type!=pType1->type);pType1=pType1->next);
    if(pType1==NULL)
    {
        char *notice1[] = {"    �÷��಻����!",
                           "¼���߲˻�����Ϣʧ��!",
                           "ȷ��"
                          };
        ClearScreen();
        ShowMenu();
        free(p);
        ShowModule(notice1, 3);
        return;
    }
    else
    {
        p->type=type;
    }
    location(30,10);printf("�߲����ƣ�");
    location(40,10);scanf("%s",name);
    getchar();

    pBasic1=pType1->snext;
    if(strlen(name)>20)
    {
        char *notice2[] = {"   �߲����ƹ���!","¼���߲˻�����Ϣʧ��!",
                    "ȷ��"
                    };
        ShowModule(notice2, 3);
        ClearScreen();
        ShowMenu();
        free(p);
        return;
    }
    else
    {
        while(pType2!=NULL)
        {
            pBasic1=pType2->snext;
            while(pBasic1!=NULL)
            {
                if(strcmp(name,pBasic1->name)==0)
                {
                    char *notice3[] = {" ���߲������ѱ�ʹ��!",
                                       "¼���߲˻�����Ϣʧ��!",
                                       "ȷ��"
                                      };
                    ClearScreen();
                    ShowMenu();
                    free(p);
                    ShowModule(notice3, 3);
                    return;
                }
                pBasic1=pBasic1->next;
            }
            pType2=pType2->next;
        }
    }
    strcpy(p->name,name);

    p->cnext=NULL;
    p->snext=NULL;
    pNutri2=(N*)calloc(1,sizeof(N));
    pNutri2->next= NULL;

    location(20,12);printf("Ӫ���ɷֵ�������#Ϊ�����������磺ά���� �� #");
    location(30,14);printf("Ӫ���ɷ֣�");
    location(40,14);
	while(1)                                        /*�����߲˻�����Ϣ�е�Ӫ���ɷ�*/
    {
	    pNutri1=(N*)malloc(sizeof(N));
        pNutri1->next=NULL;
	    char nutri[20]={'\0'};
        scanf("%s",nutri);
        if(nutri[0]=='#')
        {
        	pNutri1=NULL;
        	break;
		}
		else
		{
            strcpy(pNutri1->n,nutri);
            pNutri1->next=pNutri2->next;
            pNutri2->next=pNutri1;
		}
    }
    getchar();
    pNutri2=pNutri2->next;
    p->snext=pNutri2;

    p1=pType1->snext;
    int max;                                        /*Ϊ��������߲˻�����Ϣ�����߲˱��*/
    if(p1==NULL)
    {
        p->num=1;
    }
    else
    {
        max=p1->num;
        while(p1!=NULL)
        {
            if(max<p1->num)max=p1->num;
            p1=p1->next;
        }
        p->num=max+1;
    }
    p->next=pType1->snext;
    pType1->snext=p;
    Update();                                       /*���߲˱���ͬ�������߲���ֲ��Ϣ���߲�Ӫ���ɷ���*/

    location(30,16);printf("�߲˱��룺");
    location(40,16);printf("%d",p->num);
    printf("\n\n\t\t\t    �����������������");
    getchar();

    char *notice[] = {"���������Ϣ�ɹ���",
                      "ȷ��"
                     };
    ClearScreen();
    ShowMenu();
    ShowModule(notice, 2);
    return;
}

/********
�������ƣ�ModifBasicInfo
�������ܣ��޸��߲˻�����Ϣ
���������hdΪ����ͷ���ָ��
�����������
�� �� ֵ��void���ͣ��޷���ֵ
����˵������
********/
void ModifBasicInfo(T *hd)
{
    T *ptype=hd;
    B *pbasic1,*pbasic2;
    N *pnutri;
    P *pplant;
    char name[30];
    int find=0;
    int i=0,x,y;
    BOOL flag=TRUE;
    location(25,6);printf("��������Ҫ�޸Ļ�����Ϣ���߲����ƣ�");
    location(35,8);scanf("%s",name);
    getchar();

    while(ptype!=NULL)
    {
        pbasic1=ptype->snext;
        while(pbasic1!=NULL)
        {
            if(strcmp(name,pbasic1->name)==0)
            {
                find=1;
                break;
            }
            pbasic2=pbasic1;
            pbasic1=pbasic1->next;
        }
        if(find==1)
        {
            break;
        }
        ptype=ptype->next;
    }
    if(ptype==NULL)
    {
        char *notice1[] = {"    ���߲˲�����!","�޸��߲˻�����Ϣʧ��!",
                    "ȷ��"
                    };
        ClearScreen();
        ShowMenu();
        ShowModule(notice1, 3);

        return;
    }

    location(25,10);printf("��ǰ���߲˻�����Ϣ�������£�");
    location(30,12);printf("�߲˱�ţ�");
    location(40,12);printf("%d",pbasic1->num);
    location(30,14);printf("�߲����ƣ�");
    location(40,14);printf("%s",pbasic1->name);
    location(30,16);printf("�����룺");
    location(40,16);printf("%c",pbasic1->type);
    location(30,18);printf("Ӫ���ɷ֣�");
    location(40,18);
    pnutri=pbasic1->snext;
    while(pnutri!=NULL)
    {
        printf("%s  ",pnutri->n);
        pnutri=pnutri->next;
        i++;
        if(i%4==0)
        {
            location(40,18+(i/4)*2);
        }
    }
    location(25,20+(i/4)*2);printf("�밴���������������");
    getchar();
    ClearScreen();
    ShowMenu();

    char *pString1[] = {"�޸��߲�����",
                        " �޸ķ�����",
                        "�޸�Ӫ���ɷ�",
                        "����"
                       };
    x=ShowModule4(pString1, 4);
    char *pString2[] = {" ¼���µ�Ӫ���ɷ�",
                        "�޸����е�Ӫ���ɷ�",
                        "ɾ�����е�Ӫ���ɷ�",
                        "����"
                        };
    switch(x)
    {
        case 1:
             flag=ModifName(ptype,pbasic1);
             break;
        case 2:
             flag=ModifType(ptype,pbasic1,pbasic2);
             break;
        case 3:
            y=ShowModule4(pString2, 4);
            switch(y)
            {
                case 1:
                    flag=InsertNutri(ptype,pbasic1);
                    break;
                case 2:
                    flag=ModifNutri(ptype,pbasic1);
                    break;
                case 3:
                    flag=DelNutri(ptype,pbasic1);
                    break;
                case 4:
                    return;
            }
            break;
        case 4:
            return;
    }
    if(flag==TRUE)
    {
        char *notice2[] = {"�޸��߲˻�����Ϣ�ɹ�!",
                           "ȷ��"
                          };
        Update();
        ShowModule(notice2, 2);
    }
    else
    {
        char *notice3[] = {"�޸��߲˻�����Ϣʧ��!",
                "ȷ��"
                };
        ShowModule(notice3, 2);
    }
}

/********
�������ƣ�ModifName
�������ܣ��޸��߲�����
���������ptypeΪ��Ҫ�޸ĵ��߲�����Ӧ���߲�������Ϣ���
           pbasicΪ��Ҫ�޸ĵ��߲�����Ӧ���߲˻�����Ϣ���
�����������
�� �� ֵ��BOOL���ͣ����Ƿ���TRUE
����˵������
********/
BOOL ModifName(T *ptype,B *pbasic)
{
    T *pt=gp_head;
    B *pb;
    char name[30];
    int find=0;
    location(25,10);printf("�������޸ĺ��µķ������ƣ�");
    location(35,12);scanf("%s",name);
    getchar();
    ClearScreen();
    ShowMenu();

    if(strlen(name)>20)
    {
        char *notice1[] = {"����������ƹ���!"
                           "ȷ��"
                          };
        ShowModule(notice1, 2);
        return FALSE;
    }

    while(pt!=NULL)
    {
        pb=pt->snext;
        while(pb!=NULL)
        {
            if(strcmp(name,pb->name)==0)
            {
                find=1;
                break;
            }
            pb=pb->next;
        }
        if(find==1) break;
        pt=pt->next;
    }
    if(find==1)
    {
        char *notice2[] = {"������������Ѵ���!",
                           "ȷ��"
                          };
        ShowModule(notice2, 2);
        return FALSE;
    }
    strcpy(pbasic->name,name);
    return TRUE;
}

/********
�������ƣ�ModifType
�������ܣ��޸��߲˶�Ӧ�������
���������ptypeΪ��Ҫ�޸ĵ��߲�����Ӧ���߲�������Ϣ���
           pbasic1Ϊ��Ҫ�޸ĵ��߲�����Ӧ���߲˻�����Ϣ���
           pbasic2Ϊ��Ҫ�޸ĵ��߲�����Ӧ���߲˻�����Ϣ��ǰһ�����
�����������
�� �� ֵ��BOOL���ͣ����Ƿ���TRUE
����˵������
********/
BOOL ModifType(T *ptype,B *pbasic1,B *pbasic2)
{
    T *pt=gp_head;
    B *pb;
    char type;
    int find=0;
    location(25,10);printf("�������޸ĺ��µķ�����룺");
    location(35,12);scanf("%c",&type);
    getchar();
    ClearScreen();
    ShowMenu();

    while(pt!=NULL)
    {
        if(pt->type==type)
        {
            find=1;
            break;
        }
        pt=pt->next;
    }
    if(find==0)
    {
        char *notice[] = {"������·����벻����!",
                        "ȷ��"
                        };
        ShowModule(notice, 2);
        return FALSE;
    }

    pb=ptype->snext;
    while(pb!=NULL)                                 /*����ԭ������Ϣ֧���е��߲˱��*/
    {
        if(pb->num>pbasic1->num)pb->num=pb->num-1;
        pb=pb->next;
    }
    pb=pt->snext;
    int max;
    if(pb==NULL)max=0;
    else
    {
        max=pb->num;
        while(pb!=NULL)
        {
            if(pb->num>max)max=pb->num;
            pb=pb->next;
        }
    }
    pbasic1->type=type;
    pbasic1->num=max+1;

    if(ptype->snext==pbasic1)
    {
        ptype->snext=pbasic1->next;
    }
    else
    {
        pbasic2->next=pbasic1->next;
    }
    pbasic1->next=pt->snext;
    pt->snext=pbasic1;
    return TRUE;
}

/********
�������ƣ�Update
�������ܣ����¸�֧�������߲�������Ϣ��Ӧ����Ϣ
�����������
�����������
�� �� ֵ��void���ͣ��޷���ֵ
����˵������
********/
void Update(void)
{
    T *ptype=gp_head;
    B *pbasic;
    N *pnutri;
    P *pplant;

    while(ptype!=NULL)
    {
        pbasic=ptype->snext;
        while(pbasic!=NULL)
        {
            pnutri=pbasic->snext;
            while(pnutri!=NULL)
            {
                pnutri->type=pbasic->type;
                pnutri->num=pbasic->num;
                pnutri=pnutri->next;
            }

            pplant=pbasic->cnext;
            while(pplant!=NULL)
            {
                pplant->type=pbasic->type;
                pplant->num=pbasic->num;
                pplant=pplant->next;
            }
            pbasic=pbasic->next;
        }
        ptype=ptype->next;
    }
}

/********
�������ƣ�InsertNutri
�������ܣ�¼���µ�Ӫ���ɷ�
���������ptypeΪ��Ҫ�޸ĵ��߲�����Ӧ���߲�������Ϣ���
           pbasicΪ��Ҫ�޸ĵ��߲�����Ӧ���߲˻�����Ϣ���
�����������
�� �� ֵ��BOOL���ͣ����Ƿ���TRUE
����˵������
********/
BOOL InsertNutri(T *ptype,B *pbasic)
{
    N *p=pbasic->snext,*pnutri;
    char nutri[20];
    int find=0;
    location(25,10);printf("��������Ҫ¼�����Ӫ���ɷ֣�");
    location(35,12);scanf("%s",nutri);
    ClearScreen();
    ShowMenu();

    while(p!=NULL)
    {
        if(strcmp(nutri,p->n)==0)
        {
            find=1;
            break;
        }
        p=p->next;
    }
    if(find==1)
    {
        char *notice[] = {"�����Ӫ���ɷ��Ѵ���",
                          "ȷ��"
                          };
        ShowModule(notice, 2);
        return FALSE;
    }
    pnutri=(N*)malloc(sizeof(N));
    strcpy(pnutri->n,nutri);
    pnutri->next=pbasic->snext;
    pbasic->snext=pnutri;
    pnutri->num=pbasic->num;
    return TRUE;
}

/********
�������ƣ�
�������ܣ��޸����е�Ӫ���ɷ�
���������
���������
�� �� ֵ��BOOL���ͣ����Ƿ���TRUE
����˵����
********/
BOOL ModifNutri(T *ptype,B *pbasic)
{
    N *p=pbasic->snext;
    char nutri[20];
    int find=0;
    location(25,10);printf("��������Ҫ�޸ĵ�Ӫ���ɷ֣�");
    location(35,12);scanf("%s",nutri);
    getchar();

    while(p!=NULL)
    {
        if(strcmp(nutri,p->n)==0)
        {
            find=1;
            break;
        }
        p=p->next;
    }
    if(find==0)
    {
        char *notice2[] = {"�����Ӫ���ɷֲ�����",
                        "ȷ��"
                        };
        ClearScreen();
        ShowMenu();
        ShowModule(notice2, 2);
        return FALSE;
    }

    location(25,14);printf("�������޸ĺ����Ӫ���ɷ֣�");
    location(35,16);scanf("%s",p->n);
    getchar();
    return TRUE;
}

/********
�������ƣ�DelNutri
�������ܣ�ɾ�����е�Ӫ���ɷ�
���������ptypeΪ��Ҫ�޸ĵ��߲�����Ӧ���߲�������Ϣ���
           pbasicΪ��Ҫ�޸ĵ��߲�����Ӧ���߲˻�����Ϣ���
�����������
�� �� ֵ��BOOL���ͣ����Ƿ���TRUE
����˵������
********/
BOOL DelNutri(T *ptype,B *pbasic)
{
    N *p,*pnutri;
    char nutri[20];
    int find=0;
    location(25,10);printf("��������Ҫɾ������Ӫ���ɷ֣�");
    location(35,12);scanf("%s",nutri);
    getchar();
    ClearScreen();
    ShowMenu();

    p=pbasic->snext;
    pnutri=(N*)malloc(sizeof(N));
    while(p!=NULL)
    {
        if(strcmp(nutri,p->n)==0)
        {
            find=1;
            break;
        }
        pnutri=p;
        p=p->next;
    }
    if(find==0)
    {
        char *notice2[] = {"�����Ӫ���ɷֲ�����",
                           "ȷ��"
                          };
        ShowModule(notice2, 2);
        return FALSE;
    }
    if(p==pbasic->snext)
    {
        pbasic->snext=p->next;
    }
    else
    {
        pnutri->next=p->next;
    }
    return TRUE;
}

/********
�������ƣ�DelBasicInfo
�������ܣ�ɾ���߲˻�����Ϣ
���������hdΪ�߲˻�����Ϣ��ͷ���ָ��
�����������
�� �� ֵ��void���ͣ��޷���ֵ
����˵������
********/
void DelBasicInfo(T* hd)
{
    T *pType=hd;
    B *pBasic1,*pBasic2=NULL,*pb;
    N *pNutri;
    P *pPlant;
    char name[20];

    location(25,8);printf("��������Ҫɾ��������Ϣ�����ƣ�");
    location(35,10);scanf("%s",name);getchar();

    while(pType!=NULL)
    {
        pBasic1=pType->snext;
        while(pBasic1!=NULL)
        {
            if(strcmp(name,pBasic1->name)==0)
            {
                if(pBasic1=pType->snext)
                {
                    pType->snext=pBasic1->next;
                }
                else
                {
                    pBasic2->next=pBasic1->next;
                }

                pb=pType->snext;
                while(pb!=NULL)
                {
                    if(pb->num>pBasic1->num)pb->num=pb->num-1;
                    pb=pb->next;
                }

                pNutri=pBasic1->snext;
                while(pNutri!=NULL)
                {
                    free(pNutri);
                    pNutri=pNutri->next;
                }

                pPlant=pBasic1->cnext;
                while(pPlant!=NULL)
                {
                    free(pPlant);
                    pPlant=pPlant->next;
                }

                free(pBasic1);

                ClearScreen();
                ShowMenu();
                char *notice1[] = {"ɾ��������Ϣ�ɹ�!",
                                "ȷ��"
                                };

                ShowModule(notice1,2);
                return;
            }
            pBasic2=pBasic1;
            pBasic1=pBasic1->next;
        }
        pType=pType->next;
    }
    ClearScreen();
    ShowMenu();
    char *notice2[] = {"���߲����Ʋ�����!",
                        "ɾ��������Ϣʧ��!",
                        "ȷ��"
                        };

    ShowModule(notice2, 3);
    Update();                                       /*�����߲˱��*/
    return;
}

/********
�������ƣ�MaintainPlantInfo
�������ܣ����߲���ֲ��Ϣ����ά��
�����������
�����������
�� �� ֵ��BOOL���ͣ����Ƿ���TRUE
����˵������
********/
BOOL MaintainPlantInfo(void)
{
    char *plabel_name[] = {"���˵������ά��",
                           "�Ӳ˵����ũ��ֲ��Ϣ",
                           "¼��","�޸�","ɾ��"
                          };
    int x=ShowModule2(plabel_name, 5);
    switch(x)
    {
        case 1:
              InsertPlantInfo(gp_head);
              break;
        case 2:
              ModifPlantInfo(gp_head);
              break;
        case 3:
              DelPlantInfo(gp_head);
              break;
    }
    Update();                                       /*�����߲˱��*/
    return TRUE;
}

/********
�������ƣ�InsertPlantInfo
�������ܣ�¼���߲�������Ϣ
���������hdΪ�߲���ֲ��Ϣ����ͷ���ָ��
�����������
�� �� ֵ��void���ͣ��޷���ֵ
����˵������
********/
void InsertPlantInfo(T *hd)
{
    T *ptype=hd;
    B *pbasic;
    P *pplant,*p=(P*)malloc(sizeof(P));;
    char name[20];
    char year[5];
    int find=0;

    location(25,6);printf("��������Ҫ¼����߲���ֲ��Ϣ��");
    location(30,8);printf("�߲����ƣ�");
    location(40,8);scanf("%s",name);
    getchar();

    while(ptype!=NULL)
    {
        pbasic=ptype->snext;
        while(pbasic!=NULL)
        {
            if(strcmp(pbasic->name,name)==0)
            {
                find=1;break;
            }
            pbasic=pbasic->next;
        }
        if(find==1)break;
        ptype=ptype->next;
    }

    if(find==0)
    {
        char *notice1[] = {"   ���߲˲�����!",
                        "�����߲���ֲ��Ϣʧ��!",
                        "ȷ��"
                        };
        ClearScreen();
        ShowMenu();
        ShowModule(notice1, 3);

        return;
    }

    location(30,10);
    printf("��ֲ��ݣ�");
    location(40,10);
    scanf("%s",year);
    find=0;
    pplant=pbasic->cnext;
    while(pplant!=NULL)
    {
        if(strcmp(pplant->year,year)==0)
        {
            find=1;
            break;
        }
        pplant=pplant->next;
    }
    if(find==1)
    {
        char *notice2[] = {" �������Ϣ�Ѿ�¼��!",
                        "�����߲���ֲ��Ϣʧ��!",
                        "ȷ��"
                        };
        ClearScreen();
        ShowMenu();
        ShowModule(notice2, 3);
        return;
    }

    strcpy(p->name,name);
    strcpy(p->year,year);
    p->type=ptype->type;
    p->num=pbasic->num;

    location(30,12);printf("��ֲ�����");
    location(40,12);scanf("%d",&p->area);
    location(30,14);printf("�ջ�������");
    location(40,14);scanf("%f",&p->h);
    getchar();
    p->n=1;
    p->next=pbasic->cnext;
    pbasic->cnext=p;
    UpdateNum();                                    /*���߲���ֲ��Ϣ����ֲ��������������α��*/

    location(30,16);printf("�߲˱�ţ�");
    location(40,16);printf("%d",p->num);
    printf("\n\n\t\t\t    �����������������");
    getchar();

    char *notice3[] = {"���������Ϣ�ɹ�!",
                    "ȷ��"
                    };
    ClearScreen();
    ShowMenu();
    ShowModule(notice3, 2);

    return;
}

/********
�������ƣ�ModifPlantInfo
�������ܣ��޸��߲���ֲ��Ϣ
���������hdΪ�߲���ֲ��Ϣ����ͷ���ָ��
�����������
�� �� ֵ��void���ͣ��޷���ֵ
����˵������
********/
void ModifPlantInfo(T *hd)
{
    T *ptype=hd;
    B *pbasic;
    N *pnutri;
    P *pplant;
    char name[20];
    char year[5];
    int find=0;
    int n;
    int i=1,j=0;
    location(25,6);printf("��������Ҫ�޸���ֲ��Ϣ���߲����ƣ�");
    location(35,8);scanf("%s",name);
    getchar();

    while(ptype!=NULL)
    {
        pbasic=ptype->snext;
        while(pbasic!=NULL)
        {
            if(strcmp(name,pbasic->name)==0)
            {
                find=1;
                break;
            }
            pbasic=pbasic->next;
        }
        if(find==1)
        {
            break;
        }
        ptype=ptype->next;
    }
    if(ptype==NULL)
    {
        char *notice1[] = {"    ���߲˲�����!","�޸��߲���ֲ��Ϣʧ��!",
                    "ȷ��"
                    };
        ClearScreen();
        ShowMenu();
        ShowModule(notice1, 3);
        return;
    }
    ClearScreen();
    ShowMenu();
    UpdateNum();                                    /*���߲���ֲ��Ϣ����ֲ��������������α��*/

    location(25,6);printf("��ǰ���߲���ֲ��Ϣ�������£�");
    location(20,8);printf("�߲˱�ţ�");
    location(30,8);printf("%d",pbasic->num);
    location(40,8);printf("�߲����ƣ�");
    location(50,8);printf("%s",pbasic->name);

    P *p=pbasic->cnext,*p2=pbasic->cnext;
    if(p==NULL)
    {
        ClearScreen();
        ShowMenu();
        char *notice4[] = {"���߲�δ¼���κ���ֲ��Ϣ",
                            "ȷ��"
                            };
        ShowModule(notice4, 2);
        return;
    }

    location(15,10);printf("���");
    location(30,10);printf("��ֲ���");
    location(40,10);printf("��ֲ���");
    location(55,10);printf("�ջ�����");
    while(p!=NULL)
    {
        if(j%7==0&&j!=0)
        {
            printf("\n\n\t\t��ҳ�޷���ȷ��ʾ������Ϣ���밴�س�����ҳ!");
            getchar();
            ClearScreen();
            ShowMenu();
            location(15,10);printf("���");
            location(30,10);printf("��ֲ���");
            location(40,10);printf("��ֲ���");
            location(55,10);printf("�ջ�����");
            i=1;
        }
        j++;
        location(15,10+2*i);printf("%d",p->n);
        location(30,10+2*i);printf("%s",p->year);
        location(43,10+2*i);printf("%d",p->area);
        location(55,10+2*i);printf("%f",p->h);
        i++;
        p=p->next;
    }
    location(10,10+2*i);printf("��������Ҫ�޸ĵ���ֲ��Ϣ��ţ�");
    location(40,10+2*i);scanf("%d",&n);getchar();
    i++;
    p=pbasic->cnext;
    while(p!=NULL)
    {
        if(p->n==n)
        {
            break;
        }
        p=p->next;
    }
    if(p==NULL)
    {
        char *notice2[] = {"    �ñ�Ų�����!","�޸��߲���ֲ��Ϣʧ��!",
                    "ȷ��"
                    };
        ClearScreen();
        ShowMenu();
        ShowModule(notice2, 3);

        return;
    }
    char *notice3[] = {"�޸���ֲ���","�޸���ֲ���","�޸��ջ�����",
                    "����"
                    };
    ClearScreen();
    ShowMenu();
    int x=ShowModule4(notice3, 4);
    switch(x)
    {
        case 1:
            location(25,12);printf("�������޸ĺ����ݣ�");
            location(40,14);scanf("%s",year);

            while(p2!=NULL)
            {
                if(strcmp(p2->year,year)==0)
                {
                    break;
                }
                p2=p2->next;
            }
            if(p2!=NULL)
            {
                char *notice3[] = {"  �������Ϣ�Ѵ���!",
                                   "�޸��߲���ֲ��Ϣʧ��!",
                                   "ȷ��"
                                  };
                ClearScreen();
                ShowMenu();
                ShowModule(notice3, 3);
                return;
            }
            strcpy(p->year,year);
            break;
        case 2:
            location(25,12);printf("�������޸ĺ����ֲ�����");
            location(40,14);scanf("%d",&p->area);
            break;
        case 3:
            location(25,12);printf("�������޸ĺ���ջ�������");
            location(40,14);scanf("%f",&p->h);
            break;
        case 4:
            ClearScreen();
            ShowMenu();
            return;
    }
    char *notice4[] = {"�޸��߲���ֲ��Ϣ�ɹ�!",
                        "ȷ��"
                    };
    ClearScreen();
    ShowMenu();
    ShowModule(notice4, 2);
    return;
}

/********
�������ƣ�UpdateNum
�������ܣ����߲���ֲ��Ϣ����ֲ��������������α��
�����������
�����������
�� �� ֵ��void���ͣ��޷���ֵ
����˵������
********/
void UpdateNum(void)
{
    T *ptype=gp_head;
    B *pbasic;
    P *pplant;
    while(ptype!=NULL)
    {
        pbasic=ptype->snext;
        while(pbasic!=NULL)
        {
            pplant=pbasic->cnext;
            int len=0;

            while(pplant!=NULL)
            {
                len++;
                pplant=pplant->next;
            }
            pplant=pbasic->cnext;
            SortPlantInfo(pplant,len);             /*����ֲ��ݽ����������α��*/
            pbasic=pbasic->next;
        }
        ptype=ptype->next;
    }
}

/********
�������ƣ�SortPlantInfo
�������ܣ���������߲���ֲ��Ϣ����ݵ�������
���������headΪ�߲���ֲ��Ϣ����ͷ���ָ��
           lenΪ�߲���ֲ��Ϣ���ĳ���
�����������
�� �� ֵ��void���ͣ��޷���ֵ
����˵������
********/
void SortPlantInfo(P *head,int len)
{
    P *p=head,*q;
    int i,j;
    for(i=0;i<len-1;i++,p=p->next)
    {
        for(j=i+1,q=p->next;j<len;j++,q=q->next)
        {
            if(strcmp(p->year,q->year)>0)
            {
                int area;
                float h;
                char name[20];
                char year[5];
                area=p->area;p->area=q->area;q->area=area;
                h=p->h;p->h=q->h;q->h=h;
                strcpy(name,p->name);strcpy(p->name,q->name);strcpy(q->name,name);
                strcpy(year,p->year);strcpy(p->year,q->year);strcpy(q->year,year);
            }
        }
    }
    i=1;
    p=head;
    while(p!=NULL)
    {
        p->n=i++;
        p=p->next;
    }
}

/********
�������ƣ�DelPlantInfo
�������ܣ�ɾ���߲���ֲ��Ϣ
���������hdΪ�߲���ֲ��Ϣ����ͷ���ָ��
�����������
�� �� ֵ��void���ͣ��޷���ֵ
����˵������
********/
void DelPlantInfo(T* hd)
{
    T *ptype=hd;
    B *pbasic;
    P *pplant1,*pplant2,*p;
    char name[20];
    int n,i=1,j=0;
    int find=0;
    UpdateNum();
    location(25,6);printf("��������Ҫɾ����ֲ��Ϣ���߲����ƣ�");
    location(35,8);scanf("%s",name);
    getchar();
    ClearScreen();
    ShowMenu();

    while(ptype!=NULL)
    {
        pbasic=ptype->snext;
        while(pbasic!=NULL)
        {
            if(strcmp(pbasic->name,name)==0)
            {
                find=1;
                break;
            }
            pbasic=pbasic->next;
        }
        if(find==1)   break;
        ptype=ptype->next;
    }
    if(find==0)
    {
        char *notice1[] = {"    ���߲˲�����!","ɾ���߲���ֲ��Ϣʧ��!",
                    "ȷ��"
                    };
        ShowModule(notice1, 3);
        ClearScreen();
        ShowMenu();
        return;
    }
    location(25,6);printf("��ǰ���߲���ֲ��Ϣ�������£�");
    location(20,8);printf("�߲˱�ţ�");
    location(30,8);printf("%d",pbasic->num);
    location(40,8);printf("�߲����ƣ�");
    location(50,8);printf("%s",pbasic->name);

    p=pbasic->cnext;
    if(p==NULL)
    {
        ClearScreen();
        ShowMenu();
        char *notice4[] = {"���߲�δ¼���κ���ֲ��Ϣ!",
                            "ȷ��"
                            };
        ShowModule(notice4, 2);
        return;
    }
    location(15,10);printf("���");
    location(30,10);printf("��ֲ���");
    location(40,10);printf("��ֲ���");
    location(55,10);printf("�ջ�����");
    while(p!=NULL)
    {
        if(j%7==0&&j!=0)
        {
            printf("\n\n\t\t��ҳ�޷���ȷ��ʾ������Ϣ���밴�س�����ҳ!");
            getchar();
            ClearScreen();
            ShowMenu();
            location(15,10);printf("���");
            location(30,10);printf("��ֲ���");
            location(40,10);printf("��ֲ���");
            location(55,10);printf("�ջ�����");
            i=1;
        }
        location(15,10+2*i);printf("%d",p->n);
        location(30,10+2*i);printf("%s",p->year);
        location(43,10+2*i);printf("%d",p->area);
        location(55,10+2*i);printf("%f",p->h);
        i++;
        p=p->next;
    }
    location(10,10+2*i);printf("��������Ҫɾ����ֲ��Ϣ�ı�ţ�");
    location(40,10+2*i);scanf("%d",&n);
    find=0;
    pplant1=pbasic->cnext;
    while(pplant1!=NULL)
    {
        if(pplant1->n==n)
        {
            find=1;
            break;
        }
        pplant2=pplant1;
        pplant1=pplant1->next;
    }
    if(find==0)
    {
        char *notice2[] = {"    �ñ�Ų�����!","ɾ���߲���ֲ��Ϣʧ��!",
                    "ȷ��"
                    };
        ClearScreen();
        ShowMenu();
        ShowModule(notice2, 3);
        return;
    }

    if(pplant1==pbasic->cnext)
    {
        pbasic->cnext=pplant1->next;
    }
    else
    {
        pplant2->next=pplant1->next;
    }
    free(pplant1);
    char *notice3[] = {"ɾ���߲���ֲ��Ϣ�ɹ�!",
                    "ȷ��"
                    };
    ClearScreen();
    ShowMenu();
    ShowModule(notice3, 2);
    UpdateNum();
    return;
}

/********
�������ƣ�QueryTypeInfo
�������ܣ���ѯ�߲�������Ϣ
�����������
�����������
�� �� ֵ��BOOL���ͣ����Ƿ���TRUE
����˵������
********/
BOOL QueryTypeInfo(void)
{
    char *plabel_name[] = {"���˵�����ݲ�ѯ",
                           "�Ӳ˵���߲������Ϣ",
                           "ȷ��"
                          };
    ShowModule(plabel_name, 3);

    char type;
    T *ptype=gp_head;
    B *pbasic;
    N *pnutri;
    int find=0,j=0,i=12;
    location(15,6);printf("��������Ҫ���ҵ��߲������룺");
    location(45,6);scanf("%c",&type);
    getchar();
    while(ptype!=NULL)
    {
        if(ptype->type==type)
        {
            find=1;break;
        }
        ptype=ptype->next;
    }
    if(find==1)
    {
        location(10,8);printf("������룺");
        location(20,8);printf("%c",ptype->type);
        location(30,8);printf("�������ƣ�");
        location(40,8);printf("%s",ptype->name);
        location(10,10);printf("�������");
        location(20,10);printf("��������");
        location(30,10);printf("�߲�����");
        location(40,10);printf("�߲˱��");
        location(50,10);printf("Ӫ���ɷ�");
        pbasic=ptype->snext;
        while(pbasic!=NULL)
        {
            if(j%7==0&&j!=0)
            {
                printf("\n\n\t\t��ҳ�޷���ȷ��ʾ������Ϣ���밴�س�����ҳ!");
                getchar();
                ClearScreen();
                ShowMenu();
                location(10,8);printf("�������");
                location(20,8);printf("��������");
                location(30,8);printf("�߲�����");
                location(40,8);printf("�߲˱��");
                location(50,8);printf("Ӫ���ɷ�");
                i=10;
            }
            j++;
            location(13,i);printf("%c",ptype->type);
            location(22,i);printf("%s",ptype->name);
            location(33,i);printf("%s",pbasic->name);
            location(42,i);printf("%d",pbasic->num);
            location(50,i);
            int k=0;
            pnutri=pbasic->snext;
            while(pnutri!=NULL)
            {
                printf("%s  ",pnutri->n);
                pnutri=pnutri->next;
                k++;
                if(k%4==0)
                {
                    i=i+1;
                    location(50,i);
                }
            }
            i=i+2;
            pbasic=pbasic->next;
        }
        printf("\n\n\t\t\t    �����������������");
        getchar();
        ClearScreen();
        ShowMenu();
    }
    else
    {
        char *notice1[] = {"  �÷�����벻����!","��ѯ�߲�������Ϣʧ��!",
                    "ȷ��"
                    };
        ClearScreen();
        ShowMenu();
        ShowModule(notice1, 3);
    }
    return TRUE;
}

/********
�������ƣ�QueryBasicInfo
�������ܣ������߲˻�����Ϣ
�����������
�����������
�� �� ֵ��BOOL���ͣ����Ƿ���TRUE
����˵������
********/
BOOL QueryBasicInfo(void)
{
    char *plabel_name1[] = {"���˵�����ݲ�ѯ",
                           "�Ӳ˵���߲˻�����Ϣ",
                           "ȷ��"
                          };
    ShowModule(plabel_name1, 3);
    char *plabel_name2[] = {"���߲����������ַ��Ӵ���ѯ",
                            "�Է������Ӫ���ɷ�Ϊ������ѯ",
                            "����"
                            };
    int x=ShowModule3(plabel_name2, 3);
    BOOL flag=TRUE;
    switch(x)
    {
        case 1:
            flag=QueryBasicInfo1();
            break;
        case 2:
            flag=QueryBasicInfo2();
            break;
        case 3:
            return TRUE;
    }
    if(flag==FALSE)
    {
        char *notice3[] = {"δ��ѯ������������������Ϣ!","   ��ѯ�߲�������Ϣʧ��!",
                    "ȷ��"
                    };
        ClearScreen();
        ShowMenu();
        ShowModule(notice3, 3);
    }
    ClearScreen();
    ShowMenu();
    return TRUE;
}

/********
�������ƣ�QueryBasicInfo1
�������ܣ����߲����������ַ��Ӵ���ѯ�߲˻�����Ϣ
�����������
�����������
�� �� ֵ��BOOL���ͣ���ѯ���������TRUE�����򷵻�FALSE
����˵������
********/
BOOL QueryBasicInfo1(void)
{
    char name[20];
    T *ptype=gp_head;;
    B *pbasic;
    N *pnutri;
    int find=0;
    int i=10,j=0;

    location(15,6);printf("��������Ҫ���ҵ������Ӵ���Ϣ��");
    location(45,6);scanf("%s",name);
    getchar();
    location(10,8);printf("�������");
    location(20,8);printf("��������");
    location(30,8);printf("�߲�����");
    location(40,8);printf("�߲˱��");
    location(50,8);printf("Ӫ���ɷ�");

    while(ptype!=NULL)
    {
        pbasic=ptype->snext;
        while(pbasic!=NULL)
        {
            if(strstr(pbasic->name,name)!=NULL)
            {
                if(j%7==0&&j!=0)
                {
                    printf("\n\n\t\t��ҳ�޷���ȷ��ʾ������Ϣ���밴�س�����ҳ!");
                    getchar();
                    ClearScreen();
                    ShowMenu();
                    location(10,8);printf("�������");
                    location(20,8);printf("��������");
                    location(30,8);printf("�߲�����");
                    location(40,8);printf("�߲˱��");
                    location(50,8);printf("Ӫ���ɷ�");
                    i=10;
                }
                j++;
                find=1;
                location(13,i);printf("%c",ptype->type);
                location(22,i);printf("%s",ptype->name);
                location(33,i);printf("%s",pbasic->name);
                location(42,i);printf("%d",pbasic->num);
                location(50,i);
                int k=0;
                pnutri=pbasic->snext;
                while(pnutri!=NULL)
                {
                    printf("%s  ",pnutri->n);
                    pnutri=pnutri->next;
                    k++;
                    if(k%4==0)
                    {
                        i=i+1;
                        location(50,i);
                    }
                }
                i=i+2;
            }
            pbasic=pbasic->next;
        }
        ptype=ptype->next;
    }
    if(find==0)return FALSE;
    printf("\n\n\t\t\t    �����������������");
    getchar();
    return TRUE;
}

/********
�������ƣ�QueryBasicInfo2
�������ܣ��Է������Ӫ���ɷ�Ϊ������ѯ�߲˻�����Ϣ
�����������
�����������
�� �� ֵ��BOOL���ͣ���ѯ���������TRUE�����򷵻�FALSE
����˵������
********/
BOOL QueryBasicInfo2(void)
{
    T *ptype=gp_head;
    B *pbasic;
    N *pnutri;
    int find= 0;
    char type;
    char nutri[20];
    int i=12,j=0;

    location(15,6);printf("��������Ҫ���ҵķ����룺");
    location(45,6);scanf("%c",&type);
    location(15,8);printf("��������Ҫ���ҵ�Ӫ���ɷ֣�");
    location(45,8);scanf("%s",nutri);
    getchar();

    location(15,10);printf("�������");
    location(25,10);printf("��������");
    location(35,10);printf("�߲�����");
    location(45,10);printf("�߲˱��");

    while(ptype!=NULL)
    {
        if(ptype->type==type)
        {
            pbasic=ptype->snext;
            while(pbasic!=NULL)
            {
                pnutri=pbasic->snext;
                while(pnutri!=NULL)
                {
                    if(strcmp(pnutri->n,nutri)==0)
                    {
                        if(j%7==0&&j!=0)
                        {
                            printf("\n\n\t\t��ҳ�޷���ȷ��ʾ������Ϣ���밴�س�����ҳ!");
                            getchar();
                            ClearScreen();
                            ShowMenu();
                            location(15,10);printf("�������");
                            location(25,10);printf("��������");
                            location(35,10);printf("�߲�����");
                            location(45,10);printf("�߲˱��");
                            i=12;
                        }
                        j++;
                        find=1;
                        location(18,i);printf("%c",ptype->type);
                        location(27,i);printf("%s",ptype->name);
                        location(38,i);printf("%s",pbasic->name);
                        location(47,i);printf("%d",pbasic->num);
                        i=i+2;
                    }
                    pnutri=pnutri->next;
                }
                pbasic=pbasic->next;
            }
        }
        ptype=ptype->next;
    }
    if(find==0)return FALSE;
    printf("\n\n\t\t\t    �����������������");
    getchar();
    return TRUE;
}

/********
�������ƣ�QueryPlantInfo
�������ܣ���ѯ�߲���ֲ��Ϣ
�����������
�����������
�� �� ֵ��BOOL���ͣ����Ƿ���TRUE
����˵������
********/
BOOL QueryPlantInfo(void)
{
    char *plabel_name1[] = {"���˵�����ݲ�ѯ",
                           "�Ӳ˵���߲���ֲ��Ϣ",
                           "ȷ��"
                          };
    ShowModule(plabel_name1, 3);
    char *plabel_name2[] = {"���߲˲������ƺ���ֲ���Ϊ������ѯ",
                            "     ���߲�����Ϊ������ѯ",
                            "����"
                            };
    int x=ShowModule3(plabel_name2, 3);
    BOOL flag=TRUE;
    switch(x)
    {
        case 1:
            flag=QueryPlantInfo1();
            break;
        case 2:
            flag=QueryPlantInfo2();
            break;
        case 3:
            return TRUE;
    }
    if(flag==FALSE)
    {
        char *notice3[] = {"δ��ѯ������������������Ϣ!","   ��ѯ�߲�������Ϣʧ��!",
                    "ȷ��"
                    };
        ClearScreen();
        ShowMenu();
        ShowModule(notice3, 3);
    }
    ClearScreen();
    ShowMenu();
    return TRUE;
}

/********
�������ƣ�QueryPlantInfo1
�������ܣ����߲˲������ƺ���ֲ���Ϊ������ѯ�߲���ֲ��Ϣ
�����������
�����������
�� �� ֵ��BOOL���ͣ���ѯ���������TRUE�����򷵻�FALSE
����˵������
********/
BOOL QueryPlantInfo1(void)
{
    T *ptype=gp_head;
    B *pbasic;
    P *pplant;
    int find= 0;
    char name[20];
    char year[5];
    int i=12,j=0;

    location(10,6);printf("��������Ҫ���ҵ��߲˵Ĳ������ƣ�");
    location(45,6);scanf("%s",name);
    location(15,8);printf("��������Ҫ���ҵ���ݣ�");
    location(45,8);scanf("%s",year);
    getchar();

    location(10,10);printf("������");
    location(20,10);printf("��������");
    location(30,10);printf("�߲�����");
    location(40,10);printf("��ֲ���");
    location(50,10);printf("��ֲ���");
    location(60,10);printf("�ջ�����");

    ptype=gp_head;
    while(ptype!=NULL)
    {
        pbasic=ptype->snext;
        while(pbasic!=NULL)
        {
            if(strstr(pbasic->name,name)!=NULL)
            {
                pplant=pbasic->cnext;
                if(pplant==NULL)
                {
                    ClearScreen();
                    ShowMenu();
                    char *notice3[] = {"���߲�δ¼���κ���ֲ��Ϣ",
                                        "ȷ��"
                                        };
                    ShowModule(notice3, 2);
                    return FALSE;
                }
                while(pplant!=NULL)
                {
                    if(strcmp(pplant->year,year)==0)
                    {
                        if(j%7==0&&j!=0)
                        {
                            printf("\n\n\t\t��ҳ�޷���ȷ��ʾ������Ϣ���밴�س�����ҳ!");
                            getchar();
                            ClearScreen();
                            ShowMenu();
                            location(10,10);printf("������");
                            location(20,10);printf("��������");
                            location(30,10);printf("�߲�����");
                            location(40,10);printf("��ֲ���");
                            location(50,10);printf("��ֲ���");
                            location(60,10);printf("�ջ�����");
                            i=12;
                        }
                        j++;
                        find=1;
                        location(13,i);printf("%c",ptype->type);
                        location(22,i);printf("%s",ptype->name);
                        location(32,i);printf("%s",pbasic->name);
                        location(41,i);printf("%s",pplant->year);
                        location(53,i);printf("%d",pplant->area);
                        location(60,i);printf("%f",pplant->h);
                        i=i+2;
                    }
                    pplant=pplant->next;
                }
            }
            pbasic=pbasic->next;
        }
        ptype=ptype->next;
    }
    if(find==0)return FALSE;
    printf("\n\n\t\t\t    �����������������");
    getchar();
    return TRUE;
}

/********
�������ƣ�QueryPlantInfo2
�������ܣ����߲�����Ϊ������ѯ�߲���ֲ��Ϣ
�����������
�����������
�� �� ֵ��BOOL���ͣ���ѯ���������TRUE�����򷵻�FALSE
����˵������
********/
BOOL QueryPlantInfo2(void)
{
    T *ptype=gp_head;
    B *pbasic;
    P *pplant;
    int find= 0;
    char name[20];
    int i=12;
    UpdateNum();

    location(10,6);printf("��������Ҫ���ҵ��߲˵����ƣ�");
    location(45,6);scanf("%s",name);
    getchar();
    location(10,8);printf("�����룺");
    location(30,8);printf("�������ƣ�");
    location(50,8);printf("�߲����ƣ�");
    location(15,10);printf("���");
    location(25,10);printf("��ֲ���");
    location(40,10);printf("��ֲ���");
    location(55,10);printf("�ջ�����");

    while(ptype!=NULL)
    {
        pbasic=ptype->snext;
        while(pbasic!=NULL)
        {
            if(strcmp(pbasic->name,name)==0)
            {
                find=1;
                location(20,8);printf("%c",ptype->type);
                location(40,8);printf("%s",ptype->name);
                location(60,8);printf("%s",pbasic->name);
                pplant=pbasic->cnext;
                if(pplant==NULL)
                {
                    ClearScreen();
                    ShowMenu();
                    char *notice3[] = {"���߲�δ¼���κ���ֲ��Ϣ",
                                        "ȷ��"
                                        };
                    ShowModule(notice3, 2);
                    return FALSE;
                }
                int j=0;
                while(pplant!=NULL)
                {
                    if(j%7==0&&j!=0&&pplant->next!=NULL)
                    {
                        printf("\n\n\t\t��ҳ�޷���ȷ��ʾ������Ϣ���밴�س�����ҳ!");
                        getchar();
                        ClearScreen();
                        ShowMenu();
                        location(10,8);printf("�����룺");location(20,8);printf("%c",ptype->type);
                        location(30,8);printf("�������ƣ�");location(40,8);printf("%s",ptype->name);
                        location(50,8);printf("�߲����ƣ�");location(60,8);printf("%s",pbasic->name);
                        location(15,10);printf("���");
                        location(25,10);printf("��ֲ���");
                        location(40,10);printf("��ֲ���");
                        location(55,10);printf("�ջ�����");
                        i=12;
                    }
                    j++;
                    location(16,i);printf("%d",pplant->n);
                    location(26,i);printf("%s",pplant->year);
                    location(43,i);printf("%d",pplant->area);
                    location(55,i);printf("%f",pplant->h);
                    i=i+2;
                    pplant=pplant->next;
                }
                break;
            }
            pbasic=pbasic->next;
        }
        if(find==1)break;
        ptype=ptype->next;
    }
    if(find==0)return FALSE;
    printf("\n\n\t\t\t    �����������������");
    getchar();
    return TRUE;
}

/********
�������ƣ�StatVePlant
�������ܣ�ͳ��ĳ��������߲���ֲ���
�����������
�����������
�� �� ֵ��BOOL���ͣ����Ƿ���TRUE
����˵������
********/
BOOL StatVePlant(void)
{
    char *plabel_name[] = {"���˵������ͳ��",
                           "�Ӳ˵��ĳ��������߲���ֲ��Ϣ",
                           "ȷ��"
                          };
    ShowModule(plabel_name, 3);

    int find= 0;
    char year[5];
    int i=10;
    int len=0;
    T *ptype=gp_head;
    B *pbasic;
    P *pplant;
    struct y_p *head,*p;
    head=(struct y_p*)malloc(sizeof(struct y_p));
    head->next=NULL;

    location(15,6);printf("��������Ҫ���ҵ���ݣ�");
    location(45,6);scanf("%s",year);
    getchar();

    p=head;
    while(ptype!=NULL)
    {
        p->type=ptype->type;
        strcpy(p->name,ptype->name);
        p->area=0;p->h=0;
        p->next=NULL;

        pbasic=ptype->snext;
        while(pbasic!=NULL)
        {
            pplant=pbasic->cnext;
            while(pplant!=NULL)
            {
                if(strcmp(pplant->year,year)==0)
                {
                    find=1;
                    p->area=p->area+pplant->area;
                    p->h=p->h+pplant->h;
                    break;
                }
                pplant=pplant->next;
            }
            pbasic=pbasic->next;
        }
        ptype=ptype->next;
        if(ptype!=NULL)
        {
            p->next=(struct y_p*)malloc(sizeof(struct y_p));
            p=p->next;
        }
        len++;
    }
    if(find==0)
    {
        char *notice1[] = {"δ��ѯ������������������Ϣ!","ͳ��ĳһ��������߲���ֲ��Ϣʧ��!",
                    "ȷ��"
                    };
        ClearScreen();
        ShowMenu();
        ShowModule(notice1, 3);
        return TRUE;
    }
    SortVePlant(head,len);
    location(15,8);printf("�������");
    location(27,8);printf("��������");
    location(40,8);printf("��ֲ�����");
    location(55,8);printf("�ջ�������");
    p=head;
    int j=0;
    while(p!=NULL)
    {
        if(j%7==0&&j!=0&&p->next!=NULL)
        {
            printf("\n\n\t\t��ҳ�޷���ȷ��ʾ������Ϣ���밴�س�����ҳ!");
            getchar();
            ClearScreen();
            ShowMenu();
            location(15,6);printf("�������");
            location(28,6);printf("��������");
            location(40,6);printf("��ֲ�����");
            location(55,6);printf("�ջ�������");
            i=8;
        }
        j++;
        location(17,i);printf("%c",p->type);
        location(30,i);printf("%s",p->name);
        location(43,i);printf("%d",p->area);
        location(55,i);printf("%f",p->h);
        i=i+2;
        p=p->next;
    }
    printf("\n\n\t\t\t    �����������������");
    getchar();
    ClearScreen();
    ShowMenu();
    return TRUE;
}

/********
�������ƣ�SortVePlant
�������ܣ���StatVePlant������ͳ�ƽ�������ջ�������������
���������headΪStatVePlant������ͳ�ƽ������ͷ���ָ��
           lenΪStatVePlant������ͳ�ƽ�����ĳ���
�����������
�� �� ֵ��BOOL���ͣ����Ƿ���TRUE
����˵������
********/
BOOL SortVePlant(struct y_p* head,int len)
{
    struct y_p *p=head,*q;
    int i,j;
    for(i=0;i<len-1;i++,p=p->next)                  /*ͨ�������򽻻���������*/
    {
        for(j=i+1,q=p->next;j<len;j++,q=q->next)
        {
            if(p->h<q->h)
            {
                int area;
                float h;
                char type;
                char name[20];
                area=p->area;p->area=q->area;q->area=area;
                h=p->h;p->h=q->h;q->h=h;
                type=p->type;p->type=q->type;q->type=type;
                strcpy(name,p->name);strcpy(p->name,q->name);strcpy(q->name,name);
            }
        }
    }
}

/********
�������ƣ�StatTypeVePlant
�������ܣ�ͳ����ֹ���������߲���ֲ��Ϣ
�����������
�����������
�� �� ֵ��BOOL���ͣ����Ƿ���TRUE
����˵������
********/
BOOL StatTypeVePlant(void)
{
    char *plabel_name[] = {"���˵������ͳ��",
                           "�Ӳ˵����ֹ���������߲���ֲ��Ϣ",
                           "ȷ��"
                          };
    ShowModule(plabel_name, 3);

    int find= 0;
    char year1[5];
    char year2[5];
    int i=10;
    int len=0;
    location(20,4);printf("��������ʼ��ݣ�");
    location(40,4);scanf("%s",year1);
    location(20,6);printf("��������ֹ��ݣ�");
    location(40,6);scanf("%s",year2);
    getchar();

    T *ptype=gp_head;
    B *pbasic;
    P *pplant;
    struct s_e_t *head,*p;
    head=(struct s_e_t*)malloc(sizeof(struct s_e_t));
    head->next=NULL;
    p=head;
    while(ptype!=NULL)                              /*�������������µ�ͳ������ͬʱ��¼ͳ������ĳ���*/
    {
        strcpy(p->name,ptype->name);
        p->type=ptype->type;
        p->area=0;p->h=0;
        p->next=NULL;
        pbasic=ptype->snext;
        while(pbasic!=NULL)
        {
            pplant=pbasic->cnext;
            while(pplant!=NULL)
            {
                if(strcmp(pplant->year,year1)>=0&&strcmp(pplant->year,year2)<=0)
                {
                    find=1;
                    p->area=p->area+pplant->area;
                    p->h=p->h+pplant->h;
                }
                pplant=pplant->next;
            }
            pbasic=pbasic->next;
        }
        ptype=ptype->next;
        if(ptype!=NULL)
        {
            p->next=(struct s_e_t*)malloc(sizeof(struct s_e_t));
            p=p->next;
        }
        len++;
    }
    if(find==0)
    {
        char *notice1[] = {"δ��ѯ������������������Ϣ!","ͳ����ֹ���������߲���ֲ��Ϣʧ��!",
                    "ȷ��"
                    };
        ClearScreen();
        ShowMenu();
        ShowModule(notice1, 3);
        return TRUE;
    }
    SortTypeVePlant(head,len);
    location(15,8);printf("�������");
    location(27,8);printf("��������");
    location(40,8);printf("��ֲ�����");
    location(55,8);printf("�ջ�������");
    p=head;
    int j=0;
    while(p!=NULL)
    {
        if(j%7==0&&j!=0&&p->next!=NULL)
        {
            printf("\n\n\t\t��ҳ�޷���ȷ��ʾ������Ϣ���밴�س�����ҳ��");
            getchar();
            ClearScreen();
            ShowMenu();
            location(15,6);printf("�������");
            location(27,6);printf("��������");
            location(40,6);printf("��ֲ�����");
            location(55,6);printf("�ջ�������");
            i=8;
        }
        j++;
        location(18,i);printf("%c",p->type);
        location(30,i);printf("%s",p->name);
        location(43,i);printf("%d",p->area);
        location(55,i);printf("%f",p->h);
        i=i+2;
        p=p->next;
    }
    printf("\n\n\t\t\t    �����������������");
    getchar();
    ClearScreen();
    ShowMenu();
    return TRUE;
}
/********
�������ƣ�SortVePlant
�������ܣ���StatTypeVePlant������ͳ�ƽ�����ջ�������������
���������headΪStatVePlant������ͳ�ƽ������ͷ���ָ��
           lenΪStatVePlant������ͳ�ƽ�����ĳ���
�����������
�� �� ֵ��BOOL���ͣ����Ƿ���TRUE
����˵������
********/
BOOL SortTypeVePlant(struct s_e_t *head,int len)
{
    struct s_e_t *p=head,*q;
    int i,j;
    for(i=0;i<len-1;i++,p=p->next)                  /*ͨ�������򽻻���������*/
    {
        for(j=i+1,q=p->next;j<len;j++,q=q->next)
        {
            if(p->h<q->h)
            {
                int area;
                float h;
                char type;
                char name[20];
                area=p->area;p->area=q->area;q->area=area;
                h=p->h;p->h=q->h;q->h=h;
                type=p->type;p->type=q->type;q->type=type;
                strcpy(name,p->name);strcpy(p->name,q->name);strcpy(q->name,name);
            }
        }
    }
}

/********
�������ƣ�StatVePlantTotal
�������ܣ�ͳ����ֹ�����߲���ֲ���
�����������
�����������
�� �� ֵ��BOOL���ͣ����Ƿ���TRUE
����˵������
********/
BOOL StatVePlantTotal(void)
{
    char *plabel_name[] = {"���˵������ͳ��",
                           "�Ӳ˵����ֹ�����߲���ֲ��Ϣ",
                           "ȷ��"
                          };
    ShowModule(plabel_name, 3);

    int find= 0;
    char year1[5];
    char year2[5];
    int i=10;
    int len=0;
    location(20,4);printf("��������ʼ��ݣ�");
    location(40,4);scanf("%s",year1);
    location(20,6);printf("��������ֹ��ݣ�");
    location(40,6);scanf("%s",year2);
    getchar();

    T *ptype=gp_head;
    B *pbasic;
    P *pplant;
    struct s_e_p *head,*p;
    head=(struct s_e_p*)malloc(sizeof(struct s_e_p));
    head->next=NULL;
    p=head;
    while(ptype!=NULL)                              /*�������������µ�ͳ������ͬʱ��¼ͳ������ĳ���*/
    {
        pbasic=ptype->snext;
        while(pbasic!=NULL)
        {
            strcpy(p->t_name,ptype->name);
            strcpy(p->ve_name,pbasic->name);
            p->area=0;p->h=0;
            p->next=NULL;
            pplant=pbasic->cnext;
            while(pplant!=NULL)
            {
                if(strcmp(pplant->year,year1)>=0&&strcmp(pplant->year,year2)<=0)
                {
                    find=1;
                    p->area=p->area+pplant->area;
                    p->h=p->h+pplant->h;
                }
                pplant=pplant->next;
            }
            if(pbasic->next!=NULL||ptype->next!=NULL)
            {
                p->next=(struct s_e_p*)malloc(sizeof(struct s_e_p));
                p=p->next;
            }
            len++;
            pbasic=pbasic->next;
        }
        ptype=ptype->next;
    }
    if(find==0)
    {
        char *notice1[] = {"δ��ѯ������������������Ϣ!","ͳ����ֹ���������߲���ֲ��Ϣʧ��!",
                    "ȷ��"
                    };
        ClearScreen();
        ShowMenu();
        ShowModule(notice1, 3);
        return TRUE;
    }
    SortVePlantTotal(head,len);
    location(15,8);printf("�߲�����");
    location(27,8);printf("��������");
    location(40,8);printf("��ֲ�����");
    location(55,8);printf("�ջ�������");
    p=head;
    int j=0;
    while(p!=NULL)
    {
        if(j%7==0&&j!=0&&p->next!=NULL)
        {
            printf("\n\n\t\t��ҳ�޷���ȷ��ʾ������Ϣ���밴�س�����ҳ��");
            getchar();
            ClearScreen();
            ShowMenu();
            location(15,6);printf("�߲�����");
            location(27,6);printf("��������");
            location(40,6);printf("��ֲ�����");
            location(55,6);printf("�ջ�������");
            i=8;
        }
        j++;
        location(18,i);printf("%s",p->ve_name);
        location(30,i);printf("%s",p->t_name);
        location(43,i);printf("%d",p->area);
        location(55,i);printf("%f",p->h);
        i=i+2;
        p=p->next;
    }
    printf("\n\n\t\t\t    �����������������");
    getchar();
    ClearScreen();
    ShowMenu();
    return TRUE;
}

/********
�������ƣ�SortVePlantTotal
�������ܣ���StatVePlantTotal������ͳ�ƽ�������ջ�������������
���������headΪStatVePlantTotal������ͳ�ƽ������ͷ���ָ��
           lenΪStatVePlantTotal������ͳ�ƽ�����ĳ���
�����������
�� �� ֵ��BOOL���ͣ����Ƿ���TRUE
����˵������
********/
BOOL SortVePlantTotal(struct s_e_p* head,int len)
{
    struct s_e_p *p=head,*q;
    int i,j;
    for(i=0;i<len-1;i++,p=p->next)                  /*ͨ�������򽻻���������*/
    {
        for(j=i+1,q=p->next;j<len;j++,q=q->next)
        {
            if(p->h<q->h)
            {
                int area;
                float h;
                char name1[20];
                char name2[20];
                area=p->area;p->area=q->area;q->area=area;
                h=p->h;p->h=q->h;q->h=h;
                strcpy(name1,p->ve_name);strcpy(p->ve_name,q->ve_name);strcpy(q->ve_name,name1);
                strcpy(name2,p->t_name);strcpy(p->t_name,q->t_name);strcpy(q->t_name,name2);
            }
        }
    }
}

/********
�������ƣ�StatCount
�������ܣ�ͳ��ĳ�����߲���������
�����������
�����������
�� �� ֵ��BOOL���ͣ����Ƿ���TRUE
����˵������
********/
BOOL StatCount(void)
{
    char *plabel_name[] = {"���˵������ͳ��",
                           "�Ӳ˵��ĳ�߲���������",
                           "ȷ��"
                          };
    ShowModule(plabel_name, 3);

    int find= 0;
    int len=0;
    T *ptype=gp_head;
    B *pbasic;
    P *pplant;
    struct v_count *head,*p;
    head=(struct v_count*)malloc(sizeof(struct v_count));
    head->next=NULL;
    p=head;

    while(ptype!=NULL)
    {
        p->type=ptype->type;
        strcpy(p->name,ptype->name);
        p->h=0;
        p->next=NULL;
        pbasic=ptype->snext;
        while(pbasic!=NULL)
        {
            pplant=pbasic->cnext;
            while(pplant!=NULL)
            {
                find=1;
                p->h=p->h+pplant->h;
                pplant=pplant->next;
            }

            pbasic=pbasic->next;
        }
        ptype=ptype->next;
        if(ptype!=NULL)
        {
            p->next=(struct v_count*)malloc(sizeof(struct v_count));
            p=p->next;
        }
        len++;
    }
    if(find==0)
    {
        char *notice1[] = {"δ�����κ��߲���ֲ��Ϣ!","ͳ�Ƹ������߲�������ʧ��!",
                    "ȷ��"
                    };
        ShowModule(notice1, 3);
        return TRUE;
    }
    SortCount(head,len);
    location(15,6);printf("�������");
    location(35,6);printf("��������");
    location(55,6);printf("�ջ�������");
    p=head;
    int j=0;
    int i=8;
    while(p!=NULL)                                  /*�������������������Ϣ*/
    {
        if(j%7==0&&j!=0&&p->next!=NULL)             /*���ǵ���Ļ�������٣���ʾ��ҳ����*/
        {
            printf("\n\n\t\t��ҳ�޷���ȷ��ʾ������Ϣ���밴�س�����ҳ!");
            getchar();
            ClearScreen();
            ShowMenu();
            location(15,6);printf("�������");
            location(35,6);printf("��������");
            location(55,6);printf("�ջ�������");
            i=8;
        }
        j++;
        location(17,i);printf("%c",p->type);
        location(37,i);printf("%s",p->name);
        location(55,i);printf("%f",p->h);
        i=i+2;
        p=p->next;
    }
    printf("\n\n\t\t\t    �����������������");
    getchar();
    ClearScreen();
    ShowMenu();
    return TRUE;
}

/********
�������ƣ�SortCount
�������ܣ���StatCount������ͳ�ƽ������������������
���������headΪStatCount������ͳ�ƽ������ͷ���ָ��
           lenΪStatCount������ͳ�ƽ�����ĳ���
�����������
�� �� ֵ��BOOL���ͣ����Ƿ���TRUE
����˵������
********/
BOOL SortCount(struct v_count*head,int len)
{
    struct v_count *p=head,*q;
    int i,j;
    for(i=0;i<len-1;i++,p=p->next)                  /*ͨ�������򽻻���������*/
    {
        for(j=i+1,q=p->next;j<len;j++,q=q->next)
        {
            if(p->h<q->h)
            {
                float h;
                char type;
                char name[20];
                h=p->h;p->h=q->h;q->h=h;
                type=p->type;p->type=q->type;q->type=type;
                strcpy(name,p->name);strcpy(p->name,q->name);strcpy(q->name,name);
            }
        }
    }
}

/********
�������ƣ�StatVeNutri
�������ܣ�ͳ�ƺ���ĳ��Ӫ���ɷֵ��߲ˣ���������й���Ϣ
�����������
�����������
�� �� ֵ��BOOL���ͣ����Ƿ���TRUE
����˵������
********/
BOOL StatVeNutri(void)
{
    char *plabel_name[] = {"���˵������ͳ��",
                           "�Ӳ˵������ĳӪ���ɷֵ��߲�",
                           "ȷ��"
                          };
    ShowModule(plabel_name, 3);

    T *ptype=gp_head;
    B *pbasic;
    N *pnutri;
    int find= 0;
    char nutri[20];
    int i=12,j=0;

    location(15,6);printf("��������Ҫ���ҵ�Ӫ���ɷ֣�");
    location(45,6);scanf("%s",nutri);
    getchar();
    location(15,10);printf("�������");
    location(25,10);printf("��������");
    location(35,10);printf("�߲�����");
    location(45,10);printf("�߲˱��");

    while(ptype!=NULL)                              /*����������ѯ�������������򰴸�ʽ����������Ϣ*/
    {
        pbasic=ptype->snext;
        while(pbasic!=NULL)
        {
            pnutri=pbasic->snext;
            while(pnutri!=NULL)
            {
                if(strcmp(pnutri->n,nutri)==0)
                {
                    find=1;
                    if(j%5==0&&j!=0)                /*���ǵ���Ļ�������٣���ʾ��ҳ����*/
                    {
                        printf("\n\n\t\t��ҳ�޷���ȷ��ʾ������Ϣ���밴�س�����ҳ!");
                        getchar();
                        ClearScreen();
                        ShowMenu();
                        location(15,6);printf("�������");
                        location(25,6);printf("��������");
                        location(35,6);printf("�߲�����");
                        location(45,6);printf("�߲˱��");
                        i=8;
                    }
                    j++;
                    location(18,i);printf("%c",ptype->type);
                    location(27,i);printf("%s",ptype->name);
                    location(38,i);printf("%s",pbasic->name);
                    location(48,i);printf("%d",pbasic->num);
                    i=i+2;
                }
                pnutri=pnutri->next;
            }
            pbasic=pbasic->next;
        }
        ptype=ptype->next;
    }
    if(find==0)
    {
        char *notice1[] = {"δ��ѯ������������������Ϣ!","   ��ѯ�߲�������Ϣʧ��!",
                    "ȷ��"
                    };
        ClearScreen();
        ShowMenu();
        ShowModule(notice1, 3);
        return TRUE;
    }
    printf("\n\n\t\t\t    �����������������");
    getchar();
    ClearScreen();
    ShowMenu();
    return TRUE;
}

/********
�������ƣ�HelpTopic
�������ܣ�����������ʾ
�����������
�����������
�� �� ֵ��BOOL���ͣ����Ƿ���TRUE
����˵������
********/
BOOL HelpTopic(void)
{
    char *plabel_name[] = {"���˵������",
                           "�Ӳ˵����������",
                           "ȷ��"
                          };
    ShowModule(plabel_name, 3);
    printf("\n\n\n\n\n\t\t\t������֧���������룬���ͼ��̲�����\n\n");
    printf("\t\t\t��ALT+��ĸ���Կ��ѡ�����˵���\n\n");
    printf("\t\t�������������߼��������������ط��������ʽ���ϸ�Ҫ��\n\n");
    printf("\t\t\t������ϸ����������ʽ>");
    printf("\n\n\t\t\t�����������������");
    getchar();
    ClearScreen();
    ShowMenu();
    return TRUE;
}

/********
�������ƣ�AboutDorm
�������ܣ���ʾһЩ���ڱ��������Ϣ
�����������
�����������
�� �� ֵ��BOOL���ͣ����Ƿ���TRUE
����˵������
********/
BOOL AboutDorm(void)
{
    char *plabel_name[] = {"���˵������",
                           "�Ӳ˵������...",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);

    printf("\n\n\n\n\n\n\t\t\t��������CSIE1601��������������\n\n");
    printf("\t\t�ڴ˶��ڱ�д����ʱ�ṩ������ͬѧ�Ǳ�ʾ��л!");
    printf("\n\n\t\t\t�����������������");
    getchar();
    ClearScreen();
    ShowMenu();
    return TRUE;
}

/********
�������ƣ�ShowModule
�������ܣ���һ����ȷ�ϡ��ַ����ı�ǩ�����ó��������ȴ��û�����
���������pStringΪָ�룬nΪ��ǩ����
�����������
�� �� ֵ��BOOL���ͣ����Ƿ���TRUE
����˵������
********/
BOOL ShowModule(char **pString, int n)
{
    LABEL_BUNDLE labels;
    HOT_AREA areas;
    BOOL bRet = TRUE;
    SMALL_RECT rcPop;
    COORD pos;
    WORD att;
    int iHot = 1;
    int i, maxlen, str_len;

    for (i=0,maxlen=0; i<n; i++) {
        str_len = strlen(pString[i]);
        if (maxlen < str_len) {
            maxlen = str_len;
        }
    }

    pos.X = maxlen + 6;
    pos.Y = n + 5;
    rcPop.Left = (SCR_COL - pos.X) / 2;
    rcPop.Right = rcPop.Left + pos.X - 1;
    rcPop.Top = (SCR_ROW - pos.Y) / 2;
    rcPop.Bottom = rcPop.Top + pos.Y - 1;

    att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
    labels.num = n;
    labels.ppLabel = pString;
    COORD aLoc[n];

    for (i=0; i<n; i++) {
        aLoc[i].X = rcPop.Left + 3;
        aLoc[i].Y = rcPop.Top + 2 + i;

    }
    str_len = strlen(pString[n-1]);
    aLoc[n-1].X = rcPop.Left + 3 + (maxlen-str_len)/2;
    aLoc[n-1].Y = aLoc[n-1].Y + 2;

    labels.pLoc = aLoc;

    areas.num = 1;
    SMALL_RECT aArea[] = {{aLoc[n-1].X, aLoc[n-1].Y,
                           aLoc[n-1].X + 3, aLoc[n-1].Y}};

    char aSort[] = {0};
    char aTag[] = {1};

    areas.pArea = aArea;
    areas.pSort = aSort;
    areas.pTag = aTag;
    PopUp(&rcPop, att, &labels, &areas);

    pos.X = rcPop.Left + 1;
    pos.Y = rcPop.Top + 2 + n;
    FillConsoleOutputCharacter(gh_std_out, '-', rcPop.Right-rcPop.Left-1, pos, &ul);

    DealInput(&areas, &iHot);
    PopOff();

    return bRet;

}

/********
�������ƣ�ShowModule2
�������ܣ�����¼�롱�����޸ġ�����ɾ���������ַ����ı�ǩ�����ó��������ȴ��û�����
���������pStringΪָ�룬nΪ��ǩ����
�����������
�� �� ֵ������굥�������س���ո�ʱ���ص�ǰ�������
����˵������
********/
int ShowModule2(char **pString, int n)
{
    LABEL_BUNDLE labels;
    HOT_AREA areas;
    SMALL_RECT rcPop;
    COORD pos;
    WORD att;
    int iHot = 1;
    int i, maxlen, str_len;

    for (i=0,maxlen=0; i<n; i++) {
        str_len = strlen(pString[i]);
        if (maxlen < str_len) {
            maxlen = str_len;
        }
    }
    if(maxlen<(strlen(pString[2])+strlen(pString[3])+strlen(pString[4])+7+7))
    {
        maxlen=(strlen(pString[2])+strlen(pString[3])+strlen(pString[4])+7+7);
    }

    pos.X = maxlen + 6;
    pos.Y = n - 2 + 5;
    rcPop.Left = (SCR_COL - pos.X) / 2;
    rcPop.Right = rcPop.Left + pos.X - 1;
    rcPop.Top = (SCR_ROW - pos.Y) / 2;
    rcPop.Bottom = rcPop.Top + pos.Y - 1;

    att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
    labels.num = n;
    labels.ppLabel = pString;
    COORD aLoc[n];

    for (i=0; i<n-2-1; i++) {
        aLoc[i].X = rcPop.Left + 3;
        aLoc[i].Y = rcPop.Top + 2 + i;

    }
    for(i=n-2-1;i<n;i++)
    {
        aLoc[i].Y=rcPop.Top + 2 + n - 2 + 1;
    }
    str_len = strlen(pString[3]);
    aLoc[3].X = rcPop.Left + 3 + (maxlen-str_len)/2;
    aLoc[2].X=aLoc[3].X - 7;
    aLoc[4].X=aLoc[3].X + 7;


    labels.pLoc = aLoc;

    areas.num = 3;
    SMALL_RECT aArea[] = {{aLoc[2].X, aLoc[2].Y,aLoc[2].X + 3, aLoc[2].Y},
						  {aLoc[3].X, aLoc[3].Y,aLoc[3].X + 3, aLoc[3].Y},
						  {aLoc[4].X, aLoc[4].Y,aLoc[4].X + 3, aLoc[4].Y}
						  };

    char aSort[] = {0,0,0};
    char aTag[] = {1,2,3};

    areas.pArea = aArea;
    areas.pSort = aSort;
    areas.pTag = aTag;
    PopUp(&rcPop, att, &labels, &areas);

    pos.X = rcPop.Left + 1;
    pos.Y = rcPop.Top + 2 + n-2;
    FillConsoleOutputCharacter(gh_std_out, '-', rcPop.Right-rcPop.Left-1, pos, &ul);

    int x;
    x=DealInput(&areas, &iHot);
    PopOff();

    return x;
}

/********
�������ƣ�ShowModule3
�������ܣ��������ַ�����һ�������ء��ַ����ı�ǩ�����ó��������ȴ��û�����
���������pStringΪָ�룬nΪ��ǩ����
�����������
�� �� ֵ������굥�������س���ո�ʱ���ص�ǰ�������
����˵������
********/
int ShowModule3(char **pString, int n)
{
    LABEL_BUNDLE labels;
    HOT_AREA areas;
    SMALL_RECT rcPop;
    COORD pos;
    WORD att;
    int iHot = 1;
    int i, maxlen, str_len,x;

    for (i=0, maxlen=0; i<n; i++)
    {
        str_len = strlen(pString[i]);
        if (maxlen < str_len)
        {
            maxlen = str_len;
        }
    }

    pos.X = maxlen + 6;
    pos.Y = n + 5;
    rcPop.Left = (SCR_COL - pos.X) / 2;
    rcPop.Right = rcPop.Left + pos.X - 1;
    rcPop.Top = (SCR_ROW - pos.Y) / 2;
    rcPop.Bottom = rcPop.Top + pos.Y - 1;

    att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
    labels.num = n;
    labels.ppLabel = pString;
    COORD aLoc[n];

    for (i=0; i<n-1; i++)
    {
        aLoc[i].X = rcPop.Left + 3;
        aLoc[i].Y = rcPop.Top + 2 + i*2;
    }
    aLoc[n-1].Y = rcPop.Top + 2 + n-1;

    str_len = strlen(pString[n-1]);
    aLoc[n-1].X = rcPop.Left + 3 + (maxlen-str_len)/2;
    aLoc[n-1].Y = aLoc[n-1].Y + 2;

    labels.pLoc = aLoc;

    areas.num = 3;
    SMALL_RECT aArea[] = {{aLoc[0].X, aLoc[0].Y,
                        aLoc[0].X + maxlen - 1, aLoc[0].Y},
                        {aLoc[1].X, aLoc[1].Y,
                        aLoc[1].X + maxlen - 1, aLoc[1].Y},
                        {aLoc[2].X, aLoc[2].Y,
                        aLoc[2].X + 3, aLoc[2].Y}
                        };

    char aSort[] = {0, 0, 0};
    char aTag[] = {1, 2, 3};

    areas.pArea = aArea;
    areas.pSort = aSort;
    areas.pTag = aTag;
    PopUp(&rcPop, att, &labels, &areas);

    pos.X = rcPop.Left + 1;
    pos.Y = rcPop.Top + 2 + n;
    FillConsoleOutputCharacter(gh_std_out, '-', rcPop.Right-rcPop.Left-1, pos, &ul);
    x = DealInput(&areas, &iHot);
    PopOff();
    return x;
}

/********
�������ƣ�ShowModule4
�������ܣ��������ַ�����һ�������ء��ַ����ı�ǩ�����ó��������ȴ��û�����
���������pStringΪָ�룬nΪ��ǩ����
�����������
�� �� ֵ������굥�������س���ո�ʱ���ص�ǰ�������
����˵������
********/
int ShowModule4(char **pString, int n)
{
    LABEL_BUNDLE labels;
    HOT_AREA areas;
    SMALL_RECT rcPop;
    COORD pos;
    WORD att;
    int iHot = 1;
    int i, maxlen, str_len,x;

    for (i=0, maxlen=0; i<n; i++)
    {
        str_len = strlen(pString[i]);
        if (maxlen < str_len)
        {
            maxlen = str_len;
        }
    }

    pos.X = maxlen + 6;
    pos.Y = n + 5;
    rcPop.Left = (SCR_COL - pos.X) / 2;
    rcPop.Right = rcPop.Left + pos.X - 1;
    rcPop.Top = (SCR_ROW - pos.Y) / 2;
    rcPop.Bottom = rcPop.Top + pos.Y - 1;

    att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
    labels.num = n;
    labels.ppLabel = pString;
    COORD aLoc[n];

    for (i=0; i<n; i++)
    {
        aLoc[i].X = rcPop.Left + 3;
        aLoc[i].Y = rcPop.Top + 2 + i;
    }

    str_len = strlen(pString[n-1]);
    aLoc[n-1].X = rcPop.Left + 3 + (maxlen-str_len)/2;
    aLoc[n-1].Y = aLoc[n-1].Y + 2;

    labels.pLoc = aLoc;

    areas.num = 4;
    SMALL_RECT aArea[] = {{aLoc[0].X, aLoc[0].Y,
                        aLoc[0].X + maxlen - 1, aLoc[0].Y},
                        {aLoc[1].X, aLoc[1].Y,
                        aLoc[1].X + maxlen - 1, aLoc[1].Y},
                        {aLoc[2].X, aLoc[2].Y,
                        aLoc[2].X + maxlen - 1, aLoc[2].Y},
                        {aLoc[3].X, aLoc[3].Y,
                        aLoc[3].X + 3, aLoc[3].Y}
                        };

    char aSort[] = {0, 0, 0, 0};
    char aTag[] = {1, 2, 3, 4};

    areas.pArea = aArea;
    areas.pSort = aSort;
    areas.pTag = aTag;
    PopUp(&rcPop, att, &labels, &areas);

    pos.X = rcPop.Left + 1;
    pos.Y = rcPop.Top + 2 +n;
    FillConsoleOutputCharacter(gh_std_out, '-', rcPop.Right-rcPop.Left-1, pos, &ul);
    x = DealInput(&areas, &iHot);
	PopOff();
    return x;
}

/********
�������ƣ�ShowModule5
�������ܣ�����ȷ�ϡ��͡�ȡ���������ַ����ı�ǩ�����ó��������ȴ��û�����
���������pStringΪָ�룬nΪ��ǩ����
�����������
�� �� ֵ������굥�������س���ո�ʱ���ص�ǰ�������
����˵������
********/
int ShowModule5(char **pString, int n)
{
    LABEL_BUNDLE labels;
    HOT_AREA areas;
    BOOL bRet = TRUE;
    SMALL_RECT rcPop;
    COORD pos;
    WORD att;
    int iHot = 1;
    int i, maxlen, str_len;

    for (i=0,maxlen=0; i<n; i++) {
        str_len = strlen(pString[i]);
        if (maxlen < str_len) {
            maxlen = str_len;
        }
    }

    pos.X = maxlen + 6;
    pos.Y = n + 5;
    rcPop.Left = (SCR_COL - pos.X) / 2;
    rcPop.Right = rcPop.Left + pos.X - 1;
    rcPop.Top = (SCR_ROW - pos.Y) / 2;
    rcPop.Bottom = rcPop.Top + pos.Y - 2;

    att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
    labels.num = n;
    labels.ppLabel = pString;
    COORD aLoc[n];

    for (i=0; i<n-2; i++) {
        aLoc[i].X = rcPop.Left + 3;
        aLoc[i].Y = rcPop.Top + 2 + i;
    }
    aLoc[1].X = rcPop.Left + 10;aLoc[1].Y = aLoc[0].Y + 3;
    aLoc[2].X = rcPop.Left + 20;aLoc[2].Y = aLoc[0].Y + 3;
    labels.pLoc = aLoc;

    areas.num = 2;
    SMALL_RECT aArea[] = {{aLoc[1].X, aLoc[1].Y,aLoc[1].X + 3, aLoc[1].Y},
                          {aLoc[2].X, aLoc[2].Y,aLoc[2].X + 3, aLoc[2].Y}
                         };

    char aSort[] = {0,0};
    char aTag[] = {1,2};

    areas.pArea = aArea;
    areas.pSort = aSort;
    areas.pTag = aTag;
    PopUp(&rcPop, att, &labels, &areas);

    pos.X = rcPop.Left + 1;
    pos.Y = rcPop.Top + 2 + n - 1;
    FillConsoleOutputCharacter(gh_std_out, '-', rcPop.Right-rcPop.Left-1, pos, &ul);

    int x=DealInput(&areas, &iHot);
    PopOff();
    return x;
}

int main()
{
    COORD size = {SCR_COL, SCR_ROW};                /*���ڻ�������С*/

    gh_std_out = GetStdHandle(STD_OUTPUT_HANDLE);   /* ��ȡ��׼����豸���*/
    gh_std_in = GetStdHandle(STD_INPUT_HANDLE);     /* ��ȡ��׼�����豸���*/

    SetConsoleTitle(gp_sys_name);                   /*���ô��ڱ���*/
    SetConsoleScreenBufferSize(gh_std_out, size);   /*���ô��ڻ�������С80*25*/

    LoadData();                                     /*���ݼ���*/
    InitInterface();                                /*�����ʼ��*/
    RunSys(&gp_head);                               /*ϵͳ����ģ���ѡ������*/
    CloseSys(gp_head);                              /*�˳�ϵͳ*/

    return 0;
}

/********
�������ƣ�LoadData
�������ܣ�������������ݴ������ļ����뵽�ڴ滺������ʮ��������
�����������
�����������
�� �� ֵ��BOOL���ͣ����Ƿ���TRUE
����˵������
********/
BOOL LoadData()
{
	int Re = 0;

	Re = CreatList(&gp_head);
	if (Re < (1 | 2 | 4 | 8))
	{
		printf("\nϵͳ�������ݲ�����!\n");
	}
    printf("\n�����������...\n");
    getchar();
	return TRUE;
}

/********
�������ƣ�CreatList
�������ܣ��������ļ���ȡ�������ݣ������ڵ���������ʮ��������
�����������
���������pheadΪ����ͷָ��ĵ�ַ������������������ʮ����
�� �� ֵ��int������ֵ����ʾ�����������
           0 ������������
           1 �Ѽ����߲�������Ϣ�����߲˻�����Ϣ���߲�Ӫ���ɷֺ��߲���ֲ��Ϣ
           3 �Ѽ����߲�������Ϣ���߲˻�����Ϣ�����߲�Ӫ���ɷֺ��߲���ֲ��Ϣ
           7 �Ѽ����߲�������Ϣ���߲˻�����Ϣ���߲�Ӫ���ɷ֣����߲���ֲ��Ϣ
           15 ����������ݶ��Ѽ���
����˵������
********/
int CreatList(T **phead)
{
	T *hd = NULL, *pType, tmp1;
	B *pBasic,tmp2;
    N *pNutri,tmp3;
	P *pPlant, tmp4;
	FILE *pFile;
	int find;
	int re = 0;

	if ((pFile = fopen(gp_ve_t_info_filename, "rb")) == NULL)
	{
		printf("�߲�������Ϣ�����ļ���ʧ��!\n");
		return re;
	}
	printf("�߲�������Ϣ�����ļ��򿪳ɹ�!\n");

	/*�������ļ��ж��߲�������Ϣ���ݣ������Ժ���ȳ���ʽ������������*/
	while (fread(&tmp1, sizeof(T), 1, pFile) == 1)
	{
		pType = (T *)malloc(sizeof(T));
		*pType = tmp1;
		pType->snext = NULL;
		pType->next = hd;
		hd = pType;
	}
	fclose(pFile);

	if (hd == NULL)
	{
		printf("�߲�������Ϣ�����ļ�����ʧ��!\n");
		return re;
	}
	printf("�߲�������Ϣ�����ļ����سɹ�!\n");
	*phead = hd;
	re += 1;

	if ((pFile = fopen(gp_ve_b_info_filename, "rb")) == NULL)
	{
		printf("�߲˻�����Ϣ�����ļ���ʧ��!\n");
		return re;
	}
	printf("�߲˻�����Ϣ�����ļ��򿪳ɹ�!\n");
	re += 2;

	/*�������ļ��ж�ȡ�߲˻�����Ϣ���ݣ�����������Ӧ�����߲˻�����Ϣ֧����*/
	while (fread(&tmp2, sizeof(B), 1, pFile) == 1)
	{
		/*������㣬��Ŵ������ļ��ж������߲˻�����Ϣ*/
		pBasic = (B *)malloc(sizeof(B));
		*pBasic = tmp2;
		pBasic->cnext = NULL;
		pBasic->snext=NULL;

		/*�������ϲ��Ҹ��߲������������������*/
		pType = hd;
		while (pType != NULL && (pType->type) != (pBasic->type))
		{
			pType = pType->next;
		}

		if (pType != NULL)                          /*����ҵ����򽫽���Ժ���ȳ���ʽ�����߲˻�����Ϣ֧��*/
		{
			pBasic->next = pType->snext;
			pType->snext = pBasic;
		}
		else                                        /*���δ�ҵ������ͷ������������ڴ�ռ�*/
		{
			free(pBasic);
		}
	}
	fclose(pFile);

	if ((pFile = fopen(gp_ve_b_nutri_info_filename, "rb")) == NULL)
	{
		printf("��ũ������Ϣ�е�Ӫ���ɷ���Ϣ�����ļ���ʧ��!\n");
		return re;
	}
	printf("��ũ������Ϣ�е�Ӫ���ɷ���Ϣ�����ļ��򿪳ɹ�!\n");
	re += 4;

	/*�������ļ��ж�ȡӪ���ɷ���Ϣ���ݣ������߲˻�����Ϣ֧����Ӧ����Ӫ���ɷ�֧����*/
	while (fread(&tmp3, sizeof(N), 1, pFile) == 1)
	{
		/*������㣬��Ŵ������ļ��ж�ȡ�Ĳ�ũ��ֲ��Ϣ*/
		pNutri = (N *)malloc(sizeof(N));
		*pNutri = tmp3;

		/*�����߲˻�����Ϣ֧���϶�Ӧ�߲˻�����Ϣ���*/
		pType = hd;
		find = 0;
		while (pType != NULL&&find == 0)
		{
		    if(pType->type==pNutri->type)
		    {
                pBasic = pType->snext;
                while (pBasic != NULL&&find == 0)
                {
                    if ((pBasic->num) == (pNutri->num))
                    {
                        find = 1;
                        break;
                    }
                    pBasic = pBasic->next;
                }
		    }
			pType = pType->next;
		}
		if (find)                                   /*����ҵ����򽫽��һ����ȳ���ʽ�����ũ��ֲ��Ϣ֧����*/
		{
			pNutri->next = pBasic->snext;
			pBasic->snext = pNutri;
		}
		else   free(pNutri);
	}
	fclose(pFile);

	if ((pFile = fopen(gp_ve_p_info_filename, "rb")) == NULL)
	{
		printf("��ũ��ֲ��Ϣ�����ļ���ʧ��!\n");
		return re;
	}
	printf("��ũ��ֲ��Ϣ�����ļ��򿪳ɹ�!\n");
	re += 8;

	/*�������ļ��ж�ȡ��ũ��ֲ��Ϣ���ݣ������߲˻�����Ϣ֧����Ӧ������ֲ֧����*/
	while (fread(&tmp4, sizeof(P), 1, pFile) == 1)
	{
		/*������㣬��Ŵ������ļ��ж�ȡ�Ĳ�ũ��ֲ��Ϣ*/
		pPlant = (P *)malloc(sizeof(P));
		*pPlant = tmp4;

		/*�����߲˻�����Ϣ֧���϶�Ӧ�߲˻�����Ϣ���*/
		pType = hd;
		find = 0;
		while (pType != NULL&&find == 0)
		{
		    if(pType->type==pPlant->type)
		    {
                pBasic = pType->snext;
                while (pBasic != NULL&&find == 0)
                {
                    if ((pBasic->num) == (pPlant->num))
                    {
                        find = 1;
                        break;
                    }
                    pBasic = pBasic->next;
                }
		    }
            pType = pType->next;
		}
		if (find)                                   /*����ҵ����򽫽��һ����ȳ���ʽ�����ũ��ֲ��Ϣ֧����*/
		{
			pPlant->next = pBasic->cnext;
			pBasic->cnext = pPlant;
		}
		else   free(pPlant);
	}
	fclose(pFile);

	return re;
}

/********
�������ƣ�CloseSys
�������ܣ��ر�ϵͳ
���������hdΪ����ͷָ��
�����������
�� �� ֵ��void���ͣ��޷���ֵ
����˵������
********/
void CloseSys(T *hd)
{
	T *pType1 = hd, *pType2;
	B *pBasic1, *pBasic2;
	P *pPlant1, *pPlant2;
	N *pNutri1,*pNutri2;

	while (pType1 != NULL)                          /*�ͷ�ʮ�ֽ�������Ķ�̬�洢��*/
	{
		pType2 = pType1->next;
		pBasic1 = pType1->snext;
		while (pBasic1 != NULL)                     /*�ͷ��߲˻�����Ϣ֧���Ķ�̬�洢��*/
		{
			pBasic2 = pBasic1->next;

			pNutri1=pBasic1->snext;
			while(pNutri1!=NULL)
			{
			    pNutri2=pNutri1->next;
			    free(pNutri1);
			    pNutri1=pNutri2;
			}

			pPlant1 = pBasic1->cnext;
			while (pPlant1 != NULL)                 /*�ͷŲ�ũ��ֲ��Ϣ֧���Ķ�̬�洢��*/
			{
				pPlant2 = pPlant1->next;
				free(pPlant1);
				pPlant1 = pPlant2;
			}
			free(pBasic1);
			pBasic1 = pBasic2;
		}
		free(pType1);                               /*�ͷ��������Ķ�̬�洢��*/
		pType1 = pType2;
	}
	ClearScreen();                                  /*����*/
	free(gp_buff_menubar_info);                     /*�ͷŴ�Ų˵�����Ϣ��̬�洢��*/
	CloseHandle(gh_std_out);                        /*�رձ�׼�����豸���*/
	CloseHandle(gh_std_in);                         /*�رձ�׼����豸���*/
	SetConsoleTitle("���н���");                    /*�����ڱ�������Ϊ���н���*/
	return;
}

/********
�������ƣ�PopMenu
�������ܣ�����ָ�����˵����Ӧ���Ӳ˵�
���������numΪָ�������˵����
�����������
�� �� ֵ��void���ͣ��޷���ֵ
����˵������
********/
void PopMenu(int num)
{
    LABEL_BUNDLE labels;
    HOT_AREA areas;
    SMALL_RECT rcPop;
    COORD pos;
    WORD att;
    char *pCh;
    int i, j, loc = 0;

    if (num != gi_sel_menu)                         /*���ָ�����˵�������ѡ�в˵�*/
    {
        if (gp_top_layer->LayerNo != 0)             /*�����ǰ�����Ӳ˵�����*/
        {
            PopOff();
            gi_sel_sub_menu = 0;
        }
    }
    else if (gp_top_layer->LayerNo != 0)            /*���ѵ������Ӳ˵����򷵻�*/
    {
        return;
    }

    gi_sel_menu = num;                              /*��ѡ�����˵�����Ϊָ�������˵���*/
    TagMainMenu(gi_sel_menu);                       /*��ѡ�е����˵����������*/
    LocSubMenu(gi_sel_menu, &rcPop);                /*���㵯���Ӳ˵�������λ��, �����rcPop��*/

    /*������Ӳ˵��еĵ�һ�����Ӳ˵��ַ��������е�λ��(�±�)*/
    for (i=1; i<gi_sel_menu; i++)
    {
        loc += ga_sub_menu_count[i-1];
    }
    /*�������Ӳ˵������������ǩ���ṹ����*/
    labels.ppLabel = ga_sub_menu + loc;             /*��ǩ����һ����ǩ�ַ����ĵ�ַ*/
    labels.num = ga_sub_menu_count[gi_sel_menu-1];  /*��ǩ���б�ǩ�ַ����ĸ���*/
    COORD aLoc[labels.num];                         /*����һ���������飬���ÿ����ǩ�ַ������λ�õ�����*/
    for (i=0; i<labels.num; i++)                    /*ȷ����ǩ�ַ��������λ�ã����������������*/
    {
        aLoc[i].X = rcPop.Left + 2;
        aLoc[i].Y = rcPop.Top + i + 1;
    }
    labels.pLoc = aLoc;                             /*ʹ��ǩ���ṹ����labels�ĳ�ԱpLocָ�������������Ԫ��*/
    /*����������Ϣ*/
    areas.num = labels.num;                         /*�����ĸ��������ڱ�ǩ�ĸ��������Ӳ˵�������*/
    SMALL_RECT aArea[areas.num];                    /*������������������λ��*/
    char aSort[areas.num];                          /*��������������������Ӧ���*/
    char aTag[areas.num];                           /*����������ÿ�������ı��*/
    for (i=0; i<areas.num; i++)
    {
        aArea[i].Left = rcPop.Left + 2;             /*������λ*/
        aArea[i].Top = rcPop.Top + i + 1;
        aArea[i].Right = rcPop.Right - 2;
        aArea[i].Bottom = aArea[i].Top;
        aSort[i] = 0;                               /*�������Ϊ0(��ť��)*/
        aTag[i] = i + 1;                            /*������˳����*/
    }
    areas.pArea = aArea;                            /*ʹ�����ṹ����areas�ĳ�ԱpAreaָ������λ��������Ԫ��*/
    areas.pSort = aSort;                            /*ʹ�����ṹ����areas�ĳ�ԱpSortָ���������������Ԫ��*/
    areas.pTag = aTag;                              /*ʹ�����ṹ����areas�ĳ�ԱpTagָ���������������Ԫ��*/

    att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
    PopUp(&rcPop, att, &labels, &areas);
    DrawBox(&rcPop);                                /*���������ڻ��߿�*/
    pos.X = rcPop.Left + 2;
    for (pos.Y=rcPop.Top+1; pos.Y<rcPop.Bottom; pos.Y++)
    {                                               /*��ѭ�������ڿմ��Ӳ���λ�û����γɷָ�����ȡ���˲˵������������*/
        pCh = ga_sub_menu[loc+pos.Y-rcPop.Top-1];
        if (strlen(pCh)==0)                         /*����Ϊ0������Ϊ�մ�*/
        {                                           /*���Ȼ�����*/
            FillConsoleOutputCharacter(gh_std_out, '-', rcPop.Right-rcPop.Left-3, pos, &ul);
            for (j=rcPop.Left+2; j<rcPop.Right-1; j++)
            {                                       /*ȡ���������ַ���Ԫ����������*/
                gp_scr_att[pos.Y*SCR_COL+j] &= 3;   /*��λ��Ľ�������˵���λ*/
            }
        }

    }
    /*���Ӳ˵���Ĺ��ܼ���Ϊ�׵׺���*/
    pos.X = rcPop.Left + 3;
    att =  FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;
    for (pos.Y=rcPop.Top+1; pos.Y<rcPop.Bottom; pos.Y++)
    {
        if (strlen(ga_sub_menu[loc+pos.Y-rcPop.Top-1])==0)
        {
            continue;                               /*�����մ�*/
        }
        FillConsoleOutputAttribute(gh_std_out, att, 1, pos, &ul);
    }
    return;
}

/********
�������ƣ�PopUp
�������ܣ���ָ���������뵯��������Ϣ������������������������Ϣλ����ջ
���������pRcΪ��������λ�����ݴ�ŵĵ�ַ
           attΪ�������������ַ�����
           pLabelΪ���������б�ǩ����Ϣ��ŵĵ�ַ
           pHotAreaΪ����������������Ϣ��ŵĵ�ַ
�����������
�� �� ֵ��void���ͣ��޷���ֵ
����˵������
********/
void PopUp(SMALL_RECT *pRc, WORD att, LABEL_BUNDLE *pLabel, HOT_AREA *pHotArea)
{
    LAYER_NODE *nextLayer;
    COORD size;
    COORD pos = {0, 0};
    char *pCh;
    int i, j, row;

    /*������������λ���ַ���Ԫ��Ϣ��ջ*/
    size.X = pRc->Right - pRc->Left + 1;            /*�������ڵĿ��*/
    size.Y = pRc->Bottom - pRc->Top + 1;            /*�������ڵĸ߶�*/
    /*�����ŵ������������Ϣ�Ķ�̬�洢��*/
    nextLayer = (LAYER_NODE *)malloc(sizeof(LAYER_NODE));
    nextLayer->next = gp_top_layer;
    nextLayer->LayerNo = gp_top_layer->LayerNo + 1;
    nextLayer->rcArea = *pRc;
    nextLayer->pContent = (CHAR_INFO *)malloc(size.X*size.Y*sizeof(CHAR_INFO));
    nextLayer->pScrAtt = (char *)malloc(size.X*size.Y*sizeof(char));
    pCh = nextLayer->pScrAtt;
    /*���������ڸ���������ַ���Ϣ���棬�����ڹرյ�������ʱ�ָ�ԭ��*/
    ReadConsoleOutput(gh_std_out, nextLayer->pContent, size, pos, pRc);
    for (i=pRc->Top; i<=pRc->Bottom; i++)
    {                                               /*�˶���ѭ�����������ַ���Ԫ��ԭ������ֵ���붯̬�洢���������Ժ�ָ�*/
        for (j=pRc->Left; j<=pRc->Right; j++)
        {
            *pCh = gp_scr_att[i*SCR_COL+j];
            pCh++;
        }
    }
    gp_top_layer = nextLayer;                       /*��ɵ������������Ϣ��ջ����*/
    /*���õ������������ַ���������*/
    pos.X = pRc->Left;
    pos.Y = pRc->Top;
    for (i=pRc->Top; i<=pRc->Bottom; i++)
    {
        FillConsoleOutputAttribute(gh_std_out, att, size.X, pos, &ul);
        pos.Y++;
    }
    /*����ǩ���еı�ǩ�ַ������趨��λ�����*/
    for (i=0; i<pLabel->num; i++)
    {
        pCh = pLabel->ppLabel[i];
        if (strlen(pCh) != 0)
        {
            WriteConsoleOutputCharacter(gh_std_out, pCh, strlen(pCh),
                                        pLabel->pLoc[i], &ul);
        }
    }
    /*���õ������������ַ���Ԫ��������*/
    for (i=pRc->Top; i<=pRc->Bottom; i++)
    {                                               /*�˶���ѭ�������ַ���Ԫ�Ĳ��*/
        for (j=pRc->Left; j<=pRc->Right; j++)
        {
            gp_scr_att[i*SCR_COL+j] = gp_top_layer->LayerNo;
        }
    }

    for (i=0; i<pHotArea->num; i++)
    {                                               /*�˶���ѭ�����������������ַ���Ԫ���������ͺ��������*/
        row = pHotArea->pArea[i].Top;
        for (j=pHotArea->pArea[i].Left; j<=pHotArea->pArea[i].Right; j++)
        {
            gp_scr_att[row*SCR_COL+j] |= (pHotArea->pSort[i] << 6)
                                    | (pHotArea->pTag[i] << 2);
        }
    }
    return;
}

/********
�������ƣ�PopOff
�������ܣ��رն��㵯�����ڣ��ָ���������ԭ��ۺ��ַ���Ԫԭ����
�����������
�����������
�� �� ֵ��void���ͣ��޷���ֵ
����˵������
********/
void PopOff(void)
{
    LAYER_NODE *nextLayer;
    COORD size;
    COORD pos = {0, 0};
    char *pCh;
    int i, j;

    if ((gp_top_layer->next==NULL) || (gp_top_layer->pContent==NULL))
    {   /*ջ�״�ŵ���������Ļ��Ϣ�����ùر�*/
        return;
    }
    nextLayer = gp_top_layer->next;
    /*�ָ�������������ԭ���*/
    size.X = gp_top_layer->rcArea.Right - gp_top_layer->rcArea.Left + 1;
    size.Y = gp_top_layer->rcArea.Bottom - gp_top_layer->rcArea.Top + 1;
    WriteConsoleOutput(gh_std_out, gp_top_layer->pContent, size, pos, &(gp_top_layer->rcArea));
    /*�ָ��ַ���Ԫԭ����*/
    pCh = gp_top_layer->pScrAtt;
    for (i=gp_top_layer->rcArea.Top; i<=gp_top_layer->rcArea.Bottom; i++)
    {
        for (j=gp_top_layer->rcArea.Left; j<=gp_top_layer->rcArea.Right; j++)
        {
            gp_scr_att[i*SCR_COL+j] = *pCh;
            pCh++;
        }
    }
    free(gp_top_layer->pContent);    /*�ͷŶ�̬�洢��*/
    free(gp_top_layer->pScrAtt);
    free(gp_top_layer);
    gp_top_layer = nextLayer;
    gi_sel_sub_menu = 0;
    return;
}

/********
�������ƣ�DrawBox
�������ܣ��Ӳ˵���ʱ����ָ�����򻭱߿�
���������pRcΪ�������λ����Ϣ�ĵ�ַ
�����������
�� �� ֵ��void���ͣ��޷���ֵ
����˵������
********/
void DrawBox(SMALL_RECT *pRc)
{
    char chBox[] = {'+','-'};                       /*�����õ��ַ�*/
    COORD pos = {pRc->Left, pRc->Top};              /*��λ����������Ͻ�*/

    WriteConsoleOutputCharacter(gh_std_out, &chBox[0], 1, pos, &ul);/*���߿����Ͻ�*/
    for (pos.X = pRc->Left + 1; pos.X < pRc->Right; pos.X++)
    {                                               /*��ѭ�����ϱ߿����*/
        WriteConsoleOutputCharacter(gh_std_out, &chBox[1], 1, pos, &ul);
    }
    pos.X = pRc->Right;
    WriteConsoleOutputCharacter(gh_std_out, &chBox[0], 1, pos, &ul);/*���߿����Ͻ�*/
    pos.X = pRc->Left;
    pos.Y = pRc->Bottom;
    WriteConsoleOutputCharacter(gh_std_out, &chBox[0], 1, pos, &ul);/*���߿����½�*/
    for (pos.X = pRc->Left + 1; pos.X < pRc->Right; pos.X++)
    {                                               /*��ѭ�����±߿����*/
        WriteConsoleOutputCharacter(gh_std_out, &chBox[1], 1, pos, &ul);
    }
    pos.X = pRc->Right;
    WriteConsoleOutputCharacter(gh_std_out, &chBox[0], 1, pos, &ul);/*���߿����½�*/
    return;
}

/********
�������ƣ�TagSubMenu
�������ܣ����ƶ��Ӳ˵�������ѡ�б��
���������numΪѡ�е��Ӳ˵����
�����������
�� �� ֵ��void���ͣ��޷���ֵ
����˵������
********/
void TagSubMenu(int num)
{
    SMALL_RECT rcPop;
    COORD pos;
    WORD att;
    int width;

    LocSubMenu(gi_sel_menu, &rcPop);                /*���㵯���Ӳ˵�������λ��, �����rcPop��*/
    if ((num<1) || (num == gi_sel_sub_menu) || (num>rcPop.Bottom-rcPop.Top-1))
    {                                               /*����Ӳ˵����Խ�磬������Ӳ˵��ѱ�ѡ�У��򷵻�*/
        return;
    }

    pos.X = rcPop.Left + 2;
    width = rcPop.Right - rcPop.Left - 3;
    if (gi_sel_sub_menu != 0)                       /*����ȡ��ԭѡ���Ӳ˵����ϵı��*/
    {
        pos.Y = rcPop.Top + gi_sel_sub_menu;
        att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
        FillConsoleOutputAttribute(gh_std_out, att, width, pos, &ul);
        pos.X += 1;
        att |=  FOREGROUND_RED;                     /*�׵׺���*/
        FillConsoleOutputAttribute(gh_std_out, att, 1, pos, &ul);
    }
    /*���ƶ��Ӳ˵�������ѡ�б��*/
    pos.X = rcPop.Left + 2;
    pos.Y = rcPop.Top + num;
    att = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;  /*�ڵװ���*/
    FillConsoleOutputAttribute(gh_std_out, att, width, pos, &ul);
    gi_sel_sub_menu = num;                          /*�޸�ѡ���Ӳ˵����*/
    return;
}

/********
�������ƣ�LocSubMenu
�������ܣ����㵯���Ӳ˵��������ϽǺ����½ǵ�λ��
���������numѡ�е����˵����
���������rc�������λ����Ϣ�ĵ�ַ
�� �� ֵ��void���ͣ��޷���ֵ
����˵������
********/
void LocSubMenu(int num, SMALL_RECT *rc)
{
    int i, len, loc = 0;

    rc->Top = 1;                                    /*������ϱ߶��ڵ�2�У��к�Ϊ1*/
    rc->Left = 1;
    for (i=1; i<num; i++)
    {                                               /*����������߽�λ��, ͬʱ�����һ���Ӳ˵������Ӳ˵��ַ��������е�λ��*/
        rc->Left += strlen(ga_main_menu[i-1]) + 4;
        loc += ga_sub_menu_count[i-1];
    }
    rc->Right = strlen(ga_sub_menu[loc]);           /*��ʱ��ŵ�һ���Ӳ˵����ַ�������*/
    for (i=1; i<ga_sub_menu_count[num-1]; i++)
    {                                               /*������Ӳ˵��ַ��������䳤�ȴ����rc->Right*/
        len = strlen(ga_sub_menu[loc+i]);
        if (rc->Right < len)
        {
            rc->Right = len;
        }
    }
    rc->Right += rc->Left + 3;                      /*����������ұ߽�*/
    rc->Bottom = rc->Top + ga_sub_menu_count[num-1] + 1;/*���������±ߵ��к�*/
    if (rc->Right >= SCR_COL)                       /*�ұ߽�Խ��Ĵ���*/
    {
        len = rc->Right - SCR_COL + 1;
        rc->Left -= len;
        rc->Right = SCR_COL - 1;
    }
    return;
}

/********
�������ƣ�DealInput
�������ܣ��ڵ�������������������, �ȴ�����Ӧ�û�����
���������pHotAreaΪ������Χ
           piHot ����������ŵĴ�ŵ�ַ, ��ָ�򽹵�������ŵ�ָ��
���������piHot ����굥�������س���ո�ʱ���ص�ǰ�������
�� �� ֵ����
����˵������
********/
int DealInput(HOT_AREA *pHotArea, int *piHot)
{
    INPUT_RECORD inRec;
    CONSOLE_CURSOR_INFO lpCur;
    DWORD res;
    COORD pos = {0, 0};
    int num, arrow, iRet = 0;
    int cNo, cTag, cSort;                           /*cNoΪ���, cTagΪ�������, cSortΪ��������*/
    char vkc, asc;                                  /*vkcΪ���������, ascΪ�ַ���ASCII��ֵ*/

    SetHotPoint(pHotArea, *piHot);
    while (TRUE)
    {    /*ѭ��*/
        ReadConsoleInput(gh_std_in, &inRec, 1, &res);
        if ((inRec.EventType == MOUSE_EVENT) &&
            (inRec.Event.MouseEvent.dwButtonState
             == FROM_LEFT_1ST_BUTTON_PRESSED))
        {
            pos = inRec.Event.MouseEvent.dwMousePosition;
            cNo = gp_scr_att[pos.Y * SCR_COL + pos.X] & 3;
            cTag = (gp_scr_att[pos.Y * SCR_COL + pos.X] >> 2) & 15;
            cSort = (gp_scr_att[pos.Y * SCR_COL + pos.X] >> 6) & 3;

            if ((cNo == gp_top_layer->LayerNo) && cTag > 0)
            {
                *piHot = cTag;
                SetHotPoint(pHotArea, *piHot);
                if (cSort == 0)
                {
                    iRet = cTag;
                    return iRet;
                }
                else if(cTag == 0)
                {                                   /*������ڷ��ȵ�����*/
                    GetConsoleCursorInfo(gh_std_out, &lpCur);
                    lpCur.bVisible = FALSE;
                    SetConsoleCursorInfo(gh_std_out, &lpCur);    /*���ع��*/
                }
            }
        }
        else if (inRec.EventType == KEY_EVENT && inRec.Event.KeyEvent.bKeyDown)
        {
            vkc = inRec.Event.KeyEvent.wVirtualKeyCode;

            switch(vkc)
            {

            case 37 :                               /*�����ϡ����*/
            case 38 :
                -- *piHot;
                if(*piHot < 1)
                {
                    *piHot = pHotArea->num;
                }
                SetHotPoint(pHotArea, *piHot);
                GetConsoleCursorInfo(gh_std_out, &lpCur);
                break;
            case 13 :                               /*�س�����ո��ʾ���µ�ǰ��ť*/
            case 32 :
                if(pHotArea->pSort[*piHot-1] == 0)
                {                                   /*��Ϊ��ť*/
                    GetConsoleCursorInfo(gh_std_out, &lpCur);
                    lpCur.bVisible = FALSE;
                    SetConsoleCursorInfo(gh_std_out, &lpCur);    /*���ع��*/
                    iRet = *piHot;
                    return iRet;
                }
            case 39 :                               /*�����ҡ��¼�*/
            case 40 :
                ++ *piHot;
                if(*piHot > pHotArea->num)
                {
                    *piHot = 1;
                }
                SetHotPoint(pHotArea, *piHot);
                GetConsoleCursorInfo(gh_std_out, &lpCur);
                break;
            case 27 :                               /*��ESC��*/
                GetConsoleCursorInfo(gh_std_out, &lpCur);
                lpCur.bVisible = FALSE;
                SetConsoleCursorInfo(gh_std_out, &lpCur);       /*���ع��*/
                iRet = 27;
                return iRet;
            }
        }
    }
    return iRet;
}

/********
�������ƣ�SetHotPoint
�������ܣ���������
���������pHotAreaΪ������Χ
           iHotΪ�����������
�����������
�� �� ֵ��void���ͣ��޷���ֵ
����˵������
********/
void SetHotPoint(HOT_AREA *pHotArea, int iHot)
{
    CONSOLE_CURSOR_INFO lpCur;
    COORD pos = {0, 0};
    WORD att1, att2;
    int i, width;

    att1 = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;  /*�ڵװ���*/
    att2 = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
    for (i=0; i<pHotArea->num; i++)
    {                                               /*����ť��������Ϊ�׵׺���*/
        pos.X = pHotArea->pArea[i].Left;
        pos.Y = pHotArea->pArea[i].Top;
        width = pHotArea->pArea[i].Right - pHotArea->pArea[i].Left + 1;
        if (pHotArea->pSort[i] == 0)
        {                                           /*�����ǰ�ť��*/
            FillConsoleOutputAttribute(gh_std_out, att2, width, pos, &ul);
        }
    }

    pos.X = pHotArea->pArea[iHot-1].Left;
    pos.Y = pHotArea->pArea[iHot-1].Top;
    width = pHotArea->pArea[iHot-1].Right - pHotArea->pArea[iHot-1].Left + 1;
    if (pHotArea->pSort[iHot-1] == 0)
    {                                               /*�����������ǰ�ť��*/
        FillConsoleOutputAttribute(gh_std_out, att1, width, pos, &ul);
    }
    else if (pHotArea->pSort[iHot-1] == 1)
    {                                               /*�������������ı�����*/
        SetConsoleCursorPosition(gh_std_out, pos);
        GetConsoleCursorInfo(gh_std_out, &lpCur);
        lpCur.bVisible = TRUE;
        SetConsoleCursorInfo(gh_std_out, &lpCur);
    }
}

/********
�������ƣ�RunSys
�������ܣ�����ϵͳ����ϵͳ�������������û���ѡ��Ĺ���ģ��
�����������
���������pheadΪ����ͷָ��ĵ�ַ
�� �� ֵ��void���ͣ��޷���ֵ
����˵������
********/
void RunSys(T **phead)
{
    INPUT_RECORD inRec;
    DWORD res;
    COORD pos = {0, 0};
    BOOL bRet = TRUE;
    int i, loc, num;
    int cNo, cAtt;                                  /*cNoΪ�ַ���Ԫ���, cAttΪ�ַ���Ԫ����*/
    char vkc, asc;                                  /*vkcΪ���������, ascΪ�ַ���ASCII��ֵ*/

    while (bRet)
    {
        /*�ӿ���̨���뻺�����ж�һ����¼*/
        ReadConsoleInput(gh_std_in, &inRec, 1, &res);

        if (inRec.EventType == MOUSE_EVENT)         /*�����¼������¼�����*/
        {
            pos = inRec.Event.MouseEvent.dwMousePosition;  /*��ȡ�������λ��*/
            cNo = gp_scr_att[pos.Y * SCR_COL + pos.X] & 3; /*ȡ��λ�õĲ��*/
            cAtt = gp_scr_att[pos.Y * SCR_COL + pos.X] >> 2;/*ȡ���ַ���Ԫ����*/
            if (cNo == 0)                           /*���Ϊ0��������λ��δ�������Ӳ˵�����*/
            {
                /*cAtt > 0 ������λ�ô�������(���˵����ַ���Ԫ)
                  cAtt != gi_sel_menu ������λ�õ����˵���δ��ѡ��
                  gp_top_layer->LayerNo > 0 ������ǰ���Ӳ˵�����*/
                if (cAtt > 0 && cAtt != gi_sel_menu && gp_top_layer->LayerNo > 0)
                {
                    PopOff();                       /*�رյ������Ӳ˵�*/
                    gi_sel_sub_menu = 0;            /*��ѡ���Ӳ˵���������Ϊ0*/
                    PopMenu(cAtt);                  /*��������������˵����Ӧ���Ӳ˵�*/
                }
            }
            else if (cAtt > 0)                      /*�������λ��Ϊ�����Ӳ˵��Ĳ˵����ַ���Ԫ*/
            {
                TagSubMenu(cAtt);                   /*�ڸ��Ӳ˵�������ѡ�б��*/
            }

            if (inRec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)/*������������ߵ�һ��*/
            {
                if (cNo == 0)                       /*���Ϊ0��������λ��δ�������Ӳ˵�����*/
                {
                    if (cAtt > 0)                   /*�����λ�ô�������(���˵����ַ���Ԫ)*/
                    {
                        PopMenu(cAtt);              /*��������������˵����Ӧ���Ӳ˵�*/
                    }
                    /*�����λ�ò��������˵����ַ���Ԫ�������Ӳ˵�����*/
                    else if (gp_top_layer->LayerNo > 0)
                    {
                        PopOff();                   /*�رյ������Ӳ˵�*/
                        gi_sel_sub_menu = 0;        /*��ѡ���Ӳ˵���������Ϊ0*/
                    }
                }
                else                                /*��Ų�Ϊ0��������λ�ñ������Ӳ˵�����*/
                {
                    if (cAtt > 0)                   /*�����λ�ô�������(�Ӳ˵����ַ���Ԫ)*/
                    {
                        PopOff();                   /*�رյ������Ӳ˵�*/
                        gi_sel_sub_menu = 0;        /*��ѡ���Ӳ˵���������Ϊ0*/

                        /*ִ�ж�Ӧ���ܺ���:gi_sel_menu���˵����,cAtt�Ӳ˵����*/
                        bRet = ExeFunction(gi_sel_menu, cAtt);
                    }
                }
            }
            else if (inRec.Event.MouseEvent.dwButtonState
                     == RIGHTMOST_BUTTON_PRESSED)   /*�����������Ҽ�*/
            {
                if (cNo == 0)                       /*���Ϊ0��������λ��δ�������Ӳ˵�����*/
                {
                    PopOff();                       /*�رյ������Ӳ˵�*/
                    gi_sel_sub_menu = 0;            /*��ѡ���Ӳ˵���������Ϊ0*/
                }
            }
        }
        else if (inRec.EventType == KEY_EVENT       /*�����¼�ɰ�������*/
                 && inRec.Event.KeyEvent.bKeyDown)  /*�Ҽ�������*/
        {
            vkc = inRec.Event.KeyEvent.wVirtualKeyCode;/*��ȡ�������������*/
            asc = inRec.Event.KeyEvent.uChar.AsciiChar;/*��ȡ������ASC��*/

            /*ϵͳ��ݼ��Ĵ���*/
            if (vkc == 112)                         /*�������F1��*/
            {
                if (gp_top_layer->LayerNo != 0)     /*�����ǰ���Ӳ˵�����*/
                {
                    PopOff();                       /*�رյ������Ӳ˵�*/
                    gi_sel_sub_menu = 0;            /*��ѡ���Ӳ˵���������Ϊ0*/
                }
                bRet = ExeFunction(5, 1);           /*���а������⹦�ܺ���*/
            }
            else if (inRec.Event.KeyEvent.dwControlKeyState
                     & (LEFT_ALT_PRESSED | RIGHT_ALT_PRESSED))
            {                                       /*������������Alt��*/
                switch (vkc)                        /*�ж���ϼ�Alt+��ĸ*/
                {
                    case 88:                        /*Alt+X �˳�*/
                        if (gp_top_layer->LayerNo != 0)
                        {
                            PopOff();
                            gi_sel_sub_menu = 0;
                        }
                        bRet = ExeFunction(1,4);
                        break;
                    case 70:                        /*Alt+F*/
                        PopMenu(1);
                        break;
                    case 77:                        /*Alt+M*/
                        PopMenu(2);
                        break;
                    case 81:                        /*Alt+Q*/
                        PopMenu(3);
                        break;
                    case 83:                        /*Alt+S*/
                        PopMenu(4);
                        break;
                    case 72:                        /*Alt+H*/
                        PopMenu(5);
                        break;
                }
            }
            else if (asc == 0)                      /*�������Ƽ��Ĵ���*/
            {
                if (gp_top_layer->LayerNo == 0)     /*���δ�����Ӳ˵�*/
                {
                    switch (vkc)                    /*�������(���ҡ���)������Ӧ�������Ƽ�*/
                    {
                        case 37:
                            gi_sel_menu--;
                            if (gi_sel_menu == 0)
                            {
                                gi_sel_menu = 5;
                            }
                            TagMainMenu(gi_sel_menu);
                            break;
                        case 39:
                            gi_sel_menu++;
                            if (gi_sel_menu == 6)
                            {
                                gi_sel_menu = 1;
                            }
                            TagMainMenu(gi_sel_menu);
                            break;
                        case 40:
                            PopMenu(gi_sel_menu);
                            TagSubMenu(1);
                            break;
                    }
                }
                else                                /*�ѵ����Ӳ˵�ʱ*/
                {
                    for (loc=0,i=1; i<gi_sel_menu; i++)
                    {
                        loc += ga_sub_menu_count[i-1];
                    }                               /*������Ӳ˵��еĵ�һ�����Ӳ˵��ַ��������е�λ��(�±�)*/
                    switch (vkc)                    /*�����(���ҡ��ϡ���)�Ĵ���*/
                    {
                        case 37:
                            gi_sel_menu--;
                            if (gi_sel_menu < 1)
                            {
                                gi_sel_menu = 5;
                            }
                            TagMainMenu(gi_sel_menu);
                            PopOff();
                            PopMenu(gi_sel_menu);
                            TagSubMenu(1);
                            break;
                        case 38:
                            num = gi_sel_sub_menu - 1;
                            if (num < 1)
                            {
                                num = ga_sub_menu_count[gi_sel_menu-1];
                            }
                            if (strlen(ga_sub_menu[loc+num-1]) == 0)
                            {
                                num--;
                            }
                            TagSubMenu(num);
                            break;
                        case 39:
                            gi_sel_menu++;
                            if (gi_sel_menu > 5)
                            {
                                gi_sel_menu = 1;
                            }
                            TagMainMenu(gi_sel_menu);
                            PopOff();
                            PopMenu(gi_sel_menu);
                            TagSubMenu(1);
                            break;
                        case 40:
                            num = gi_sel_sub_menu + 1;
                            if (num > ga_sub_menu_count[gi_sel_menu-1])
                            {
                                num = 1;
                            }
                            if (strlen(ga_sub_menu[loc+num-1]) == 0)
                            {
                                num++;
                            }
                            TagSubMenu(num);
                            break;
                    }
                }
            }
            else if ((asc-vkc == 0) || (asc-vkc == 32)){  /*������ͨ��*/
                if (gp_top_layer->LayerNo == 0)     /*���δ�����Ӳ˵�*/
                {
                    switch (vkc)
                    {
                        case 70:                    /*f��F*/
                            PopMenu(1);
                            break;
                        case 77:                    /*m��M*/
                            PopMenu(2);
                            break;
                        case 81:                    /*q��Q*/
                            PopMenu(3);
                            break;
                        case 83:                    /*s��S*/
                            PopMenu(4);
                            break;
                        case 72:                    /*h��H*/
                            PopMenu(5);
                            break;
                        case 13:                    /*�س�*/
                            PopMenu(gi_sel_menu);
                            TagSubMenu(1);
                            break;
                    }
                }
                else                                /*�ѵ����Ӳ˵�ʱ�ļ������봦��*/
                {
                    if (vkc == 27)                  /*�������ESC��*/
                    {
                        PopOff();
                        gi_sel_sub_menu = 0;
                    }
                    else if(vkc == 13)              /*������»س���*/
                    {
                        num = gi_sel_sub_menu;
                        PopOff();
                        gi_sel_sub_menu = 0;
                        bRet = ExeFunction(gi_sel_menu, num);
                    }
                    else                            /*������ͨ���Ĵ���*/
                    {
                        /*������Ӳ˵��еĵ�һ�����Ӳ˵��ַ��������е�λ��(�±�)*/
                        for (loc=0,i=1; i<gi_sel_menu; i++)
                        {
                            loc += ga_sub_menu_count[i-1];
                        }

                        /*�����뵱ǰ�Ӳ˵���ÿһ��Ĵ����ַ����бȽ�*/
                        for (i=loc; i<loc+ga_sub_menu_count[gi_sel_menu-1]; i++)
                        {
                            if (strlen(ga_sub_menu[i])>0 && vkc==ga_sub_menu[i][1])
                            {                       /*���ƥ��ɹ�*/
                                PopOff();
                                gi_sel_sub_menu = 0;
                                bRet = ExeFunction(gi_sel_menu, i-loc+1);
                            }
                        }
                    }
                }
            }
        }
    }
}

/********
�������ƣ�InitInterface
�������ܣ���ʼ������
�����������
�����������
�� �� ֵ��void���ͣ��޷���ֵ
����˵������
********/
void InitInterface()
{
    WORD att = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY ;

    SetConsoleTextAttribute(gh_std_out, att);       /*���ÿ���̨��Ļ�������ַ�����*/

    ClearScreen();                                  /* ����*/

    /*��������������Ϣ��ջ������ʼ�������Ļ���ڵ�����һ�㵯������*/
    gp_scr_att = (char *)calloc(SCR_COL * SCR_ROW, sizeof(char));/*��Ļ�ַ�����*/
    gp_top_layer = (LAYER_NODE *)malloc(sizeof(LAYER_NODE));
    gp_top_layer->LayerNo = 0;                      /*�������ڵĲ��Ϊ0*/
    gp_top_layer->rcArea.Left = 0;                  /*�������ڵ�����Ϊ������Ļ����*/
    gp_top_layer->rcArea.Top = 0;
    gp_top_layer->rcArea.Right = SCR_COL - 1;
    gp_top_layer->rcArea.Bottom = SCR_ROW - 1;
    gp_top_layer->pContent = NULL;
    gp_top_layer->pScrAtt = gp_scr_att;
    gp_top_layer->next = NULL;

    ShowMenu();                                     /*��ʾ�˵���*/
    return;
}

/********
�������ƣ�ClearScreen
�������ܣ�����
�����������
�����������
�� �� ֵ��void���ͣ��޷���ֵ
����˵������
********/
void ClearScreen(void)
{
    CONSOLE_SCREEN_BUFFER_INFO bInfo;
    COORD home = {0, 0};
    unsigned long size;

    GetConsoleScreenBufferInfo( gh_std_out, &bInfo );/*ȡ��Ļ��������Ϣ*/
    size =  bInfo.dwSize.X * bInfo.dwSize.Y;        /*������Ļ�������ַ���Ԫ��*/

    /*����Ļ���������е�Ԫ���ַ���������Ϊ��ǰ��Ļ�������ַ�����*/
    FillConsoleOutputAttribute(gh_std_out, bInfo.wAttributes, size, home, &ul);

    /*����Ļ���������е�Ԫ���Ϊ�ո��ַ�*/
    FillConsoleOutputCharacter(gh_std_out, ' ', size, home, &ul);
    return;
}

/********
�������ƣ�ShowMenu
�������ܣ�����Ļ����ʾ���˵��������������������˵���һ������ѡ�б��
�����������
���������void���ͣ��޷���ֵ
�� �� ֵ����
����˵������
********/
void ShowMenu()
{
    CONSOLE_SCREEN_BUFFER_INFO bInfo;
    CONSOLE_CURSOR_INFO lpCur;
    COORD size;
    COORD pos = {0, 0};
    int i, j;
    int PosA = 2, PosB;
    char ch;

    GetConsoleScreenBufferInfo( gh_std_out, &bInfo );
    size.X = bInfo.dwSize.X;
    size.Y = 1;
    SetConsoleCursorPosition(gh_std_out, pos);
    for (i=0; i < 5; i++)                           /*�ڴ��ڵ�һ�е�һ�д�������˵���*/
    {
        printf("  %s  ", ga_main_menu[i]);
    }

    GetConsoleCursorInfo(gh_std_out, &lpCur);
    lpCur.bVisible = FALSE;
    SetConsoleCursorInfo(gh_std_out, &lpCur);       /*���ع��*/

    /*���붯̬�洢����Ϊ��Ų˵�����Ļ���ַ���Ϣ�Ļ�����*/
    gp_buff_menubar_info = (CHAR_INFO *)malloc(size.X * size.Y * sizeof(CHAR_INFO));
    SMALL_RECT rcMenu ={0, 0, size.X-1, 0} ;

    /*�����ڵ�һ�е����ݶ��뵽��Ų˵�����Ļ���ַ���Ϣ�Ļ�������*/
    ReadConsoleOutput(gh_std_out, gp_buff_menubar_info, size, pos, &rcMenu);

    /*����һ����Ӣ����ĸ��Ϊ��ɫ�������ַ���Ԫ��Ϊ�׵׺���*/
    for (i=0; i<size.X; i++)
    {
        (gp_buff_menubar_info+i)->Attributes = BACKGROUND_BLUE | BACKGROUND_GREEN
                                               | BACKGROUND_RED;
        ch = (char)((gp_buff_menubar_info+i)->Char.AsciiChar);
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
        {
            (gp_buff_menubar_info+i)->Attributes |= FOREGROUND_RED;
        }
    }

    /*�޸ĺ�Ĳ˵����ַ���Ϣ��д�����ڵĵ�һ��*/
    WriteConsoleOutput(gh_std_out, gp_buff_menubar_info, size, pos, &rcMenu);
    COORD endPos = {0, 1};
    SetConsoleCursorPosition(gh_std_out, endPos);   /*�����λ�������ڵ�2�е�1��*/

    /*���˵�����Ϊ�������������Ϊ�˵���ţ���������Ϊ0(��ť��)*/
    i = 0;
    do
    {
        PosB = PosA + strlen(ga_main_menu[i]);      /*��λ��i+1�Ų˵������ֹλ��*/
        for (j=PosA; j<PosB; j++)
        {
            gp_scr_att[j] |= (i+1) << 2;            /*���ò˵��������ַ���Ԫ������ֵ*/
        }
        PosA = PosB + 4;
        i++;
    } while (i<5);

    TagMainMenu(gi_sel_menu);                       /*��ѡ�����˵���������ǣ�gi_sel_menu��ֵΪ1*/
    return;
}

/********
�������ƣ�TagMainMenu
�������ܣ���ָ�����˵�������ѡ�б��
���������numΪѡ�е����˵����
�����������
�� �� ֵ��void���ͣ��޷���ֵ
����˵������
********/
void TagMainMenu(int num)
{
    CONSOLE_SCREEN_BUFFER_INFO bInfo;
    COORD size;
    COORD pos = {0, 0};
    int PosA = 2, PosB;
    char ch;
    int i;

    if (num == 0)                                   /*numΪ0ʱ������ȥ�����˵���ѡ�б��*/
    {
        PosA = 0;
        PosB = 0;
    }
    else                                            /*���򣬶�λѡ�����˵������ֹλ��: PosAΪ��ʼλ��, PosBΪ��ֹλ��*/
    {
        for (i=1; i<num; i++)
        {
            PosA += strlen(ga_main_menu[i-1]) + 4;
        }
        PosB = PosA + strlen(ga_main_menu[num-1]);
    }

    GetConsoleScreenBufferInfo( gh_std_out, &bInfo );
    size.X = bInfo.dwSize.X;
    size.Y = 1;

    /*ȥ��ѡ�в˵���ǰ��Ĳ˵���ѡ�б��*/
    for (i=0; i<PosA; i++)
    {
        (gp_buff_menubar_info+i)->Attributes = BACKGROUND_BLUE | BACKGROUND_GREEN
                                               | BACKGROUND_RED;
        ch = (gp_buff_menubar_info+i)->Char.AsciiChar;
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
        {
            (gp_buff_menubar_info+i)->Attributes |= FOREGROUND_RED;
        }
    }

    /*��ѡ�в˵���������ǣ��ڵװ���*/
    for (i=PosA; i<PosB; i++)
    {
        (gp_buff_menubar_info+i)->Attributes = FOREGROUND_BLUE | FOREGROUND_GREEN
                                               | FOREGROUND_RED;
    }

    /*ȥ��ѡ�в˵������Ĳ˵���ѡ�б��*/
    for (i=PosB; i<bInfo.dwSize.X; i++)
    {
        (gp_buff_menubar_info+i)->Attributes = BACKGROUND_BLUE | BACKGROUND_GREEN
                                               | BACKGROUND_RED;
        ch = (char)((gp_buff_menubar_info+i)->Char.AsciiChar);
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
        {
            (gp_buff_menubar_info+i)->Attributes |= FOREGROUND_RED;
        }
    }

    /*�����ñ�ǵĲ˵�����Ϣд�����ڵ�һ��*/
    SMALL_RECT rcMenu ={0, 0, size.X-1, 0};
    WriteConsoleOutput(gh_std_out, gp_buff_menubar_info, size, pos, &rcMenu);
    return;
}
