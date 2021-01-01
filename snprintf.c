#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <limits.h>
#include <stdio.h>
#define CONFIG_DIR "/etc/usbs/"
int main()
{
  
     FILE *fp;
    char  fname[PATH_MAX];
    char filename[40];
    strcpy(filename,"abc.txt");
    snprintf(fname, sizeof(fname), "%s%s", CONFIG_DIR,           filename);
    printf("%s\n",fname);
    printf("Hello, World!\n");
    return 0;
}
