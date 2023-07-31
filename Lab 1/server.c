#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet.h>
#include<stdlib.h>
#include<stdio.h>
main()
{
int s,r,recb,sntb,port,ns,a=0;
printf("Enter port number: ");
scanf("%d",&port);
socklen_t len;
struct sockaddr_in server,client;
char buff[50];
s=socket(AF_INET,SOCK_STREAM,0);
if(s==-1)
{
printf("\nSocket creation error.");
exit(0);
}
printf("\nSocket created.");
server.sin_family=AF_INET;
server.sin_port=htons(x);
server.sin_addr.s_addr=htonl(INADDR_ANY);
r=bind(s,(struct sockaddr*)&server,sizeof(server));
if(r==-1)
{
printf("\nBinding error.");
exit(0);
}
printf("\nSOcket binded.");
r=listens(s,1);
if(r==-1)
{
close(s);
exit(0);
}
printf("\nSocket listening.");
len=sizeof(client);
ns=accept(s,(struct sockaddr*)&client,&len);
if(ns==-1)
{
close(s);
exit(0);
}
printf("\Socket accepting.");
recb=recv(ns,buff,sizeof(buff),0);
if(recb==-1)
{
printf("\nMessage Receiving Failed.");
close(s);
close(ns);
exit(0);
}
printf("\nMessage REceived: ");
printf("%s", buff);
sntb=send(ns,buff,sizeof(buff),0);
if(sntb==1)
[
printf("\nMessage sending failed.");
close(s);
close(ns);
exit(0);
}
close(ns);
close(s);
}
