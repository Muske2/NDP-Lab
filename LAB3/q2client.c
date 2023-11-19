#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define MAX 100


int main()
{
	int s,r,sntb,recb,x;
	struct sockaddr_in server;
	socklen_t len;
	char buff[MAX];
	printf("Enter port number: ");
	scanf("%d",&x);
	s=socket(AF_INET,SOCK_DGRAM,0);
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
		printf("\nConnect error.");
		close(s);
		exit(1);
	}
	printf("\nSocket connected.");
	//printf("\nParent Process:\nPID: %d  PPID: %d\n",getpid(),getppid());
	while(1)
	{
			printf("\nEnter string: ");
			scanf("%s",buff);
			sntb=sendto(s,buff,sizeof(buff),0,(struct sockaddr*)&server,sizeof(server));
			if(strcmp(buff,"BYE")==0)
			{ printf("\nExiting.");close(s);exit(1);}
	}
	close(s);
	return 0;
}