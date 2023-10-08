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
	int choice,n;
	int num[MAX];
	do
	{
		printf("\n1. Search for a number.\n2. Sort in asc/desc. \n3. Split array into odd and even.\n4. Exit\n");
		printf("\nEnter choice: ");
		scanf("%d",&choice);
		send(s,&choice,sizeof(choice),0);
		switch(choice)
		{
			case 1:
				printf("\nEnter number of elements in array: ");
				scanf("%d",&n);
				printf("\nEnter numbers: ");
				for(int i=0;i<n;i++)
				{
					scanf("%d",&num[i]);
				}
				send(s,&n,sizeof(n),0);
				send(s,num,n*sizeof(int),0);
				int target,ans;
				printf("\nEnter number to be searched: ");
				scanf("%d",&target);
				send(s,&target,sizeof(target),0);
				recv(s,&ans,sizeof(ans),0);
				if(ans==-1)
				{
					printf("\nNumber absent in array.");
				}
				else
				{
					printf("Number found in position: %d",ans);
				}
				break;
			case 2:
				printf("\nEnter number of elements in array: ");
				scanf("%d",&n);
				printf("\nEnter numbers: ");
				for(int i=0;i<n;i++)
				{
					scanf("%d",&num[i]);
				}
				send(s,&n,sizeof(n),0);
				send(s,num,n*sizeof(int),0);
				int c;
				printf("\nEnter 1 for ascending or 2 for descending: ");
				scanf("%d",&c);
				send(s,&c,sizeof(c),0);
				recv(s,num,n*sizeof(int),0);
				printf("\nSorted array: ");
				for(int i=0;i<n;i++)
				{
					printf("%d ",num[i]);
				}
				printf("\n");
				break;
			case 3:
				printf("\nEnter number of elements in array: ");
				scanf("%d",&n);
				printf("\nEnter numbers: ");
				for(int i=0;i<n;i++)
				{
					scanf("%d",&num[i]);
				}
				send(s,&n,sizeof(n),0);
				send(s,num,n*sizeof(int),0);
				int e,o;
				recv(s,&e,sizeof(e),0);
				recv(s,&o,sizeof(o),0);
				int even[e];
				int odd[o];
				recv(s,even,e*sizeof(int),0);
				recv(s,odd,o*sizeof(int),0);
				printf("\nEVEN ARRAY: ");
				for(int i=0;i<e;i++)
				{
					printf("%d ",even[i]);
				}
				printf("\n");
				printf("\nODD ARRAY: ");
				for(int i=0;i<o;i++)
				{
					printf("%d ",odd[i]);
				}
				printf("\n");
				break;
		}
	}
	while(choice!=4);
	close(s);
	return 0;
}
