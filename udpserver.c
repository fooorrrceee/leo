#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
  int server_socket;
  struct sockaddr_in server_address;
  char buffer[1024];

  server_socket=socket(AF_INET,SOCK_DGRAM,0);

  server_address.sin_family=AF_INET;
  server_address.sin_addr.s_addr=INADDR_ANY;
  server_address.sin_port=htons(8080);



  bind(server_socket,(struct sockaddr *)&server_address,sizeof(server_address));

  printf("Server listening\n");
  while(1)
  {

    socklen_t client_address_size=sizeof(server_address);
    int bytes_recieved=recvfrom(server_socket,buffer,sizeof(buffer),0,(struct sockaddr *)&server_address,&client_address_size);
    buffer[bytes_recieved]='\0';
    printf("Message recieved: %s\n",buffer);
    if(strcmp(buffer,"exit")==0)
    {
      break;
    }
    printf("Enter message to send ");
    fgets(buffer,sizeof(buffer),stdin);
    buffer[strcspn(buffer,"\n")]=0;
    sendto(server_socket,buffer,strlen(buffer),0,(struct sockaddr *)&server_address,sizeof(server_address));
  }
  close(server_socket);
  return 0;
}