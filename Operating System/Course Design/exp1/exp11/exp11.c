#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<malloc.h>
#include<signal.h>

#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<linux/sem.h> 
#include<fcntl.h>


#define BufferSize 1000
#define BufferNum 50
char* writePath; 
char* readPath; 

int pid1,pid2;
int semid;

typedef struct sharebuff{
	char data[BufferSize];
	bool end;
	int len;
	struct sharebuff* next;
}ShareBuff;
ShareBuff* head=NULL,*tail=NULL;
int Buffers[BufferNum];

int semget(key_t,int,int);
int semop(int,struct sembuf*,unsigned);
int semctl(int,int,int,union semun);
int shmget(key_t,int,int);
void* shmat(int,char*,int);
int shmctl(int,int,ShareBuff*);

void killall()
{
	kill(pid1,SIGUSR1);
	kill(pid2,SIGUSR2);
}
void killp(int signal)
{
	exit(0);
}
void P(int semid,int index)
{
	struct sembuf sem;
	sem.sem_num=index;//要操作的信号灯的编号
	sem.sem_op=-1;//要执行的操作
	sem.sem_flg=0;//操作标志，一般设置为0
	semop(semid,&sem,(unsigned)1);
	return;
}
void V(int semid,int index)
{
	struct sembuf sem;	
	sem.sem_num = index;
	sem.sem_op =  1;
	sem.sem_flg = 0;	
	semop(semid,&sem,(unsigned)1);	
	return;
}
void readbuf()
{
	signal(SIGINT,SIG_IGN);//设置忽略信号SIGINT
	signal(SIGUSR1,killp);//设置信号SIGUSR1
	ShareBuff* in=head;
	int fd;
	if((fd=open(readPath,O_RDONLY))==-1)
	{
		printf("Open failed in readBuf.\n");
		kill(pid2,SIGUSR2);
		close(fd);
		exit(0);
	}
	int len;	
	while(1)
	{
		P(semid,0);
		len=read(fd,in->data,BufferSize);
		if(len!=BufferSize)
		{
			in->end=1;
			in->len=len;
			V(semid,1);
			close(fd);
			exit(0);
		}
		in=in->next;
		V(semid,1);	
	}
	exit(0);
}
void writebuf()
{
	signal(SIGINT,SIG_IGN);//设置忽略信号SIGINT
	signal(SIGUSR2,killp);//设置信号SIGUSR2
	ShareBuff* out=head;
	int fd;
	if((fd=open(writePath,O_WRONLY|O_TRUNC|O_CREAT,S_IRWXU))==-1)
	{
		printf("Open failed in writeBuf.\n");
		kill(pid1,SIGUSR1);
		close(fd);
		exit(0);
	}
	int len;	
	while(1)
	{
		P(semid,1);
		
		if(out->end==1)
		{
			len=write(fd,out->data,out->len);
			V(semid,0);
			close(fd);
			exit(0);
		}
		len=write(fd,out->data,BufferSize);
		out=out->next;
		V(semid,0);	
	}
	exit(0);
}
int main(int argc,char*argv[])
{
	readPath=(char *)malloc(10*sizeof(char));
	writePath=(char *)malloc(10*sizeof(char));
	if(argc==1)
	{
		printf("Source:");scanf("%s",readPath);getchar();
		printf("Target:");scanf("%s",writePath);getchar();
	}
	else if(argc==2)
	{
		readPath=argv[1];
		char*str=(char *)malloc(10*sizeof(char));
		strcpy(str,argv[1]);
		char*tail=(char *)malloc(10*sizeof(char));
		int i,j,k;		
		for(i=0;i<strlen(str);i++)
			if(str[i]=='.')break;
		k=strlen(str);
		for(j=0;i<strlen(str);i++,j++)	
			tail[j]=str[i];
		tail[j]='\0';
		for(;k>=i-j;k--)
			str[k]='\0';
		strcat(str,"_Copy");
		strcat(str,tail);
		strcpy(writePath,str);
	}
	else if(argc==3)
	{
		readPath=argv[1];
		writePath=argv[2];
	}
	else
	{
		printf("Input error.\n");
		exit(0);
	}
	printf("Source:%s\n",readPath);
	printf("Target:%s\n",writePath);	


	int size=sizeof(ShareBuff);
	void* shm=NULL;
	for(int i=0;i<BufferNum;i++)
	{
		ShareBuff* q=(ShareBuff*)malloc(size);
	
		Buffers[i]=shmget(IPC_PRIVATE,size,IPC_CREAT|0666);
		if(Buffers[i]==-1)
		{
			printf("shmget failed.\n");
			exit(0);
		}

		shm=shmat(Buffers[i],(void*)0,0);
		if(shm==(void*)-1)
		{
			printf("shmat failed.\n");
			exit(0);
		}

		q=(ShareBuff*)shm;
		q->next=NULL;
		if(i==0)
		{
			head=(ShareBuff*)malloc(sizeof(ShareBuff));
			head=q;
			tail=q;
		}
		else
		{
			tail->next=q;
			tail=q;
		}
	}
	tail->next=head;
	
	//创建新信号量或获取一个已经存在的信号量的键值
	//IPC_CREAT表示不存在则创建
	semid=semget(IPC_PRIVATE,2,IPC_CREAT|0666);
	
    	//用于初始化信号量，在使用信号量前必须这样做
	//SETVAL用来把信号量初始化为一个已知的值
    	union semun sem_union;
	sem_union.val = BufferNum;
  	semctl(semid,0,SETVAL,sem_union);
  	sem_union.val=0;
  	semctl(semid,1,SETVAL,sem_union);

	while((pid1=fork())==-1);
	if(pid1!=0)
	{
		while((pid2=fork())==-1);
	}

	if(pid1==0)
		readbuf();
	else if(pid2==0)
		writebuf();
	else
	{
		signal(SIGINT,killall);
		waitpid(pid1,NULL,0);
		waitpid(pid2,NULL,0);
		
		semctl(semid,0,IPC_RMID,sem_union);
  		semctl(semid,1,IPC_RMID,sem_union);

		for(int i=0;i<BufferNum;i++)
		{
			if(shmctl(Buffers[i],IPC_RMID,0)==-1)
			{
				printf("shmctl failed.\n");
				exit(0);
			}
		}
	}
	printf("Copy success!\n");
	return 0;
}