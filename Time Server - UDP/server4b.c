#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
void main()
{
	time_t t;
	struct sockaddr_in server,cli;
	int cli_len,sd,n,i,len,data,temp,portno;
	
	char buffer[100],ipaddr[20],buffer1[100];
	
	if((sd=socket(AF_INET,SOCK_DGRAM,0))<0)
	{
		perror("SOCKET FAILED");
		exit(1);
	}
	
	memset(&server,0,sizeof(server));
	memset(&cli,0,sizeof(cli));

	server.sin_family=AF_INET;
	server.sin_port=htons(8080);
	server.sin_addr.s_addr=htonl(INADDR_ANY);
	
	if(bind(sd,(struct sockaddr *)&server,sizeof(server))<0)
	{
		perror("\nBIND ERROR");
		exit(1);
	}
	
	 len = sizeof(cli); 
    
         n = recvfrom(sd, (char *)buffer,1024,  MSG_WAITALL, ( struct sockaddr *) &cli, &len); 
    	buffer[n] = '\0'; 
    	printf("REQUEST RECIEVED FROM CLIENT\n");
    	if(strcmp("GET TIME",buffer)==0)
    	{
    		time(&t);
    		strcpy(buffer1 ,ctime(&t));
    		sendto(sd, (const char *)buffer1, strlen(buffer1),MSG_CONFIRM, (const struct sockaddr *) &cli, len); 
    		printf("TIME-STAMP  DELIVERED \n");
    	}
    	
 	
		
}
	
