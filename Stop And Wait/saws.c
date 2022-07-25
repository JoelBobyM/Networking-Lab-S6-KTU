#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#define PORT 8080
#define n 4
void stop_and_wait(int client_socket)
{
  char frame[100];
  int seqno=0;
  char ack[6];
  int count=1,i=0;
  char exit[4]={'e','x','i','t'};
  while(1)
  {
    int noexit=0;
    bzero(frame,100);
    recv(client_socket,frame,sizeof(frame),0);
    bzero(ack,6);
    if(frame[0]==seqno && count%n!=0)
    {
      ack[0] = 'A';
      ack[1] = 'C';
      ack[2] = 'K';
      ack[3] = seqno;
      ack[4] = '\0';
      printf("Frame received from client:");
      for(int j=1;frame[j]!='\0';j++)
        printf("%c",frame[j]);
      printf("\n");
      seqno=seqno==0?1:0;
    }
    else
    {
      ack[0] = 'N';
      ack[1] = 'A';
      ack[2] = 'C';
      ack[3] = 'K';
      ack[4] = seqno;
      ack[5] = '\0';
    }
    sleep(2);
    send(client_socket,ack,sizeof(ack),0);
    for(int j=1;j<5;j++)
    {
      if(frame[j]!=exit[j-1]) 
      {
        noexit = 1;
        break;
      }
    }
    if(noexit==0)
    {
      printf("Server has successfully exited the network ... \n");
      return;
    }
    count++;
  }
}
int main()
{
  int server_socket;
  server_socket=socket(PF_INET,SOCK_STREAM,0);
  if(server_socket<0)
  {
    printf("Error creating socket\n");
    exit(1);
  }
  else
  {
    printf("Socket created successfully\n");
  }
  struct sockaddr_in sa;
  bzero(&sa,sizeof(sa));
  sa.sin_family=PF_INET;
  sa.sin_port=htons(PORT);
  sa.sin_addr.s_addr=inet_addr("127.0.0.7");
  if(bind(server_socket,(struct sockaddr*)&sa,sizeof(sa))==0)
  {
    printf("Socket binded successfully\n");
  }
  else
  {
    printf("Unable to bind server\n");
    exit(1);
  }
  if(listen(server_socket,10)==0)
  {
    printf("Server listening\n");
  }
  else
  {
    printf("Server listen failed\n");
  }
  struct sockaddr_in cli;
  int len = sizeof(cli);
  int client_socket=accept(server_socket,(struct sockaddr*)&cli,&len);
  if(client_socket<0)
  {
    printf("Falied to accept client\n");
    exit(1);
  }
  else
  {
    printf("Server accepted client\n");
  }
  stop_and_wait(client_socket);
  close(server_socket);
}
