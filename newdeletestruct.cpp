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
 //定义表 PACKAGE_SEND_AUDIT 的结构体
typedef struct{
	double msg_code;
	int package_split_number;
	char file_name[256];
	double file_length;
	char send_package_id[29];
	int send_flag;
	char audit_ntid[33];
	int audit_flag;
	char receive_date[9];
}package_send_audit_t;

int upload_package_send_audit(char *database,package_send_audit_t *address,package_send_audit_t *p_package_send_audit,double memory_length,int *deal_count,double *leaving_count)
{
  return 0;
}
int main()
{
	int iMaxRecord = 0;
	iMaxRecord = 1000;  
  	double dMemSize = 0;
	package_send_audit_t* pResult = NULL;
  
  pResult = new package_send_audit_t[iMaxRecord];
		dMemSize = iMaxRecord * sizeof(package_send_audit_t);
  	if(pResult != NULL)
	{
  }
   
	if(NULL != pResult)
		delete[] pResult;

    cout<<"2021,新年快乐"<<endl;
   return 0;
}
