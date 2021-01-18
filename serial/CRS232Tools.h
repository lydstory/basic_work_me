#ifndef ZN_CRS232TOOLS_H
#define ZN_CRS232TOOLS_H
#include     <termios.h>
namespace ZN
{
class CRS232Tools
{
	protected:
          int m_fdCom;
public:
	int set_Parity(int databits, int stopbits, int parity) ;
	int closeCom() ;
	int OpenCom(const int nThisThreadType, char* pDevName, speed_t speed, int databits, int stopbits, int parity) ;
	CRS232Tools();
	~CRS232Tools();
} ;

}

#endif
