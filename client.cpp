#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

int main()
{
  int sockfn = 0;
  int n = 0;
  
  char recvBuff[1024];
  
  struct sockaddr_in sevr_addr;
  memset(recvBuff, 0, sizeof(recvBuff));
  sockfn = socket(AF_INET, SOCK_STREAM, 0);
  
  sevr_addr.sin_family = AF_INET;
  sevr_addr.sin_port = htons(5000);
  sevr_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  
  if ( (n= connect(sockfn, (struct sockaddr*)&sevr_addr, sizeof(sevr_addr)) )<0)
  {
    printf("Connection failed %d\n", n);
    return 0;
  }
  char sendBuf[] = "i'm client\0";
  write(sockfn, sendBuf, strlen(sendBuf));
  printf("%s\n", sendBuf);
  shutdown(sockfn, SHUT_WR);
  while((n=read(sockfn, recvBuff, sizeof(recvBuff) - 1)) > 0)
  {
    recvBuff[n] = 0;
    /*  if(fputs(recvBuff, stdout) == EOF)
    {
      break;
    }*/
      printf("%s\n", recvBuff);
  }
  
  if (n < 0)
  {
    printf("read error");
  }
  close(sockfn);
}