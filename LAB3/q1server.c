#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<netinet/in.h>
#define MAX 100

int main()
{
	int s,r,ns,x,sntb,recb;
	struct sockaddr_in server,client;
	socklen_t len;
	pid_t pid,ppid;
	char  inbuff[1024],outbuff[1024];
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
	pid=fork();
	if(pid==0)
	{
		printf("\nChild process: \nPID: %d   PPID: %d",getpid(),getppid());
		while(1)
		{recb= recv(ns, inbuff, sizeof(inbuff), 0);

            //inbuff[recb] = '\0';

            if (strcmp(inbuff, "BYE") == 0) {
                // Gracefully exit the child process
                break;
            }

            printf("Client: %s\n", inbuff);
		}
	}
	else
	{
		printf("\nParent process: \nPID: %d   PPID: %d",getpid(),getppid());
		while(1)
		{
			printf("Server: ");
			scanf("%s",outbuff);
			sntb=send(ns,outbuff,strlen(outbuff),0);
			if(strcmp(outbuff,"BYE")==0)
			{
				printf("\nExiting");
				break;
			}
		}
	}
	close(ns);
	close(s);
	return 0;
}

