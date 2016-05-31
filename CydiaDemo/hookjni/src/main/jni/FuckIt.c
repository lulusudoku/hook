//
// Created by LCX on 2016/5/30.
//
#include <string.h>
#include <assert.h>
#include <android/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <dlfcn.h>
#include <jni.h>

#include "parseMethod.h"
#include "jInterfaceTrace.h"


#define LOG_TAG "lulusudoku"
#define pagesize 0x1000
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)


JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved)
{
    LOGI("Load hook library");
    JNIEnv* env = NULL;
    jint result = -1;

    if ((*vm)->GetEnv(vm, (void**) &env, JNI_VERSION_1_1) != JNI_OK) {
        LOGI("Load library error");
        return JNI_ERR;
    }

    assert(env != NULL);
    LOGI("Trying to hook jni function");

    mprotect((void*)((int)(*env) & ~((pagesize)-1)) , pagesize*2, PROT_READ | PROT_WRITE | PROT_EXEC );
    trace_jInterfaceFunction(env);
    mprotect((void*)((int)(*env) & ~((pagesize)-1)), pagesize*2, PROT_READ | PROT_EXEC );

    LOGI("Hook Success");
    result = (*env)->GetVersion(env);
    LOGI("Load library success: %d", result);

    return result;
}

