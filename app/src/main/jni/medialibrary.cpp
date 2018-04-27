//
// Created by train on 2018-04-04.
// medialibrary
// 1. nativestart
// 2. nativestop
//

#include <jni.h>
#include <stdio.h>
#include "Utils/log.h"
#include "Utils/Player.h"

static inline void MediaLibrary_setInstance(JNIEnv *env, jobject thiz, Player *p_obj);
static inline Player* MediaLibrary_getInstance(JNIEnv *env, jobject thiz);

jfieldID field;

int init(JNIEnv *env, jobject thiz, jstring url){
    LOGI("nativeInit ");

    Player *player = new Player(url);

    MediaLibrary_setInstance(env, thiz, player);
    return 0;
}

int play(JNIEnv* env, jobject thiz){
    LOGI("nativeplay ");
    Player *player = MediaLibrary_getInstance(env, thiz);
    return 0;
}

int stop(){
    LOGI("nativestop ");
    return 0;
}

int nativeSetSurface(JavaVM *jvm, jobject surface){
    LOGI("set surface");
    return 0;
}
static JNINativeMethod sMethod[] = {
        {"nativeInit", "(Ljava/lang/String;)I", (void*)init},
        {"nativeSetSurface", "(Ljava/lang/Object;)I",(void*)nativeSetSurface},
        {"nativePlay", "()I",(void*)play},
        {"nativeStop", "()I",(void*)stop}
};

JNIEXPORT int JNI_OnLoad(JavaVM* vm, void* reserved) {
    JNIEnv* env = NULL;
    jint result = -1;
    int methodLength = sizeof(sMethod) / sizeof(sMethod[0]);

    if(vm->GetEnv((void**) &env, JNI_VERSION_1_6) != JNI_OK){
        return result;
    }

        //함수 사이즈 제대로 받게끔 수정해야함
#define GetMethod(className, sMethod) \
        jclass clazz = env->FindClass(className); \
        if(clazz == NULL){ \
            return -1; \
        } \
        if(env->RegisterNatives(clazz, sMethod, methodLength) < 0){ \
            return -1; \
        } \

    GetMethod("medialibrary/Medialibrary", sMethod);

    return JNI_VERSION_1_6;
}

Player *
MediaLibrary_getInstance(JNIEnv *env, jobject thiz)
{
    Player *p_obj = MediaLibrary_getInstanceInternal(env, thiz);
    if (!p_obj){
        printf("error getInstance\n");
    }
        // throw_IllegalStateException(env, "can't get AndroidMediaLibrary instance");
    return p_obj;
}


static void
MediaLibrary_setInstance(JNIEnv *env, jobject thiz, AndroidMediaLibrary *p_obj)
{
    env->SetLongField(thiz,
                      field,
                      (jlong)(intptr_t)p_obj);
}
