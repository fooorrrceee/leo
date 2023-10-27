#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>

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
	
	char input[100],temp[30],key[30],key1[30],final[100],quo[100];
	printf("Enter binary message: ");
	fgets(input,sizeof(input),stdin);
	input[strcspn(input,"\n")]=0;
	printf("Enter Generator polynomial: ");
	fgets(key,sizeof(key),stdin);
	key[strcspn(key,"\n")]=0;
	strcpy(final,input);
	int meslen=strlen(input);
	int keylen=strlen(key);
	char rem[keylen-1];
	char key2[keylen];
	strcpy(key2,key);
	
	
	int i=0,j=0;
	for(i=0;i<keylen-1;i++)
	{
		input[meslen+i]='0';
	}
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
	printf("CRC is : ");
	for(i=0;i<keylen-1;i++)
	{
		printf("%c ",rem[i]);
	}
	printf("\n");
	rem[i]='\0';
	int k=1;
	printf("Do you want to simulate error(enter 0 for yes): ");
	
	scanf("%d",&k);
	if(k==0)
	{
		printf("Enter position to introduce error ");
		int pos=0;
		scanf("%d",&pos);
		if(pos<0 || pos>= meslen)
		{
			printf("OUT OF BOUNDS\n");
		}
		else
		{
			if(final[pos]=='0')
			{
				final[pos]='1';
			}
			else
			{
				final[pos]='0';
			}
		}
	}
	write(client_socket,final,100);
	write(client_socket,rem,30);
	write(client_socket,key2,30);
	printf("\n");
	memset(buffer,0,sizeof(buffer));
	int bytes_recieved=recv(client_socket,buffer,sizeof(buffer),0);
	printf("Message recieved : %s\n",buffer);
	close(client_socket);
	return 0;
}
	
	































