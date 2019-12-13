#ifndef _FPDFSPLIT_H_
#define _FPDFSPLIT_H
#define DLLEXPORT
#define STDCALL
typedef const char* FPDF_STRING;
typedef int		FPDF_BOOL;
typedef int		FPDF_ERROR;
#ifdef __cplusplus
extern "C" {
#endif

DLLEXPORT FPDF_BOOL STDCALL FPDF_Split(FPDF_STRING SourPdf,FPDF_STRING DestPdf,FPDF_BOOL PageNum);

void mytest(void*);





#ifdef __cplusplus
};
#endif
#endif
