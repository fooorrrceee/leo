#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include <stdbool.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define SWS 3

typedef struct
{
	int seq_no;
	char data[20];
	int ack;
}Frame;

int main()
{
	int client_socket;
	struct sockaddr_in server_address;
	
	client_socket=socket(AF_INET,SOCK_STREAM,0);
	
	server_address.sin_family=AF_INET;
	server_address.sin_addr.s_addr=inet_addr("127.0.0.1");
	server_address.sin_port=htons(8080);
	
	connect(client_socket,(struct sockaddr *)&server_address,sizeof(server_address));
	
	printf("connected to server\n");
	
	Frame frames[SWS];
	int LFS=-1,LAR=-1,i=LAR+1,flag=1;
	for(;;)
	{
		for(;i<SWS;i++)
		{
			if(flag==1)
			{
				frames[i].seq_no=++LFS;
			}
			printf("Enter message for %d ",i);
			scanf("%s",frames[i].data);
			send(client_socket,&frames[i],sizeof(Frame),0);
			printf("\n");
			
		}
		i=(LAR+1)%SWS;
		for(;i<SWS;i++)
		{
			recv(client_socket,&frames[i].ack,sizeof(int),0);
		}
		i=(LAR+1)%SWS;
		for(;i<SWS;i++)
		{
			if(frames[i].ack ==0)
			{
				flag=0;
				break;
			}
			LAR+=1;
			flag=1;
		}
		i=(LAR+1)%SWS;
		if(flag==0)
		{
			printf("Retransmit frame\n");
			continue;
		}
		LAR+=SWS;
		i=(LAR+1)%SWS;
		printf("\n");
	}
	close(client_socket);
	return 0;
}

		































