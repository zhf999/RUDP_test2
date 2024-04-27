#include <iostream>
#include "utils.h"

int main() {
    int servSock = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
    sockaddr_in addr,clientAddr;
    InitAddr(&addr, nullptr,"7979");
    bind(servSock,(sockaddr *)&addr,sizeof(addr));
    listen(servSock,15);
    socklen_t addrLen;
    int opt = 1;
    setsockopt( servSock, SOL_SOCKET,SO_REUSEADDR, (const void *)&opt, sizeof(opt) );

    char fileName[30];
    char buf[4096];
    for(int i=0;i<CONNECT_TIMES;i++)
    {
        int res;
        printf("Connection %d starts...\n",i);
        int clientSock = accept(servSock,(sockaddr*)&clientAddr,&addrLen);
        sprintf(fileName,"../data/file.html");
        FILE *fp = fopen(fileName,"rb");
        int len = 0;
        while((len=fread(buf,1,TCP_PACKET_LEN,fp))!=0)
        {
            send(clientSock,buf,len,0);
        }
        fclose(fp);
        shutdown(clientSock,SHUT_RDWR);
        close(clientSock);
    }
    close(servSock);
    return 0;
}
