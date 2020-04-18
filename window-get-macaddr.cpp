#include <stdio.h>　
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <windows.h>
#include <vector>
#include <ctime>
#include <io.h>
#include "iptypes.h"
#include "shlobj.h" 
using namespace std;
typedef DWORD (__stdcall *GETADAPTERINFO)(PIP_ADAPTER_INFO,PULONG);
/*获取物理地址*/
bool GetMacAddress(string& addr)
{
	PIP_ADAPTER_INFO pAdapterInfo;
	PIP_ADAPTER_INFO pAdapter = NULL;
	DWORD retVal = 0;
	ULONG bufLen = sizeof (IP_ADAPTER_INFO);
	pAdapterInfo = (IP_ADAPTER_INFO *) malloc(sizeof (IP_ADAPTER_INFO));
	if (pAdapterInfo == NULL) 
	{
		return false;
	}
	HINSTANCE hIphlpapi = LoadLibrary("iphlpapi.dll");
	GETADAPTERINFO pGetAdaptersInfo = (GETADAPTERINFO)GetProcAddress(hIphlpapi,"GetAdaptersInfo");
	if (pGetAdaptersInfo(pAdapterInfo, &bufLen) == ERROR_BUFFER_OVERFLOW) 
	{
		free(pAdapterInfo);
		pAdapterInfo = (IP_ADAPTER_INFO *) malloc(bufLen);
		if (pAdapterInfo == NULL)
		{
			return false;
		}
	}
	if (pGetAdaptersInfo(pAdapterInfo, &bufLen) == NO_ERROR) 
	{
		pAdapter = pAdapterInfo;
		if(pAdapter)
		{
			char temp[10];
			string tempString;
			for (int i = 0; i < pAdapter->AddressLength; i++) 
			{
				sprintf(temp, "%.2X", (int) pAdapter->Address[i]);
				tempString.assign(temp);
				addr.append(tempString);
			}		
		}
	} 
	else
	{
		free(pAdapterInfo);
		return false;
	}
	free(pAdapterInfo);
	FreeLibrary(hIphlpapi);
	return true;
}
int main()
{
	string addr="";                                    
	if(!GetMacAddress(addr))
	{
		return 0;
	}
	cout<<"Mac: "<<addr<<endl;
	system("PAUSE");
	return 1;
}
