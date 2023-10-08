#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#define MAX 100

int main()
{
	int s,r,recb,sntb,x,ca;
	char buff[MAX];
	struct sockaddr_in server,client;
	socklen_t len;
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
	server.sin_addr.s_addr=htonl(INADDR_ANY);
	r=bind(s,(struct sockaddr*)&server,sizeof(server));
	if(r==-1)
	{
		printf("\nBinding error.");
		close(s);
		exit(1);
	}
	printf("\nSocket binded.");
	len=sizeof(client);
	ca=sizeof(client);
	while(1)
	{
		recb=recvfrom(s,buff,sizeof(buff),0,(struct sockaddr*)&client,&ca);
		if(recb==-1)
		{
			printf("\nMessage not received.");
			close(s);
			exit(1);
		}
		printf("\nMessage received: ");
		int l=strlen(buff);
		for(int i=0;i<l;i++)
		{
			printf("%c",buff[i]);
		}
		if(strcmp("Halt",buff)==0)
		{
			printf("\nExiting");
			close(s);
			exit(1);
		}
		char rev[100];
		int a=0,e=0,I=0,o=0,u=0,ans,i,j;
		for(i=l-1,j=0;i>=0;i--,j++)
		{
			rev[j]=buff[i];
			switch(buff[j])
			{
				case 'a':
				case 'A':
					a++;
					break;
				case 'e':
				case 'E':
					e++;
					break;
				case 'i':
				case 'I':
					I++;
					break;
				case 'o':
				case 'O':
					o++;
					break;
				case 'u':
				case 'U':
					u++;
					break;
			}
		}
		rev[j]='\0';
		if(strcmp(buff,rev)==0)
		{
			ans=1;
		}
		else
		{
			ans=0;
		}
		sendto(s,&ans,sizeof(ans),0,(struct sockaddr*)&client,len);
		sendto(s,&a,sizeof(a),0,(struct sockaddr*)&client,len);
		sendto(s,&e,sizeof(e),0,(struct sockaddr*)&client,len);
		sendto(s,&I,sizeof(I),0,(struct sockaddr*)&client,len);
		sendto(s,&o,sizeof(o),0,(struct sockaddr*)&client,len);
		sendto(s,&u,sizeof(u),0,(struct sockaddr*)&client,len);
	}
	close(s);
	return 0;
	
}
