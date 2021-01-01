#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <limits.h>
#include <stdio.h>

#ifdef WIN32
#define SEP '\\'
#else
#define SEP '/'
#endif
/*
 * splitPath()
 *  path, the string to be split
 *  dirname, save dirname
 *  dnsize, dirname memory size
 *  basename, save filename
 *  bnsize, basename memory size
 *
 *  return 0,success; 1,error
 * */
size_t SplitPath(const char* path, char* dirname, size_t *dnsize,  char* basename, size_t *bnsize)
{
    char* last_slash = NULL;
    size_t dirLen = 0, nameLen=0;
    size_t pathLen = 0; 

    if (path == NULL)
      return dirLen;

    pathLen = strlen(path);
    last_slash = strrchr((char*)path, SEP);
    if (last_slash == NULL)
	{
        // there is no '/'???, So the path is a file name 
        dirLen = 0;
        nameLen = pathLen;
	}
    else if(last_slash == path && pathLen >= 1)
    {
        // So it's a file in the root directory
        dirLen = 1;
        nameLen = pathLen-1;
    }
    else if(last_slash-path+1 == (int)pathLen)
    {
        // It's a directory
        dirLen = pathLen;
        nameLen = 0;
    }
    else{
        dirLen = last_slash - path;
        nameLen = pathLen-dirLen-1;
    }

    /* save result */
    if(dirname)
    { 
        if(*dnsize <= dirLen)
        {
            return 1;
           
        }
        memcpy(dirname, path, dirLen);
        *dnsize = dirLen;
    }
    if(basename && nameLen > 0)
    {
        if(*bnsize <= nameLen)
        {
            return 1;
           
        }
        memcpy(basename, last_slash+1, *bnsize);
        *bnsize = nameLen;
    }
    
    return 0;
}
/*
 * basename()
 *  path, the strin gto be split
 *  basename, save filename
 *  size, basename memory size
 *
 *  return
 * */
size_t Basename(const char* path, char* basename, size_t *size)
{
    size_t offset = 0;
    if(basename == NULL || size == 0)
    {
        return -1;
    }
    offset = SplitPath(path, NULL, 0, basename, size);
    if(offset>0)
      offset += 1;

    return offset; 
}

/*
 * dirname()
 *  path, the string to be split
 *  dirname, save filename
 *  size, dirname memory size 
 *
 *  return
 * */
size_t Dirname(const char* path, char* dirname, size_t *size)
{
    if(dirname == NULL || size == 0)
    {
        return -1;
    }
    return SplitPath(path, dirname, size, NULL, 0); 
}
/*
 * pathJoin(char* pathname, int size, const char* name1, ...)
 *
 * pathname, save the path string
 * size, pathname memory size
 * name1,  
 * ..., variable parameters
 *
 * */
size_t PathJoin(char* pathname, int size, const char* name1, ...)
{
    int pos = 0;
    va_list va;
    char *name = NULL;

    if(name1 == NULL || strlen(name1)==0)
      return pos;
    
    snprintf(pathname, size-pos, "%s", name1);
    pos += strlen(name1);

    va_start(va, name1);
    while(1)
    {
        name = va_arg(va, char*);
        if(NULL==name || strcmp(name, "") == 0) break;
        if(PATH_MAX < pos+strlen(name)) break;
        snprintf(pathname+pos, size-pos, "%c%s", SEP, name);
        pos += strlen(name)+1;
    }
    va_end(va);

    return pos < size ? pos : size;
}
int main()
{
  
   char path[40];
   char name[40];
  size_t rs = 40;
  Basename("/home/lyd/uuu/aa.txt",path,&rs);
     size_t rs2 = 40;
  Dirname("/home/ljk/jkl/aa.txt",name,&rs2);
  printf("%s",path);
  printf("\n%s\n",name);
   printf("Hello, World!\n");
   return 0;
}
