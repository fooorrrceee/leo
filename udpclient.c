#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main()
{
  int client_socket;
  struct sockaddr_in server_address;
  char buffer[1024];

  client_socket=socket(AF_INET,SOCK_DGRAM,0);

  server_address.sin_family=AF_INET;
  inet_pton(AF_INET,"127.0.0.1",&server_address.sin_addr);
  server_address.sin_port=htons(8080);


  connect(client_socket,(struct sockaddr *)&server_address,sizeof(server_address));

  printf("Connected to 8080\n");
  while(1)
  {
    printf("Enter message to send ");
    fgets(buffer,sizeof(buffer),stdin);
    buffer[strcspn(buffer,"\n")]=0;
    sendto(client_socket,buffer,strlen(buffer),0,(struct sockaddr *)&server_address,sizeof(server_address));
    if(strcmp(buffer,"exit")==0)
    {
      break;
    }
    memset(buffer,0,sizeof(buffer));
    socklen_t client_address_size=sizeof(server_address);
    int bytes_recieved = recvfrom(client_socket,buffer,sizeof(buffer),0,NULL,NULL);
    buffer[bytes_recieved]='\0';
    printf("Message recieved : %s\n",buffer);
  }
  close(client_socket);
  return 0;
}