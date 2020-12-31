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
class CAfcOpTransformTool
{
  public:
  	static void  encrypt_fromACC( const unsigned char * plaintext, int len, char * ciphertext );
		static void decrypt_fromACC( const unsigned char * ciphertext, int len, char * plaintext);
};
void CAfcOpTransformTool::encrypt_fromACC( const unsigned char * plaintext, int len, char * ciphertext )
{
	int i;
	for ( i = 0; i < len; i++ ) {
		ciphertext[ i ] = ((plaintext[ i ] - '0') + i ) % 10 + '0';
	}
	ciphertext[ len ] = '\0';
}
void CAfcOpTransformTool::decrypt_fromACC( const unsigned char * ciphertext, int len, char * plaintext)
{
	int i;
	for ( i = 0; i < len; i++ ) {
		if( ciphertext[ i ]  < ( i + 0x30 ) ) {
			plaintext[ i ] = 10 + ciphertext[ i ] - i;
		} else {
			plaintext[ i ] = ciphertext[ i ] - i;
		}
	}	
	plaintext[ len ] = '\0';
}

class CAfcOpCommonTool
{
  public:
  	/**
	* AFC内部加密算法
	* 算法描述： 将输入的每个字符格式化成其ASCII对应的四位数字，不够四位前补零
	*			 然后八个数字一组，不够八个最后补0，调用ACC的加密算法进行加密
	* 输入参数： 待加密的原文
	* 输出参数： 加密后的密文
	*/
	void AFCEncrypt(const char* chDataplain, string& strDataCipher);

	/**
	* AFC内部解密算法
	* 算法描述： 将输入的数字串八个一组，调用ACC的解密算法进行解密
	*			 然后对解密出来的数字字符串每四个一组转换成对应数字，进而转换成ACII码
	* 输入参数： 待解密的密文
	* 输出参数： 解密后的原文
	*/
	void AFCDecrypt(const string& strDataCipher, string &strDataPlain);
};


void CAfcOpCommonTool::AFCEncrypt(const char* chDataplain, string& strDataCipher)
{
	char chtmp[5];
	string strDataOri;
	for (unsigned int i = 0; i < strlen(chDataplain); i++)
	{
		sprintf(chtmp, "%04d", chDataplain[i]);
		strDataOri+=chtmp;
	}
	if (strDataOri.size() % 8 != 0)
		strDataOri+="0000";
	
	char chDataEn[9];
	for (unsigned int i = 0; i < strDataOri.size(); i+= 8)
	{
		CAfcOpTransformTool::encrypt_fromACC((unsigned char*)strDataOri.substr(i, 8).c_str(),8, chDataEn);
		strDataCipher += chDataEn;
	}
}
void CAfcOpCommonTool::AFCDecrypt(const string& strDataCipher, string &strDataPlain)
{
	unsigned int iLength = strDataCipher.length();
	//非法密文，不做处理
	if (iLength % 8 != 0)
	{
		strDataPlain = "";
		return;
	}
	char chData[9];
	string strDataOri;
	for (unsigned int i = 0; i < strDataCipher.size(); i+= 8)
	{
		CAfcOpTransformTool::decrypt_fromACC((unsigned char*)strDataCipher.substr(i, 8).c_str(),8, chData);
		strDataOri += chData;
	}
	char chTmp;
	for (unsigned int i = 0; i < strDataOri.size(); i+= 4)
	{
		chTmp = atoi(strDataOri.substr(i, 4).c_str());
		strDataPlain += chTmp;
	}
}

int main()
{
  	string strDataOri;
    string str2;
  CAfcOpCommonTool caftool;
  caftool.AFCEncrypt("2021,	unsigned char m_ucCRCFlag;",strDataOri);
  cout<<strDataOri<<endl;
 caftool.AFCDecrypt(strDataOri,str2);
  cout<<str2<<endl;
   cout<<"2021,新年快乐"<<endl;
   return 0;
}
