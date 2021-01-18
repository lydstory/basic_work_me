#include     <stdio.h>      /*标准输入输出定义*/
#include     <stdlib.h>     /*标准函数库定义*/
#include     <unistd.h>     /*Unix 标准函数定义*/
#include     <sys/types.h>  
#include     <sys/stat.h>   
#include     <fcntl.h>      /*文件控制定义*/
#include     <termios.h>    /*PPSIX 终端控制定义*/
#include     <errno.h>      /*错误号定义*/
#include "deftype.h"
#include "CRS232Tools.h"
#include "znErrorModNo.h"
using namespace ZN;
namespace ZN {
// ===================================================================================================
//	CRS232Tools
// ===================================================================================================
int CRS232Tools::set_Parity(int databits, int stopbits, int parity)
{
	struct termios options;
	if(tcgetattr( m_fdCom, &options) !=  0)  {
		perror("SetupSerial 1"); 
		return ZN_ERROR ; 
	}
	
	options.c_cflag &= ~CSIZE;
	switch (databits) {
		case 7: options.c_cflag |= CS7;	break;
		case 8: options.c_cflag |= CS8 ;	break;
		default : 
			 
			return ZN_ERROR ;
	}
	
	options.c_oflag  &= ~OPOST;   // Output
	options.c_lflag  &= ~(ICANON | ECHO | ECHOE | ISIG);  // Input
	options.c_cflag |= CLOCAL | CREAD;
	options.c_iflag |= INPCK; // Set input parity option
	options.c_iflag &= ~(BRKINT | ICRNL | ISTRIP | IXON);
	switch (parity) {
		case 'n': case 'N':
			options.c_cflag &= ~PARENB;   
			options.c_iflag &= ~INPCK;     // Enable parity checking 
			break;
		case 'o': case 'O':
			options.c_cflag |= (PARODD | PARENB);
			break;
		case 'e': case 'E':
			options.c_cflag |= PARENB;     // Enable parity 
			options.c_cflag &= ~PARODD;   
			break;
		case 'S': case 's':  //as no parity
			options.c_cflag &= ~PARENB;
			options.c_cflag &= ~CSTOPB;
			break;
		default:
			 
			return ZN_ERROR ;
	}

	switch (stopbits) {
  		case 1: options.c_cflag &= ~CSTOPB; break;
		case 2: options.c_cflag |= CSTOPB;   break;
		default: 
			 
			return ZN_ERROR ;
	}

    options.c_cc[VINTR] = 0; /* Ctrl-c */
    options.c_cc[VQUIT] = 0; /* Ctrl-\ */
    options.c_cc[VERASE] = 0; /* del */
    options.c_cc[VKILL] = 0; /* @ */
    options.c_cc[VEOF] = 0; /* Ctrl-d */
    options.c_cc[VTIME] = 0; /* inter-character timer, timeout VTIME*0.1 */
    options.c_cc[VMIN] = 0; /* blocking read until VMIN character arrives */
    options.c_cc[VSWTC] = 0; /* '\0' */
    options.c_cc[VSTART] = 0; /* Ctrl-q */
    options.c_cc[VSTOP] = 0; /* Ctrl-s */
    options.c_cc[VSUSP] = 0; /* Ctrl-z */
    options.c_cc[VEOL] = 0; /* '\0' */
    options.c_cc[VREPRINT] = 0; /* Ctrl-r */
    options.c_cc[VDISCARD] = 0; /* Ctrl-u */
    options.c_cc[VWERASE] = 0; /* Ctrl-w */
    options.c_cc[VLNEXT] = 0; /* Ctrl-v */
    options.c_cc[VEOL2] = 0; /* '\0' */

	tcflush(m_fdCom, TCIFLUSH) ; // Update the options and do it NOW 
	if (tcsetattr(m_fdCom, TCSANOW, &options) != 0) { 
		 
		return ZN_ERROR ; 
	}
	return ZN_OK ;
}

int CRS232Tools::closeCom()
{
	return close(m_fdCom) ;
}

int CRS232Tools::OpenCom(const int nThisThreadType, char* pDevName, speed_t speed, int databits, int stopbits, int parity) 
{
	m_fdCom = ZN_INVALIDATE_FD;
	for(int nRetry = 0; nRetry < ZN_SOCKET_RETRY_TIME; nRetry++) {
		if(m_fdCom >= 0) {
			// because it is retry, close old
			if (closeCom() < 0) 
				 
			sleep(ZN_CLI_SOCKET_CONN_INTERVAL) ;
		}

		// O_RDWR | O_NOCTTY | O_NONBLOCK
		if((m_fdCom = open(pDevName, O_RDWR | O_NOCTTY | O_NONBLOCK )) < 0) {
			 
			return (-1) * ZN_ERROR_SOCKET_FD ; 
		}

		struct  termios Opt;
		tcgetattr(m_fdCom, &Opt);
		cfsetispeed(&Opt, speed);    
		cfsetospeed(&Opt, speed);
		tcsetattr(m_fdCom, TCSANOW, &Opt);
		if (set_Parity(databits, stopbits, parity) != ZN_OK) { 
			return 0 ;  
		}
		tcflush(m_fdCom, TCIFLUSH);
		return m_fdCom ; 
	}
	if(m_fdCom >= 0) {
		// because it is retry, close old
		if (close(m_fdCom) < 0) 
			 
		sleep(ZN_CLI_SOCKET_CONN_INTERVAL) ;
		tcflush(m_fdCom, TCIFLUSH);
	}
	return (-1) * ZN_ERROR_SOCKET_FD ;   // try SOCKET_RETRY_TIME times, error happen 
}

CRS232Tools::CRS232Tools()
{
	m_fdCom = ZN_INVALIDATE_FD ; 
}

CRS232Tools::~CRS232Tools()
{
	closeCom();
}


};
