#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>
main()
{
int s,r,recb,sntb,port;
int ca;
printf("Enter port number: ");
scanf("%d",&port);
socklen_t len;
struct sockaddr_in server,client;
char buff[50];
s=socket(AF_INET,SOCK_DGRAM,0);
if(s==-1)
{
printf("\nSOcket creation error");
exit(0);
}
printf("\nSocket  created");
server.sin_family=AF_INET;
server.sin_port=htons(port);
server.sin_addr.s_addr=htonl(INADDR_ANY);
len=sizeof(client);
ca=sizeof(client);
r=bind(s,(struct sockaddr*)&server,sizeof(server));
if(r==-1)
{
printf("\n Socket BInded");
while(1)
{
recb=recvfrom(s,buff,sizeof(buff),0,(struct sockaddr*)&client,&ca);
if(recb==-1)
{
printf("\nMessage Receiving failed");
close(s);
exit(0);
}

