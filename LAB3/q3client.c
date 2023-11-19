#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define MAX 100

int main()
{
	int s,x,r,recb,sntb;
	struct sockaddr_in server;
	socklen_t len;
	printf("Enter port number: ");
	scanf("%d",&x);
	char buff[MAX];
	s=socket(AF_INET,SOCK_STREAM,0);
	if(s==-1)
	{
		printf("\nSocket creation error.");
		exit(1);
	}
	printf("\nSocket created.");
	server.sin_family=AF_INET;
	server.sin_port=htons(x);
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	r=connect(s,(struct sockaddr*)&server,sizeof(server));
	if(r==-1)
	{
		printf("\nConnection error.");
		close(s);
		exit(1);
	}
	printf("\nSocket connected.");
	
	printf("\nEnter string: ");
	scanf("%s",buff);
	sntb=send(s,buff,sizeof(buff),0);
	char num[50],alpha[50];
	int pc,pp;
	//recb=recv(s,&pc,sizeof(pc),0);
	recb=recv(s,num,sizeof(num),0);
	printf("\n%s\n",num);
	recb=recv(s,&pp,sizeof(pp),0);
	recb=recv(s,alpha,sizeof(alpha),0);
	printf("\n%s\n",alpha);
	close(s);
	return 0;
}
