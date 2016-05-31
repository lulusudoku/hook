#ifndef _JINTERFACETRACE_H
#define _JINTERFACETRACE_H

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

void trace_jInterfaceFunction(JNIEnv* env);
void Untrace_jInterfaceFunction(JNIEnv* env);

#ifdef __cplusplus
};
#endif

#endif


