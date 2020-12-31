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
struct SysParamsData
{
	unsigned int uiLostPackageResendTimes;	// 丢失数据重传请求次数，单位 - 次，sys_parameter_id = 1
	unsigned int uiPasswordRetryTimes;	// 密码重试次数，单位 - 次，sys_parameter_id = 2
	unsigned int uiTransactionSendTimeSlot;	// 交易数据上传时间间隔，单位 - 分钟，sys_parameter_id = 3
	unsigned int uiBusinessSendTimeSlot;	// 业务数据上传时间间隔，单位 - 分钟，sys_parameter_id = 4
	unsigned int uiAuditTimeSlot;		// 审计时间间隔，单位 - 分钟，sys_parameter_id = 5
	unsigned int uiSynchorizeTimeSlot;	// 时钟同步时间间隔，单位 - 分钟，sys_parameter_id = 6
	unsigned int uiSynchorizeWarningCount;	// 同步时间报警差值，单位 - 秒，sys_parameter_id = 7
	unsigned int uiSynchorizeErrorCount;	// 同步时间故障差值，单位 - 秒，sys_parameter_id = 8
	unsigned int uiAutoLogoffTimeSlot;	// 无操作自动登出时间，单位 - 分钟，sys_parameter_id = 9

	void Init() {
		// 按照数据字典定义设置初始值
		uiLostPackageResendTimes = 3;
		uiPasswordRetryTimes = 3;
		uiTransactionSendTimeSlot = 15;
		uiBusinessSendTimeSlot = 15;
		uiAuditTimeSlot = 15;
		uiSynchorizeTimeSlot = 30;
		uiSynchorizeWarningCount = 60;
		uiSynchorizeErrorCount = 300;
		uiAutoLogoffTimeSlot = 120;
	};
};

void SelectSysParams(SysParamsData& sSysParamsData)
{
	// 设置缺省值
	sSysParamsData.Init();
}
int main()
{
   SysParamsData Para;
   SelectSysParams(Para);
   printf("%d\n",Para.uiSynchorizeErrorCount);
   cout<<"2021,新年快乐"<<endl;
   return 0;
}
