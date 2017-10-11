#include <sys/errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <time.h>
#include <pthread.h>
#include <errno.h>
#include <uuid.h>

int main(int argc, char *argv[])
{
    int fd,ret=0;
    fd=socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in addr;
    bzero(&addr,sizeof(addr));
    inet_pton(AF_INET,"120.55.238.29",(struct sockaddr*)&addr.sin_addr.s_addr);
    addr.sin_family=AF_INET;
    addr.sin_port=htons(80);
     printf("Start connect ...\n");
    ret= connect(fd,(struct sockaddr*)&addr,sizeof(addr));
    if(ret<0)
    {
        perror("connetc error");
        return 0;
    }
    char buff[2048]={0};
    printf("Start recv...\n");
    recv(fd,buff,sizeof(buff),0);
    printf("%s",buff);
    close(fd);

    return 0;
}
