//
// Created by train on 2018-04-04.
// medialibrary
// 1. nativestart
// 2. nativestop
//
#include<jni.h>
#include"log.h"

jint init(){
    LOGI("nativeInit");
    return 0;
}

static JNINativeMethod sMethod[] = {
        {"nativeInit", "()I", (void*)init}
};

JNIEXPORT int JNI_OnLoad(JavaVM* vm, void* reserved) {
    JNIEnv* env = NULL;
    jint result = -1;

    if(vm->GetEnv((void**) &env, JNI_VERSION_1_6) != JNI_OK){
        return result;
    }

#define GetMethod(className, sMethod) \
        jclass clazz = env->FindClass(className); \
        if(clazz == NULL){ \
            return -1; \
        } \
        if(env->RegisterNatives(clazz, sMethod, 1) < 0){ \
            return -1; \
        } \

    GetMethod("medialibrary/Medialibrary", sMethod);

    return JNI_VERSION_1_6;
}
