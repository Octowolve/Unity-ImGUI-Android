#include <pthread.h>
#include <jni.h>

#include "includes/hooks.h"

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void * reserved)
{
    pthread_t ptid;
    pthread_create(&ptid, NULL, hooks::init, NULL);
    return JNI_VERSION_1_6;
}