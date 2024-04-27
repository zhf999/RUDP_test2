#include <iostream>
#include "utils.h"

int main() {
    int servSock = socket(PF_INET,SOCK_DGRAM,IPPROTO_RUDP);
    sockaddr_in addr,clientAddr;
    InitAddr(&addr, nullptr,"7878");
    bind(servSock,(sockaddr *)&addr,sizeof(addr));
    socklen_t addrLen;

    char fileName[30];
    char buf[4096];
    for(int i=0;i<CONNECT_TIMES;i++)
    {
        printf("Connection %d starts...\n",i);
        int len = 0;
        len = recvfrom(servSock,fileName,30,0,(sockaddr*)&clientAddr,&addrLen);
        if(len==-1)
        {
            printf("Receive error! errno=%d\n",errno);
            continue;
        }
        fileName[len] = 0;
        FILE *fp = fopen(fileName,"rb");
        while((len=fread(buf,1,RUDP_PACKET_LEN,fp))!=0)
        {
            sendto(servSock,buf,len,0,(sockaddr*)&clientAddr,addrLen);
        }
        sendto(servSock,"EOF",3,0,(sockaddr*)&clientAddr,addrLen);
        fclose(fp);
    }
    close(servSock);
    return 0;
}
