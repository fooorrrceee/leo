#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<netdb.h>
#include<fcntl.h>
#include<unistd.h>

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
    memset(buffer,0,sizeof(buffer));
    printf("Enter Message to send: ");
    fgets(buffer,sizeof(buffer),stdin);

    buffer[strcspn(buffer,"\n")]=0;
    send(client_socket,buffer,strlen(buffer),0);
    if(strcmp(buffer,"exit")==0)
    {
      break;
    }
  }
  close(client_socket);

  return 0;
}