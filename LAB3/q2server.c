#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define MAX 100

void permute(char str[],int l,int r)
{
	if(l==r)
	{
		printf("%s\n",str);
	}
	else
	{
		for(int i=l;i<=r;i++)
		{
			char temp=str[l];
			str[l]=str[i];
			str[i]=temp;
			
			permute(str,l+1,r);
			
		        temp=str[l];
			str[l]=str[i];
			str[i]=temp;
		}
	}
	
}
int main()
{
	int s,r,sntb,recb,x;
	struct sockaddr_in server,client;
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
	server.sin_addr.s_addr=htonl(INADDR_ANY);
	r=bind(s,(struct sockaddr*)&server,sizeof(server));
	if(r==-1)
	{
		printf("\nBinding error.");
		close(s);
		exit(1);
	}
	printf("\nSocket binded.");
	printf("\nParent Process:\nPID: %d  PPID: %d\n",getpid(),getppid());
	len=sizeof(client);
	int ca=sizeof(client);
	while(1)
	{
			recb=recvfrom(s,buff,sizeof(buff),0,(struct sockaddr*)&client,&ca);
			if(strcmp(buff,"BYE")==0)
			{ printf("\nExiting.");close(s);exit(1);}
			permute(buff,0,strlen(buff)-1);
	}
	close(s);
	return 0;
}
