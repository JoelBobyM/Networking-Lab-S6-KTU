#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

void main()
{
	struct sockaddr_in server;
	int sd,len,n;
	int portno;
	char ipaddr[20];
	char buffer[200];
	
	if((sd=socket(AF_INET,SOCK_DGRAM,0))<0)
	{
		printf("SOCKET FAILURE");
		exit(0);
	}
	
	memset(&server,0,sizeof(server));
	
	server.sin_family=AF_INET;
	server.sin_port=htons(8080);
	server.sin_addr.s_addr=INADDR_ANY;
	
	printf(">>> CLIENT : ");
	 fgets(buffer,sizeof(buffer),stdin);
	buffer[strlen(buffer)-1]='\0';
	sendto(sd, (const char *)buffer, strlen(buffer), MSG_CONFIRM, (const struct sockaddr *) &server, sizeof(server)); 
    	printf("REQUEST DELIVERED TO SERVER.\n"); 
   	 n = recvfrom(sd, (char *)buffer, 1024,  MSG_WAITALL, (struct sockaddr *) &server, &len); 
   	 buffer[n] = '\0'; 
    	printf(">>> SERVER  : %s", buffer); 
    	printf("CONVERSATION ENDED.\n");
	close(sd);

}

