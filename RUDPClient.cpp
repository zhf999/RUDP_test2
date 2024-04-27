//
// Created by hfzhou on 24-4-26.
//

#include "utils.h"
#include <iostream>
int main()
{
    int servSock = socket(PF_INET,SOCK_DGRAM,IPPROTO_RUDP);
    sockaddr_in addr;
    InitAddr(&addr, "127.0.0.1","7878");

    char fileName[30]="../data/file.html";
    char buf[4096];
    long start_time = clock();
    for(int i=0;i<CONNECT_TIMES;i++)
    {
        int res ;
        printf("Connection %d starts...\n",i);
        sendto(servSock,fileName,strlen(fileName),0,(sockaddr*)&addr,sizeof(addr));

        FILE *fp = fopen("../download/file.html","wb+");
        int len = 0;
        while((len=recvfrom(servSock,buf,RUDP_PACKET_LEN,0, nullptr, nullptr))>0)
        {
            if(strncmp(buf,"EOF",3)==0)
                break;
            fwrite(buf,1,len,fp);
        }
        fclose(fp);
    }
    close(servSock);
    long end_time = clock();
    printf("cost time:%ld\n",end_time-start_time);
    return 0;
}