#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>


int main()
{
  int listenfd = 0;
  int connfd = 0;
  struct sockaddr_in sevr_addr;
  
  char sendBuf[1025];
  char recvBuf[1025];
  int numrv;
  int n=0;
  
  listenfd = socket(AF_INET, SOCK_STREAM, 0);
  printf("Socket retrieve success\n");
  
  memset(&sevr_addr, 0, sizeof(sevr_addr));
  memset(sendBuf, 0, sizeof(sendBuf));
  
  sevr_addr.sin_family = AF_INET;
  sevr_addr.sin_port = htons(5000);
  sevr_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  
  bind(listenfd, (struct sockaddr*) &sevr_addr, sizeof(sevr_addr));
  if (listen(listenfd,10) == -1)
  {
    printf("failed to listen");
    return -1;
  }
  
  while(1)
  {
    connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
    printf("client connected\n");
    while((n=read(connfd, recvBuf, sizeof(recvBuf) - 1)) > 0)
  {
    recvBuf[n] = 0;
    /*  if(fputs(recvBuf, stdout) == EOF)
    {
      break;
    }*/
      printf("%s\n", recvBuf);
  }
    
    strcpy(sendBuf, "Message from server\0");
    write(connfd, sendBuf, strlen(sendBuf));
    close(connfd);
    sleep(1);
  }
  return 0;
}