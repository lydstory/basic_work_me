#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <limits.h>
#include <stdio.h>
#define CONFIG_DIR "/etc/usbs/"

struct macro {
    const char *name;
    unsigned int code;
};
#define URB_FUNCTION_SELECT_CONFIGURATION            0x0000
#define URB_FUNCTION_SELECT_INTERFACE                0x0001
#define K_V(a) {#a, a},

struct macro usb_funcs[]={
K_V( URB_FUNCTION_SELECT_CONFIGURATION           )
K_V( URB_FUNCTION_SELECT_INTERFACE               )
{0,0}}; 
const char * func2name(unsigned int func)
{
    int i;
    for(i=0;usb_funcs[i].name;i++){
        if(func==usb_funcs[i].code)
            return usb_funcs[i].name;
    }
    return "Unknown func code";
}
int main()
{
  
  printf("%s",func2name(URB_FUNCTION_SELECT_INTERFACE));
 
    
    return 0;
}
