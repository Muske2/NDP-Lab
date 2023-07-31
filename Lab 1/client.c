#include<string.c>
#include<arpa/inet.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<sys/stat.h>
main()
{
int s,r,recb,sntb,port;
printf("Enter port number: ");
scanf("%d", &port);
struct sockaddr_in server;
char buff[50];
s=socket(AF_INET,SOCK_STREAM,0);
if(s==-1)
{
printf("\nSOcket creation error.");
exit(0);
}
printf("\nSOcket created.");
server.sin_family=AF_INET;
server.sin_port=htons(port);
server.sin_addr.s_addr=inet_addr("127.0.0.1");
r=connect(s,(struct sockaddr*)&server,sizeof(server));
if(r==-1)
{
printf("\nConnection error.");
exit(0);
}
printf("\nSocket connected.");
printf("\n\n");
printf("Type Message: ");
scanf("%s",buff);
sntb=send(s,buff,sizeof(buff),0);
if(sntb==-1)
{
close(s);
printf("\nMessage Sending Failed.");
exit(0);
}
recb=recv(s,buff,sizeof(buff),0);
if(recb==-1)
{
printf("Message Receiving Failed.");
close(s);
exit(0);
}
printf("\nMessage Received: ");
printf("%s",buff);
printf("\n\n");
close(s);
}


