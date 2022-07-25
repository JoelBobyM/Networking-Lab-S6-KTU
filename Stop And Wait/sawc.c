#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#define PORT 8080
void stop_and_wait(int client_socket)
{
  char frame[100];
  int seqno=0;
  char ack[6];
  int next=1,i=0;
  char exit[4]={'e','x','i','t'};
  while(1)
  {
    int noexit=0;
    if(next==1)
    {
      bzero(frame,100);
      i=1;
      printf("\nEnter message to server:");
      while((frame[i++]=getchar())!='\n');
      frame[i-1]='\0';
      frame[0]=seqno;
    }
    sleep(3);
    send(client_socket,frame,sizeof(frame),0);
    bzero(ack,6);
    recv(client_socket,ack,sizeof(ack),0);
    if(ack[0]=='A')
    {
      printf("Acknowledgement received from server for frame %d - [",seqno);
      for(int j=1;frame[j]!='\0';j++)
        printf("%c",frame[j]);
      printf("]\n");
      seqno=seqno==0?1:0;
      next=1;
    }
    else
    {
      next=0;
      printf("Negative acknowledgement received from server for frame %d -[",seqno);
      for(int j=1;frame[j]!='\0';j++) 
        printf("%c",frame[j]);
      printf("]\nResending frame %d - [",seqno);
      for(int j=1;frame[j]!='\0';j++) 
        printf("%c",frame[j]);
      printf("]\n");
    }
    for(int j=1;j<5;j++)
    {
      if(frame[j]!=exit[j-1])
      {
        noexit=1;
        break;
      }
    }
    if(noexit==0)
    {
      printf("Client has successfully exited the network\n");
      return;
    }
  }
}
int main ()
{
  int client_socket,sock;
  client_socket = socket (PF_INET, SOCK_STREAM, 0);
  if (client_socket < 0)
  {
    printf("Error creating socket ...\n");
    exit (1);
  }
  else
  {
    printf ("Socket created successfully ...\n");
  }
  struct sockaddr_in sa;
  bzero (&sa, sizeof (sa));
  sa.sin_family = PF_INET;	
  sa.sin_port = htons (PORT);	
  sa.sin_addr.s_addr = inet_addr ("127.0.0.7");
  if (connect(client_socket, (struct sockaddr*)&sa,sizeof(sa))< 0) 
  {
     printf("\nConnection Failed \n");
     return -1;
  }
  else 
    printf("\nConnected successfully\n");
  stop_and_wait (client_socket);
  close (client_socket);
}
