#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<netinet/in.h>
#include<ctype.h>
#include<sys/wait.h>
#define MAX 100

int main()
{
	int s,r,ns,x,sntb,recb;
	struct sockaddr_in server,client;
	socklen_t len;
	pid_t pid,ppid;
	char  buff[100];
	printf("Enter port number: ");
	scanf("%d",&x);
	s=socket(AF_INET,SOCK_STREAM,0);
	if(s==-1)
	{
		printf("\nSocket creation error.");
		exit(1);
	}
	printf("\nSocket created.");
	server.sin_family=AF_INET;
	server.sin_port=htons(x);
	server.sin_addr.s_addr=htonl(INADDR_ANY);
	r=bind(s,(struct sockaddr*)&server,sizeof(server));
	if(r==-1)
	{
		printf("\nBinding error.");
		close(s);
		exit(1);
	}
	printf("\nSocket binded.");
	r=listen(s,1);
	if(r==-1)
	{
		close(s);
		exit(1);
	}
	printf("\nSocket listening.");
	len=sizeof(client);
	ns=accept(s,(struct sockaddr*)&client,&len);
	if(ns==-1)
	{
		printf("\nAccept error.");
		close(s);
		exit(1);
	}
	printf("\nSocket accepting.");
	recb=recv(ns,buff,sizeof(buff),0);
	pid=fork();
	char num[50],alpha[50];
	int j=0,k=0;
	for(int i=0;i<strlen(buff);i++)
	{
		if(isalpha(buff[i]))
		{
			alpha[j]=buff[i];
			j++;
		}		
		else
		{
			num[k]=buff[i];
			k++;
		}
	}
	if(pid==0)
	{
		//pid_t pid=getpid();
		int snt;
		//snt=send(ns,&pid,sizeof(pid),0);
		for(int i=0;i<k-1;i++)
		{
			for (int a=0;a<k-i-1;a++)
			{
				if(num[a]>num[a+1])
				{
					char temp=num[a];
					num[a]=num[a+1];
					num[a+1]=temp;
				}
			}
		}
		snt=send(ns,num,sizeof(num),0);
	}
	else
	{
		int status;
		wait(&status);
		pid_t p=getpid();
		sntb=send(ns,&p,sizeof(p),0);
		for(int i=0;i<j-1;i++)
		{
			for (int a=0;a<j-i-1;a++)
			{
				if(alpha[a]<alpha[a+1])
				{
					char temp=alpha[a];
					alpha[a]=alpha[a+1];
					alpha[a+1]=temp;
				}
			}
		}
		sntb=send(ns,alpha,sizeof(alpha),0);
		
	}
	close(ns);
	close(s);
	return 0;
}

