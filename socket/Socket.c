 

#include <stdio.h>
#include <errno.h>

#include "Socket.h"

/*Define Area*/
/*#define AIX*/
/*#define LINUX*/




/******************************************************************************
 函数：BuildSktSvr
 功能：建立服务端
 输入：ip地址，端口
 输出：无
 返回：lsn_skt，-1错误
 
 	  
 ******************************************************************************/
int BuildSktSvr(char *IPAddr, int ServPort)
{
	int lsn_skt;
	struct sockaddr_in svr_addr;
#ifdef AIX
	unsigned long addr_len;
#elif defined(SCO)
	int addr_len;
#elif defined(UNIXWARE) || defined(LINUX)
	unsigned int addr_len;
#else
	unsigned int addr_len;
#endif
	
	struct linger optval;
	int reuse_flag;
	struct hostent *HostEnt;

	int ret;
	
	if( ( lsn_skt=socket(AF_INET,SOCK_STREAM,0) )<0 )
	{
		ERR("BuildSktSvr: Failed to create listening socket!");
		return -1;
	}
	
	memset(&optval,0,sizeof(optval));
	optval.l_onoff = 1;
	optval.l_linger = 0;
	setsockopt(lsn_skt,SOL_SOCKET,SO_LINGER,&optval,sizeof(optval));
	reuse_flag = 1;
	setsockopt(lsn_skt,SOL_SOCKET,SO_REUSEADDR,&reuse_flag,sizeof(reuse_flag));

	/*初始化结构体，并绑定ServPort端口*/	
	memset(&svr_addr,0,sizeof(svr_addr));
	svr_addr.sin_family=AF_INET;
	if( strlen(IPAddr)!=0 ) svr_addr.sin_addr.s_addr=inet_addr(IPAddr);
	else svr_addr.sin_addr.s_addr = INADDR_ANY;
	svr_addr.sin_port=htons(ServPort);
	addr_len=sizeof(struct sockaddr);

	/*绑定套接口*/
	if( bind(lsn_skt,(struct sockaddr*)&svr_addr,addr_len)<0 )
	{
		close(lsn_skt);
		ERR("BuildSktSvr: Failed to complete socket bind!");
		return -1;
	}

	/*创建监听套接口*/
	if( listen(lsn_skt, 10)<0 )
	{
		close(lsn_skt);
		ERR("BuildSktSvr: Failed to complete socket listen!");
		return -1;
	}
	
	return lsn_skt;
}


/******************************************************************************
 函数：SktAccept
 功能：
 输入：
 输出：
 返回：
 
 	  
 ******************************************************************************/
int SktAccept(int lsn_skt, int timeout, char *clnt_ip)
{
	int accept_fd;
	fd_set s_set;
	struct	timeval tmout;
	struct	timeval *ptmout;
	struct sockaddr_in clnt_addr;
#ifdef AIX
	unsigned long addr_len;
#elif defined(SCO)
	int addr_len;
#elif defined(UNIXWARE) || defined(LINUX)
	unsigned int addr_len;
#else
	unsigned int addr_len;
#endif
	
	addr_len=sizeof(struct sockaddr);
	if( (accept_fd=accept(lsn_skt, (struct sockaddr*)&clnt_addr, &addr_len))<0 )
	{
		if(errno==EINTR) return -2;
		else
		{
			close(lsn_skt);
			ERR("SktAccept: Failed to accept client socket!");
			return -1;
		}
	}
	
	return accept_fd;
}


/******************************************************************************
 函数：ConnSvr
 功能：连接服务器
 输入：ipaddr-ip地址，port-端口
 输出：无
 返回：-1 错误，
 
 ******************************************************************************/
int ConnSvr(char *ipaddr, int port)
{
	struct sockaddr_in sinsock;
	int fd;
	int rcvbufsize;
	
	if( ( fd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP) )<0 )
	{
		ERR("ConnSvr: Failed to create client socket!");
		return -1;
	}
		
	bzero((char *)&sinsock, sizeof(sinsock));
	sinsock.sin_family=AF_INET;
	sinsock.sin_port=htons(port);
	sinsock.sin_addr.s_addr=inet_addr(ipaddr);
	
	if(connect(fd, (struct sockaddr *)&sinsock, sizeof(sinsock))<0)
	{
		close(fd);
		ERR("ConnSvr: Failed to connect server(%s:%d)!", ipaddr, port);
		return -1;
	}

	return fd;
}

/******************************************************************************
 函数：SktRcv
 功能：Receive message from peer
 输入：int fd, int size, int timeout
 输出：char *msgbuf
 返回：1-Success;  0-No data;  -1-Fail;  -2-Timeout
 
 ******************************************************************************/
int SktRcv(int fd, char *msgbuf, int size, int timeout)
{
	int nleft;
	int nrecved;
	char *ptr;

	if (fd < 0)
		return -1;
	
	ptr = msgbuf;
	nleft = size;
	while( nleft > 0 )
	{
		nrecved = recv(fd, ptr, nleft, 0);
		if( nrecved < 0 )
		{
			if( errno == EINTR )
				nrecved = 0;
			else
			{
				ERR("SktRcv: nrecved=%d",nrecved);
				return -1;
			}
		}else if( nrecved == 0 )
			break;
		nleft -= nrecved;
		ptr += nrecved;
	}

	DBG("SktRcv: rcv len=%d",size-nleft);
	
	return (size-nleft);

}
/******************************************************************************
 函数：SktSnd
 功能：socket发送数据
 输入：int fd, char *msgbuf, int size, 
 输出：无
 返回：1-Success;  0-No data;  -1-Fail;  -2-Timeout
 
 ******************************************************************************/
int SktSnd(int fd, char *msgbuf, int size, int timeout)
{
	int nleft;
	int nsended;
	const char *ptr;

	if (fd < 0)
		return -1;
	
	ptr = msgbuf;
	nleft = size;
	while( nleft >0 )
	{
		nsended = send(fd, ptr, nleft, 0);
		if( nsended <= 0 )
		{
			if( errno == EINTR )
				nsended = 0;
			else
			{
				ERR("SktSnd: nsended=%d",nsended);
				return -1;
			}
		}
		nleft -= nsended;
		ptr += nsended;
	}

	DBG("SktSnd: send len=%d",size);
	
	return size;
}


