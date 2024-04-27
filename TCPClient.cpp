//
// Created by hfzhou on 24-4-25.
//
#include "utils.h"
#include <iostream>
int main()
{
    sockaddr_in addr;
    InitAddr(&addr, "127.0.0.1","7979");

    char fileName[30];
    char buf[4096];
    long start_time = clock();
    for(int i=0;i<CONNECT_TIMES;i++)
    {
        int res ;
        printf("Connection %d starts...\n",i);
        int servSock = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
        res = connect(servSock,(sockaddr *)&addr,sizeof(addr));
        if(res!=0)
        {
            printf("Connect failed! errno=%d\n",errno);
            continue;
        }
        sprintf(fileName,"../download/file.html");
        FILE *fp = fopen(fileName,"wb+");
        int len = 0;
        while((len=recv(servSock,buf,TCP_PACKET_LEN,0))>0)
        {
            fwrite(buf,1,len,fp);
        }
        fclose(fp);
        shutdown(servSock,SHUT_RDWR);
        close(servSock);
    }
    long end_time = clock();
    printf("cost time:%ld\n",end_time-start_time);
    return 0;
}