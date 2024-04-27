//
// Created by hfzhou on 24-4-25.
//
#include<unistd.h>
#include<arpa/inet.h>
#include <sys/socket.h>
#include<stdlib.h>
#include<cstring>
#ifndef RUDPWEBSERVER_UTILS_H
#define RUDPWEBSERVER_UTILS_H

#define  IPPROTO_RUDP 141
#define CONNECT_TIMES 32
#define TCP_PACKET_LEN 1024
#define RUDP_PACKET_LEN 1024

void InitAddr(sockaddr_in *addr, const char *ip, const char *port);

void InitAddr(sockaddr_in *addr, const char *ip, const char *port) {
    int iport = atoi(port);
    memset(addr,0,sizeof(addr));
    addr->sin_family = AF_INET;
    if(ip== nullptr)
        addr->sin_addr.s_addr = INADDR_ANY;
    else
        addr->sin_addr.s_addr = inet_addr(ip);
    addr->sin_port = htons(iport);
}

#endif //RUDPWEBSERVER_UTILS_H
