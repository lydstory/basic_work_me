#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <stdbool.h>

#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>

#include <fstream>
#include <iostream>
using namespace std;
static const unsigned short	DEVCTRL_POWEROFF				= 0x0101;	//电源关闭
static const unsigned short	DEVCTRL_SLEEP					= 0x0105;	//睡眠模式
bool InsertSleCeaseCmd(unsigned short usAfcCtrlCmd)
 {
	int iAfcCtrlCmd = 0;
	switch(usAfcCtrlCmd)
	{
	case DEVCTRL_POWEROFF:
		iAfcCtrlCmd = 1;		
		break;
	case DEVCTRL_SLEEP:
		iAfcCtrlCmd = 2;
		break;
	default:
		break;
	}
	if(iAfcCtrlCmd == 0)
	{
    return false;
  }
  return true;
 }
int main()
{
   if(InsertSleCeaseCmd(DEVCTRL_POWEROFF))
    cout<<"2021,新年快乐"<<endl;
   return 0;
}
