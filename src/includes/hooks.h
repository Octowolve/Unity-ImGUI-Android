#pragma once
#include <dobby.h>
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <jni.h>
#include <mutex>

#include "utils.h"
#include "logger.h"
#include "menu.h"

namespace hooks{
    void* init(void*);

    namespace swapbuffers {
        using orig = EGLBoolean (*)(EGLDisplay dpy, EGLSurface surf);
        EGLBoolean hook(EGLDisplay dpy, EGLSurface surf);
    }

    namespace input {
        namespace inject_event {
            using orig = int (*)(JNIEnv *env, jobject thiz, jobject inputEvent);
            int hook(JNIEnv *env, jobject thiz, jobject inputEvent);
        }
    }
}