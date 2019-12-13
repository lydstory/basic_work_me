#include "fpdfsplit.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <list>
#include <string>
#include <utility>
#include "fpdfsdk/include/fpdf_dataavail.h"
#include "fpdfsdk/include/fpdf_ext.h"
#include "fpdfsdk/include/fpdfformfill.h"
#include "fpdfsdk/include/fpdftext.h"
#include "fpdfsdk/include/fpdfview.h"
#include "fpdfsdk/include/fpdfedit.h"
#include "fpdfsdk/include/fpdfsave.h"
#include "fpdfsdk/include/fpdfppo.h"
extern "C" {
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
}
struct PdfToFdWriter : FPDF_FILEWRITE {
    int dstFd;
};

static bool writeAllBytes(const int fd, const void *buffer, const size_t byteCount) {
    char *writeBuffer = static_cast<char *>(const_cast<void *>(buffer));
    size_t remainingBytes = byteCount;
    while (remainingBytes > 0) {
        ssize_t writtenByteCount = write(fd, writeBuffer, remainingBytes);
        if (writtenByteCount == -1) {
             return false;
        }
        remainingBytes -= writtenByteCount;
        writeBuffer += writtenByteCount;
    }
    return true;
}
static int writeBlock(FPDF_FILEWRITE* owner, const void* buffer, unsigned long size) {
    const PdfToFdWriter* writer = reinterpret_cast<PdfToFdWriter*>(owner);
    const bool success = writeAllBytes(writer->dstFd, buffer, size);
    if (success < 0) {
        return 0;
    }
    return 1;
}
#include <stdio.h>
#include <fcntl.h>
#include <iostream>
#include <string>
using namespace std;
DLLEXPORT FPDF_BOOL STDCALL FPDF_Split(FPDF_STRING SourPdf,FPDF_STRING DestPdf,FPDF_BOOL PageNum)
{
	 int splitnum = 0;
	 FPDF_InitLibrary(NULL);
	 FPDF_DOCUMENT doc;
   string inpdf =SourPdf;
   string outpdf = DestPdf;
   splitnum = PageNum;
 doc = FPDF_LoadDocument(inpdf.c_str(),NULL);
	 int numPages = FPDF_GetPageCount(doc);
	 int pagesplit = splitnum;
	 int pagesize= splitnum;
	 int nowpage = 1;
	 int ipagesize = splitnum;
	 int j = 0;
	 std::cout<<"pagge is"<<numPages<<std::endl;
	 for (int i = 0; i < numPages; i += ipagesize) {
		 nowpage = nowpage;
		 if(i + ipagesize > numPages)
			 pagesize = numPages+1;
		 else
		 pagesize = nowpage + pagesplit;


 		 FPDF_DOCUMENT outdoc;
		 outdoc = FPDF_CreateNewDocument();
		 char a[100];
		 memset(a, 0, 100);
		 sprintf(a,"%d-%d",nowpage,pagesize - 1);
		 FPDF_ImportPages(outdoc,doc,a,0);
		 memset(a, 0, 100);
		 sprintf(a,"%d.pdf",j);
   	                 string filename2 = a;
	  	 int fp = open(filename2.c_str(), O_RDWR|O_CREAT);
		 PdfToFdWriter writer;
		 writer.version = 1;
		 writer.dstFd = fp;
		 writer.WriteBlock = &writeBlock;
	    FPDF_SaveAsCopy(outdoc, &writer, FPDF_NO_INCREMENTAL);
	    nowpage = nowpage + pagesplit;
	    FPDF_CloseDocument(outdoc);
		 close(fp);
                                j++;
		  }

	  FPDF_CloseDocument(doc);
        FPDF_DestroyLibrary(); 
          return numPages;

 }



void mytest(void*)
{
   std::cout<<"my test"<<std::endl;
}

