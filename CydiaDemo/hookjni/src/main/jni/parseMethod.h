#ifndef _PARSEMETHOD_H
#define _PARSEMETHOD_H

#include <jni.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

void parsePara(jmethodID methodID, va_list args, char *para);

#ifdef __cplusplus
};
#endif




#endif 
