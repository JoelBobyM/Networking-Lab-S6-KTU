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
	struct sockaddr_in serv,cli;
	int sd,p,cli_len,data,i,l;
	char buffer[100],temp;
	printf(">>> SERVER STARTED\n");
	if((sd = socket(AF_INET,SOCK_STREAM,0))<0)
	{
		perror("SOCKET FAILED");
		exit(1);
	}
	else
	{
		printf(">>> WAITING FOR CLIENT .......\n");
		 serv.sin_family = AF_INET;
		 serv.sin_port = htons(8080);
		 serv.sin_addr.s_addr = htonl(INADDR_ANY);
		 if(bind(sd,(struct sockaddr *)&serv,sizeof(serv))<0)
		 {
		 	perror("BIND ERROR !!");
		 	exit(1);
		 }
		 else
		 {
		 	listen(sd,5);
		 	if((data = accept(sd,(struct sockaddr*)&cli,&cli_len))<0)
		 	{
		 		perror("ACCEPT FAILED");
		 		exit(1);
		 	}
		 	else
		 	{
		 		printf(">>> CONNECTION CREATED\n");
		 		read(data,buffer,sizeof(buffer));
		 		 l=strlen(buffer);
    				for(i=0;i<l/2;i++)
    				{
      					temp=buffer[i];
      					buffer[i]=buffer[l-1-i];
      					buffer[l-1-i]=temp;
    				}
    				write(data,buffer,sizeof(buffer));
		 		close(data);
		 		printf(">>> CONNECTION CLOSED\n");
		 		close(sd);
		 	}
		 }
	}
}
