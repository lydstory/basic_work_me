#include <memory.h>
 
void GetFileName(char *path,char *filename)
{
	char 	*ptr = NULL;
	ptr = strrchr(path,'/');
	if (!ptr)
		return;
	memcpy(filename,ptr+1,strlen(ptr+1));
}
#include <string.h>
static int cutString(char *buffer)
{
	char    *ptr;
	char    tmp[256] = {0};
	if (NULL == (ptr = strchr(buffer,','))){
		ptr = strchr(buffer,'}');
	}   
	if (!ptr)
		return -1; 
	memcpy(tmp,buffer,ptr-buffer);
	memset(buffer,0,strlen(buffer));
	strcpy(buffer,tmp);
	return strlen(buffer);
}
int main()
{
  char paht[256];
  strcpy(paht,"/home,/abc/dd}.txt");
  char name[40];
  cutString(paht);
  printf("%s\n",paht);
  return 0;
}
