#include <stdio.h> 
#include <dlfcn.h> 
   
int main(int argc, char **argv) { 
    void *handle; 
    void (*cosine)(void*); 
    char *error; 
   
    handle = dlopen ("/tmp/libsplitpdf.so", RTLD_LAZY); 
    if (!handle) { 
        fprintf (stderr, "%s ", dlerror()); 
    } 
   
    cosine = (void(*)(void*))dlsym(handle, "FPDF_InitLibrary"); 
    if ((error = dlerror()) != NULL)  { 
        fprintf (stderr, "%s ", error); 
    } 
    cosine(NULL);
    dlclose(handle); 
    return 0; 
} 
