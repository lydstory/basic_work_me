#ifndef ZN_DEFTYPE_H
#define ZN_DEFTYPE_H
namespace ZN
{
static const short ZN_INVALIDATE_FD = -1;
static const int ZN_SOCKET_RETRY_TIME	  = 3;
static const int ZN_CLI_SOCKET_CONN_RETRY_TIMES = 30;// seconds: retry this times
static const int ZN_CLI_SOCKET_CONN_INTERVAL = 1; // seconds: after this time, retry again
}

#endif
