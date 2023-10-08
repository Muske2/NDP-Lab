#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#define MAX 100

int main()
{
	int s,r,sntb,recb,x;
	struct sockaddr_in server;
	socklen_t len;
	char buff[MAX];
	printf("\nEnter port number: ");
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
	len=sizeof(server);
	int sa=sizeof(server);
	while(1)
	{
		printf("\nEnter string: ");
		scanf("%s",buff);
		if(strcmp(buff,"Halt")==0)
		{
			printf("\nExiting.");
			sendto(s,buff,sizeof(buff),0,(struct sockaddr*)&server,len);
			close(s);
			exit(1);
		}
		sntb=sendto(s,&buff,sizeof(buff),0,(struct sockaddr*)&server,len);
		int a,e,I,o,u,ans;
		recvfrom(s,&ans,sizeof(ans),0,(struct sockaddr*)&server,&sa);
		if(ans==1)
		{
			printf("\nIt is a palindrome.");
		}
		else
		{
			printf("\nIt is not a palindrome.");
		}
		recvfrom(s,&a,sizeof(a),0,(struct sockaddr*)&server,&sa);
		recvfrom(s,&e,sizeof(e),0,(struct sockaddr*)&server,&sa);
		recvfrom(s,&I,sizeof(I),0,(struct sockaddr*)&server,&sa);
		recvfrom(s,&o,sizeof(o),0,(struct sockaddr*)&server,&sa);
		recvfrom(s,&u,sizeof(u),0,(struct sockaddr*)&server,&sa);
		printf("\nCount of vowels: \n");
		printf("a= %d\ne= %d\ni= %d\no= %d\nu= %d\n",a,e,I,o,u);
		printf("\n");
	}
	close(s);
	return 0;
}
