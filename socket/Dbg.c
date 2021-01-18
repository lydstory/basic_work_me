 

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

/*�����ļ���־��Ϣ��������ʽ��ʹ��ͬprintf����*/
/******************************************************************************
 ������DBG
 ���ܣ�
 ���룺
 �����
 ���أ�
 
 	  
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
	/*��������������*/
	fprintf(stdout, "[%04d-%02d-%02d %02d:%02d:%02d]<PID=%d>", 
		timebuf->tm_year+1900, timebuf->tm_mon+1, timebuf->tm_mday,
		timebuf->tm_hour, timebuf->tm_min, timebuf->tm_sec, getpid());
	va_start(ap, format);
	vfprintf(stdout, format, ap);
	va_end(ap);
	fputc('\n', stdout);
	fflush(stdout);
#endif
	
	/*ȡ����־�ļ������ļ�����ʽΪ${LOG_PATH}/agent_YYYYMMDD.log*/
	sprintf(filename, "cmdTunnel%04d%02d%02d.log",timebuf->tm_year+1900, timebuf->tm_mon+1, timebuf->tm_mday);
	fplog = fopen(filename, "at");
	if (fplog == NULL)
		return;
	/*��д��־����*/
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
 ������ERR
 ���ܣ�
 ���룺
 �����
 ���أ�
 
 	  
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
	/*��������������*/
	fprintf(stdout, "[%04d-%02d-%02d %02d:%02d:%02d]<PID=%d>", 
		timebuf->tm_year+1900, timebuf->tm_mon+1, timebuf->tm_mday,
		timebuf->tm_hour, timebuf->tm_min, timebuf->tm_sec, getpid());
	va_start(ap, format);
	vfprintf(stdout, format, ap);
	va_end(ap);
	fputc('\n', stdout);
	fflush(stdout);
#endif
	
	/*ȡ����־�ļ������ļ�����ʽΪ${LOG_PATH}/agent_YYYYMMDD.log*/
	sprintf(filename, "cmdTunnel%04d%02d%02d.log",timebuf->tm_year+1900, timebuf->tm_mon+1, timebuf->tm_mday);
	fplog = fopen(filename, "at");
	if (fplog == NULL)
		return;
	/*��д��־����*/
	fprintf(fplog, "[E] [%02d:%02d:%02d]<PID=%d>", 
		timebuf->tm_hour, timebuf->tm_min, timebuf->tm_sec, getpid());
	va_start(ap, format);
	vfprintf(fplog, format, ap);
	va_end(ap);
	fputc('\n', fplog);
	fflush(fplog);
	fclose(fplog);
}

