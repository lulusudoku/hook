//
// Created by LCX on 2016/5/19.
//

#include <stdio.h>
#include <android/log.h>
#include <unistd.h>
#include "substrate.h"

#define TAG "CydiaHook"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__) // 定义LOGI类型


#define GETLR(store_lr)  \
  __asm__ __volatile__(  \
    "movl %0, %%eax\n\t"  \
    :  "=r"(store_lr)  \
  )


//指明要hook的lib
MSConfig(MSFilterLibrary, "/system/lib/libc.so")

int (* oldfopen)(const char* path, const char* mode);

int newfopen(const char* path, const char* mode) {

	LOGI("call my fopen!!:%d",getpid());
	unsigned int eax;
	GETLR(eax);

	if (strstr(path, "status") != NULL) {
		LOGI("[*] Traced-fopen Call function: 0x%x\n", eax);
		if (strstr(path, "task") != NULL) {
			LOGI("[*] Traced-anti-task/status");
		} else
			LOGI("[*] Traced-anti-status");
	} else if (strstr(path, "wchan") != NULL) {
		LOGI("[*] Traced-fopen Call function: 0x%x\n", eax);
		LOGI("[*] Traced-anti-wchan");
	}
	return oldfopen(path, mode);
}



/*
 * Substrate entry point
 */
//初始化时进行hook
MSInitialize
{
	// Let the user know that the extension has been
	// extension has been registered
	LOGI( "Substrate initialized.");
	MSImageRef image;

	image = MSGetImageByName("/system/lib/libc.so");

	if (image != NULL)
	{
		void * hookfopen=MSFindSymbol(image,"fopen");
		if(hookfopen==NULL)
		{
			LOGI("error find fopen ");
		}
		else {
			MSHookFunction(hookfopen,(void*)&newfopen,(void **)&oldfopen);
		}
	}
	else {
		LOGI("ERROR FIND LIBC");
	}

}