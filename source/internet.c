#define _BSD_SOURCE
#include <unistd.h>
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   internet.c
 * Author: michael.oriley
 *
 * Created on January 26, 2016, 11:46 AM
 */

#include <stdio.h>
#include <stdlib.h>

#include </home/omikey/Desktop/libctru/include/netdb.h>
#include </home/omikey/Desktop/libctru/include/netinet/in.h>

#include <string.h>

#include <sys/types.h>
#include </home/omikey/Desktop/libctru/include/sys/socket.h>
#include <unistd.h>
#include <malloc.h>
#include </home/omikey/Desktop/libctru/include/arpa/inet.h>
#include <fcntl.h>
#include </home/omikey/Desktop/libctru/include/3ds.h>
#include <setjmp.h>
#include <assert.h>
#include "structures.h"
/*
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <netdb.h>
#include <unistd.h>

#include <malloc.h>
//#include <arpa/inet.h>
#include <fcntl.h>
//////////////////
//#include <arpa/inet.h>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <malloc.h>
//#include <netdb.h>
//#include <netinet/in.h>
//#include <poll.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <sys/socket.h>
#include <sys/stat.h>
#include <time.h>
//#include <arpa/inet.h>
#include </home/omikey/Desktop/libctru/include/3ds/result.h>       // To be removed when dkA patch to newlib is applied
#include </home/omikey/Desktop/libctru/include/3ds/services/soc.h>
#include <stdio.h>
#include <stdlib.h>
#include "websocket.h"


static const char *inet_ntop4(const void *restrict src, char *restrict dst, socklen_t size)
{
	const u8 * ip = src;
	if(size < INET_ADDRSTRLEN)
	{
		errno = ENOSPC;
		return NULL;
	}
	snprintf(dst,size,"%hhu.%hhu.%hhu.%hhu",ip[0], ip[1], ip[2], ip[3]);
	return dst;
}


const char *inet_ntop(int af, const void *restrict src, char *restrict dst, socklen_t size)
{
	if(af == AF_INET)
	{
		return inet_ntop4(src,dst,size);
	}
	// only support IPv4
	errno = EAFNOSUPPORT;
	return NULL;
}


char tmpBuffer[512];
const int commandPort=5000;
int dataPort=5001;
char currentPath[4096];
u32 currentIP;
int listenfd;



int internet_access(char* str)
{

    //    void *memalign(size_t alignment, size_t size);

    fsInit();
	//printf("fsInit %08X\n", (unsigned int)ret);
	//printf("FSUSER_OpenArchive %08X\n", (unsigned int)ret);

    socInit((u32*)memalign(0x1000, 0x100000), 0x100000);
	//printf("SOC_Initialize %08X\n", (unsigned int)ret);

    sprintf(currentPath, "/");

    currentIP=(u32)gethostid();

    listenfd=-1;
   
    wsContext_t *ctx = NULL;
    ctx = wsContextNew(NULL);
//    if (global.t=0)
//    {
//        global.t++;
        //global.chat = "context created";
//        return -1;
//    }
    int fd = 0;
    if (global.first == 0)
    {
        
        fd = global.t;
        sendUtf8Data(global.t,str,strlen(str));
    }
    else
    {
        fd = wsCreateConnection(ctx,"www.japanfour.com");
    }    
//    global.socket = fd;
//    if (global.t=1)
//    {
//        global.t++;
        global.t = fd;
//        return -1;
//    }
//    char buff[1024*1024];
//    while(1)
//    {
//        int len = recvData(ctx,buff, 1*1024*1024);
//        //int len = read(fd, buff, 1024*1024);
//        if(len)
//        {
//            //printf("recieved: %s\n", buff);
//        }
//
//        if(len < 0)
//        {
//            //printf("recv nada\n");
//           break;
//        }
//    }
 //   wsContextFree(ctx);
//    return 1;
	return -1;
}

