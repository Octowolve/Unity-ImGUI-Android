#pragma once
#include <android/log.h>

enum daLogType {
    daDEBUG = 3,
    daERROR = 6,
    daINFO  = 4,
    daWARN  = 5
};

//Change this to another Log Tag if ya want.
#define TAG "void"

#define LOGD(...) ((void)__android_log_print(daDEBUG, TAG, __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(daERROR, TAG, __VA_ARGS__))
#define LOGI(...) ((void)__android_log_print(daINFO,  TAG, __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(daWARN,  TAG, __VA_ARGS__))
