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
class CAfcOpCommonTool
{
  public:
  	bool HexStr2UC(const char* bufStr, unsigned char& ucValue);

};

bool  CAfcOpCommonTool::HexStr2UC(const char* bufStr, unsigned char& ucValue)
{
	ucValue = 0;
	// 准备转换缓冲区
	static char buf[3], cTmp; memset((void*)buf, 0, 3);
	size_t sizeStr = strlen(bufStr);
	if(sizeStr < 1)
		return false;
	if(sizeStr == 1){
		buf[0] = '0'; buf[1] = bufStr[0];
	}
	else
		memcpy((void*)buf, (void*)bufStr, 2);
	// 转换
	for(int i=0; i<2; i++){
		cTmp = buf[i];
		ucValue = ucValue * 16;
		if(cTmp >= '0' && cTmp <= '9')
			ucValue = ucValue + (unsigned char)(cTmp - '0');
		else if(cTmp >= 'a' && cTmp <= 'f')
			ucValue = ucValue + (unsigned char)(cTmp - 'a' + 10);
		else if(cTmp >= 'A' && cTmp <= 'F')
			ucValue = ucValue + (unsigned char)(cTmp - 'A' + 10);
		else
			return false;
	}
	return true;
}

int main()
{
  unsigned char ucLineID = 0;
  string strLinenId = "1";
  char m_chCurrentStationID[9];
  CAfcOpCommonTool gclOpCommonTool;
  	gclOpCommonTool.HexStr2UC(strLinenId.c_str(), ucLineID);
  sprintf(m_chCurrentStationID, "%2x",ucLineID, ucLineID);
  cout<<m_chCurrentStationID<<endl;
 
   return 0;
}
