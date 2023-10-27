#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
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
	
	listen(server_socket,5);
	printf("Server is listening\n");
	
	socklen_t client_address_size=sizeof(client_address);
	client_socket=accept(server_socket,(struct sockaddr *)&client_address,&client_address_size);
	printf("Client %s connected\n",inet_ntoa(client_address.sin_addr));
	
	while(1)
	{
		memset(buffer,0,sizeof(buffer));
		int bytes_recieved=recv(client_socket,buffer,sizeof(buffer),0);
		printf("Message recieved: %s\n",buffer);
		printf("Enter message to send" );
		fgets(buffer,sizeof(buffer),stdin);
		buffer[strcspn(buffer,"\n")]=0;
		send(client_socket,buffer,strlen(buffer),0);
		if(strcmp(buffer,"exit")==0)
		{
			break;
		}
	}
	close(client_socket);
	close(server_socket);
	return 0;
}
	

































