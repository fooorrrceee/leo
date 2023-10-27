#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

#define RWS 3

typedef struct
{
	int seq_no;
	char data[20];
	int ack;
}Frame;

int main()
{
	int server_socket,client_socket;
	struct sockaddr_in server_address,client_address;
	char buffer[1024];
	
	server_socket=socket(AF_INET,SOCK_STREAM,0);
	
	server_address.sin_family=AF_INET;
	server_address.sin_addr.s_addr=INADDR_ANY;
	server_address.sin_port=htons(8080);
	
	bind(server_socket,(struct sockaddr *)&server_address,sizeof(server_address));
	
	listen(server_socket,1);
	printf("Server listening on 8080\n");
	
	socklen_t client_address_size=sizeof(client_address);
	client_socket=accept(server_socket,(struct sockaddr *)&client_address,&client_address_size);
	
	Frame frames[RWS];
	int LFR=-1,i=LFR+1,flag=1;
	for(;;)
	{
		for(;i<RWS;i++)
		{
			recv(client_socket,&frames[i],sizeof(Frame),0);
		}
		i=(LFR+1)%RWS;
		for(;i<RWS;i++)
		{
			printf("Frame %d , data: %s, seq_no :%d \n",i,frames[i].data,frames[i].seq_no);
			printf("Enter 0 for NoACK, 1 for ACK\n");
			scanf("%d",&frames[i].ack);
			printf("\n");
		}
		i=(LFR+1)%RWS;
		for(;i<RWS;i++)
		{
			send(client_socket,&frames[i].ack,sizeof(int),0);
		}
		i=(LFR+1)%RWS;
		for(;i<RWS;i++)
		{
			if(frames[i].ack==0)
			{
				flag=0;
				break;
			}
			LFR+=1;
			flag=1;
		}
		i=(LFR+1)%RWS;
		if(flag==0)
		{
			continue;
		}
		LFR+=RWS;
		i=(LFR+1)%RWS;
	}
	close(client_socket);
	close(server_socket);
	return 0;
}
		
































