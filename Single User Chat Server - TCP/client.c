#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <string.h>
void main()
{
	struct sockaddr_in server;
	int sd;
	char buff[100],ip_addr[100];
	printf(">>> CLIENT STARTED\n");
	printf(">>> ENTER THE SERVER IP ADDRESS :  ");
	scanf("%s",ip_addr);
	if((sd = socket(AF_INET,SOCK_STREAM,0))<0)
	{
		perror("Socket Failed");
		exit(0);
	}
	else
	{
		server.sin_family = AF_INET;
		server.sin_port = htons(8080);
		inet_pton(AF_INET,ip_addr,&server.sin_addr);
		
		if(connect(sd,(struct sockaddr*)&server,sizeof(server)))
		{
			perror("CONNECTION FAILED");
			exit(0);
		}
		else
		{
			printf(">>> ENTER THE STRING : ");
			scanf("% %");
			fgets(buff,sizeof(buff),stdin);
			buff[strlen(buff)-1]='\0';
			write(sd,buff,sizeof(buff));
			read(sd,buff,sizeof(buff));
			printf(">>> REVERSED STRING : %s\n",buff);
			close(sd);
		}
	}
}	
