#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>

int main()
{
	int client_socket;
	struct sockaddr_in server_address;
	char buffer[1024];
	
	client_socket=socket(AF_INET,SOCK_STREAM,0);
	
	server_address.sin_family=AF_INET;
	server_address.sin_addr.s_addr=inet_addr("127.0.0.1");
	server_address.sin_port=htons(8080);
	
	connect(client_socket,(struct sockaddr *)&server_address,sizeof(server_address));
	
	printf("Connected to Server\n");
	
	while(1)
	{
		printf("Enter message to send ");
		fgets(buffer,sizeof(buffer),stdin);
		buffer[strcspn(buffer,"\n")]=0;
		send(client_socket,buffer,strlen(buffer),0);
		memset(buffer,0,sizeof(buffer));
		int bytes_received =recv(client_socket,buffer,sizeof(buffer),0);
		printf("Message recieved: %s\n",buffer);
		if(strcmp(buffer,"exit")==0)
		{
			break;
		}
	}
	close(client_socket);
	return 0;
}































