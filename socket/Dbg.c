 

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <time.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <ctype.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/resource.h> 

#include "Dbg.h"

//#define PRINT

/*生成文件日志信息，参数格式和使用同printf函数*/
/******************************************************************************
 函数：DBG
 功能：
 输入：
 输出：
 返回：
 
 	  
 ******************************************************************************/
void DBG(const char* format, ...)
{
	va_list ap;
	FILE* fplog = NULL;
	char filename[256];
	struct tm* timebuf;
	time_t curtime = time(NULL);
	timebuf = localtime(&curtime);

#ifdef PRINT
	/*输出到错误输出中*/
	fprintf(stdout, "[%04d-%02d-%02d %02d:%02d:%02d]<PID=%d>", 
		timebuf->tm_year+1900, timebuf->tm_mon+1, timebuf->tm_mday,
		timebuf->tm_hour, timebuf->tm_min, timebuf->tm_sec, getpid());
	va_start(ap, format);
	vfprintf(stdout, format, ap);
	va_end(ap);
	fputc('\n', stdout);
	fflush(stdout);
#endif
	
	/*取得日志文件名，文件名格式为${LOG_PATH}/agent_YYYYMMDD.log*/
	sprintf(filename, "cmdTunnel%04d%02d%02d.log",timebuf->tm_year+1900, timebuf->tm_mon+1, timebuf->tm_mday);
	fplog = fopen(filename, "at");
	if (fplog == NULL)
		return;
	/*填写日志内容*/
	fprintf(fplog, "[%02d:%02d:%02d]<PID=%d>", 
		timebuf->tm_hour, timebuf->tm_min, timebuf->tm_sec, getpid());
	va_start(ap, format);
	vfprintf(fplog, format, ap);
	va_end(ap);
	fputc('\n', fplog);
	fflush(fplog);
	fclose(fplog);
}


/******************************************************************************
 函数：ERR
 功能：
 输入：
 输出：
 返回：
 
 	  
 ******************************************************************************/
void ERR(const char* format, ...)
{
	va_list ap;
	FILE* fplog = NULL;
	char filename[256];
	struct tm* timebuf;
	time_t curtime = time(NULL);
	timebuf = localtime(&curtime);

#ifdef PRINT
	/*输出到错误输出中*/
	fprintf(stdout, "[%04d-%02d-%02d %02d:%02d:%02d]<PID=%d>", 
		timebuf->tm_year+1900, timebuf->tm_mon+1, timebuf->tm_mday,
		timebuf->tm_hour, timebuf->tm_min, timebuf->tm_sec, getpid());
	va_start(ap, format);
	vfprintf(stdout, format, ap);
	va_end(ap);
	fputc('\n', stdout);
	fflush(stdout);
#endif
	
	/*取得日志文件名，文件名格式为${LOG_PATH}/agent_YYYYMMDD.log*/
	sprintf(filename, "cmdTunnel%04d%02d%02d.log",timebuf->tm_year+1900, timebuf->tm_mon+1, timebuf->tm_mday);
	fplog = fopen(filename, "at");
	if (fplog == NULL)
		return;
	/*填写日志内容*/
	fprintf(fplog, "[E] [%02d:%02d:%02d]<PID=%d>", 
		timebuf->tm_hour, timebuf->tm_min, timebuf->tm_sec, getpid());
	va_start(ap, format);
	vfprintf(fplog, format, ap);
	va_end(ap);
	fputc('\n', fplog);
	fflush(fplog);
	fclose(fplog);
}

