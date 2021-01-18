#ifndef SOCKET_H
#define SOCKET_H

/*Include Area*/
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
/*#include <sys/select.h>     */
#include <fcntl.h>
#include <netdb.h>
#include <sys/wait.h>
#include <stdarg.h>
#include <sys/stat.h>
#include "Dbg.h"
extern int gi_DEBUG;

#ifdef __cplusplus
extern "C"   
{
#endif

void Release_Skt();

int BuildSktSvr(char *IPAddr, int ServPort);

int SktAccept(int lsn_skt, int timeout, char *clnt_ip);

int ConnSvr(char *ipaddr, int port);

int SktRcv(int fd, char *msgbuf, int size, int timeout);

int SktSnd(int fd, char *msgbuf, int size, int timeout);

int FlushSkt(int fd);
#ifdef __cplusplus
}
#endif

#endif
