/**
*  Hook dlopen and print base addr and size
*  by lulusudoku
*/

#include <stdio.h>
#include <android/log.h>
#include <unistd.h>
#include "substrate.h"

#define LOG_TAG "HOOK_DLOPEN"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,LOG_TAG ,__VA_ARGS__) // 定义LOGI类型

// Lib to hook
// Can not hook linker
MSConfig(MSFilterLibrary, "/system/lib/libdvm.so")

// original function template
void (*old_dlopen)(const char* pathname, int mode);

void new_dlopen(const char* path, int mode)
{
    LOGI("****Call new dlopen, so name is: %d\n", getpid());
    return old_dlopen(path, mode);
}

MSInitialize
{
    LOGI("****dlopen hook initialized gg");
    MSImageRef image, image1;

    image = MSGetImageByName("/system/lib/libc.so");

    if(image != NULL)
    {
        void * hookdlopen = MSFindSymbol(image,"__dl_open");
        		if(hookdlopen==NULL)
        		{
        			LOGI("error find __dl_open ");
        		}
        		else {
        			MSHookFunction(hookdlopen,(void*)&new_dlopen,(void **)&old_dlopen);
        		}
    } else {
        LOGI("error find libc.so ");
    }

    image1 = MSGetImageByName("/system/lib/libdvm.so");
    if(image1 != NULL)
    {
        void * hookJNI = MSFindSymbol(image,"Check_RegisterNatives");
        if(hookJNI == NULL)
        {
            LOGI("error find jni method.");
        }
        else {
                			MSHookFunction(hookJNI,(void*)&new_dlopen,(void **)&old_dlopen);
                		}
    }
    else {
        LOGI("error find libdvm.so");
    }
}