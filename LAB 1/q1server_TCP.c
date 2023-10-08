#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<netinet/in.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#define MAX 100

void search(int ns,int num[],int n)
{
   int i,target=0,pos=-1;
   recv(ns,&target,sizeof(target),0);
   for(i=0;i<n;i++)
   {
   	if(num[i]==target)
   	{
   		pos=i;
   	}
   }
   send(ns,&pos,sizeof(pos),0);
}
void sortnum(int ns,int num[],int n)
{
	int i,j,temp,c=0;
	recv(ns,&c,sizeof(c),0);
	if(c==1) //Ascending
	{
		for(i=0;i<n-1;i++)
		{
			for(int j=0;j<n-i-1;j++)
			{
				if(num[j]>num[j+1])
				{
					temp=num[j+1];
					num[j+1]=num[j];
					num[j]=temp;
				}
			}
		}
	}
	if(c==2) //Descending
	{
		for(i=0;i<n-1;i++)
		{
			for(int j=0;j<n-i-1;j++)
			{
				if(num[j]<num[j+1])
				{
					temp=num[j+1];
					num[j+1]=num[j];
					num[j]=temp;
				}
			}
		}
	}
	send(ns,num,n*sizeof(int),0);
}
void split(int ns,int num[],int n)
{
	int i,j=0,k=0,e=0,o=0;
	for(int i=0;i<n;i++)
	{
		if(num[i]%2==0)
		{
			e++;
		}
		else
		{
			o++;
		}
	}
	int even[e];
	int odd[o];
	for(i=0;i<n;i++)
	{
		if(num[i]%2==0)
		{
			even[j]=num[i];
			j++;
		}
		else
		{
			odd[k]=num[i];
			k++;
		}
	}
	send(ns,&e,sizeof(e),0);
	send(ns,&o,sizeof(o),0);
	send(ns,even,e*sizeof(int),0);
	send(ns,odd,o*sizeof(int),0);
}
int main()
{
   int s,ns,r,sntb,recb,i,x;
   struct sockaddr_in server,client;
   socklen_t len;
   //char buff[MAX];
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
   printf("\nBinding successful");
   r=listen(s,1);
   if(r==-1)
   {
   	close(s);
   	exit(1);
   }
   printf("\nServer listening...");
   len=sizeof(client);
   ns=accept(s,(struct sockaddr*)&client,&len);
   if(ns==-1)
   {
   	printf("\nAccepting error.");
   	close(s);
   	exit(1);
   }
   printf("Connection accepted.");
   while(1)
   {
   	int choice,n;
   	int num[MAX];
   	recb=recv(ns,&choice,sizeof(choice),0);
   	if(recb==-1)
   	{
   		printf("\nMessage not received.");
   		close(s);
   		close(ns);
   		exit(1);
   	}
   	if(recb==0)
   	{
   		printf("\nClient disconnected.");
   		close(s);
   		close(ns);
   		exit(1);
   	}
   	switch(choice)
   	{
   		case 1: //search
   			recb=recv(ns,&n,sizeof(n),0);
   			if(recb==-1)
   			{
   				printf("\nMessage not received.");
   				close(s);
   				close(ns);
   				exit(1);
   			}
   			recb=recv(ns,num,n*sizeof(int),0);
   			if(recb==-1)
   			{
   				printf("\nMessage not received.");
   				close(s);
   				close(ns);
   				exit(1);
   			}
   			search(ns,num,n);
   			break;
   		case 2:  //sort
   			recb=recv(ns,&n,sizeof(n),0);
   			if(recb==-1)
   			{
   				printf("\nMessage not received.");
   				close(s);
   				close(ns);
   				exit(1);
   			}
   			recb=recv(ns,num,n*sizeof(int),0);
   			if(recb==-1)
   			{
   				printf("\nMessage not received.");
   				close(s);
   				close(ns);
   				exit(1);
   			}
   			sortnum(ns,num,n);
   			break;
   		case 3:  //split
   			recb=recv(ns,&n,sizeof(n),0);
   			if(recb==-1)
   			{
   				printf("\nMessage not received.");
   				close(ns);
   				close(s);
   				exit(1);
   			}
   			recb=recv(ns,num,n*sizeof(int),0);
   			if(recb==-1)
   			{
   				printf("\nMessage not received.");
   				close(ns);
   				close(s);
   				exit(1);
   			}
   			split(ns,num,n);
   			break;
   		case 4: //exit
   			printf("\nEXITING");
   			close(ns);
   			close(s);
   			exit(1);
   			break;
   		default:
   			printf("\nInvalid choice!");
   			break;
   	}
   }
   close(ns);
   close(s);
   return 0;
}
