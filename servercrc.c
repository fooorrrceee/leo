#include <stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include <unistd.h>

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
	
	int client_address_size=sizeof(client_address);
	client_socket=accept(server_socket,(struct sockaddr *)&client_address,&client_address_size);
	
	printf("Connected to 8080\n");
	
	char input[100],rem[30],temp[30],key[30],key1[30],final[100],quo[100];
	
	read(client_socket,input,100);
	read(client_socket,rem,30);
	read(client_socket,key,30);
	printf("Message recieved: %s%s \n",input,rem);
	printf("CRC: %s\n",rem);
	printf("Generator polynomial: %s\n",key);
	
	
	
	strcpy(final,input);
	int meslen=strlen(input);
	int keylen=strlen(key);
	char key2[keylen];
	strcpy(key2,key);
	strcat(input,rem);
	
	int i=0,j=0;
	for(i=0;i<keylen;i++)
	{
		temp[i]=input[i];
	}
	strcpy(key1,key);
	for(i=0;i<meslen;i++)
	{
		quo[i]=temp[0];
		if(quo[i]=='0')
		{
			for(j=0;j<keylen;j++)
			{
				key[j]='0';
			}
		}
		else
		{
			for(j=0;j<keylen;j++)
			{
				key[j]=key1[j];
			}
		}
		for(j=keylen-1;j>0;j--)
		{
			if(temp[j]==key[j])
			{
				rem[j-1]='0';
			}
			else
			{
				rem[j-1]='1';
			}
		}
		rem[keylen-1]=input[i+keylen];
		strcpy(temp,rem);
	}
	strcpy(rem,temp);
	printf("Quotient is : ");
	for(i=0;i<meslen;i++)
	{
		printf("%c ",quo[i]);
	}
	printf("\n");
	printf("Remainder is : ");
	int flag=0;
	for(i=0;i<keylen-1;i++)
	{
		printf("%c ",rem[i]);
		if(rem[i]!='0')
		{
			flag++;
		}
	}
	printf("\n");
	rem[i]='\0';
	if(flag!=0)
	{
		strcpy(buffer,"ERROR IN TRANSMISSION\n");
		printf("%s\n",buffer);
		buffer[strcspn(buffer,"\n")]=0;
		send(client_socket,buffer,sizeof(buffer),0);
	}
	else
	{
		strcpy(buffer,"TRANSMISSION IS ERROR FREE\n");
		printf("%s\n",buffer);
		buffer[strcspn(buffer,"\n")]=0;
		send(client_socket,buffer,sizeof(buffer),0);
	}
	close(client_socket);
	close(server_socket);
	return 0;
}
	

































