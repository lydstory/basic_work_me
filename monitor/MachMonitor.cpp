#include "MachMonitor.h"
#include <dlfcn.h>
MachMonitor::MachMonitor(void)
{
}

MachMonitor::~MachMonitor(void)
{
}

bool MachMonitor::InitCallBack()
{
     void *handle;
     handle = dlopen("libMachStatus.so",RTLD_LAZY);
     if(!handle)
       {
           return false;

        }
      
        return true;
}
