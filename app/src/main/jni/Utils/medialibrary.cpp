//
// Created by train on 2018-04-04.
// medialibrary
// 1. nativestart
// 2. nativestop
//

#include <jni.h>
#include <stdio.h>
#include <string>
#include "Utils/log.h"
#include "Utils/Player.h"

PlayerField field;

static inline void MediaLibrary_setInstance(JNIEnv *env, jobject thiz, Player *p_obj);
static inline Player* MediaLibrary_getInstance(JNIEnv *env, jobject thiz);

static Player *
MediaLibrary_getInstanceInternal(JNIEnv *env, jobject thiz)
{
    return (Player*) env->GetLongField(thiz, field.instanceId);
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

/*자바에서 설정한 id 값으로 인스턴스를 초기화한다.
 * 플레이어를 여러개 만들기위해서 이렇게 하는거네
 * 그래서 플레이어의 모든 객체를 독립적으로 관리해서 인스턴스를 여러개 생성될때마다 아이디값이 달라지면 jni단에서도 독립적으로 만들어지니까.
 * 미디어플레이어가 독립적으로 만들어지잖아 자바에서 객체가 생성이 되면
 * 그래서 자바에서 만든 객체와
 * instance 아이디는 자바와 객체를 관리하기 위해서 만든거고
 *
 * 다른 메소드는 getId한게 콜백메소드를 하기위해서 한거같다.
 * 미디어 추가하는거를 보면 어떤식으로 했냐면, jni단에서 미디어를 찾고, 찾으면 자바 메소드호출해서 찾은 미디어를 추가하는 방식 왜이렇게 할까 자바에서 하면 안돼?
 * 냉생각에는 아에 그냥 무조건 jni 단에서 하고 진짜 말그대로 ui만 자바로 짜려고한듯 근데 굉장히 귀찮은 작업인데 왜 이렇게 했을까 ios도 같은방식인가
 *
 */
static void
MediaLibrary_setInstance(JNIEnv *env, jobject thiz, Player *p_obj)
{
    env->SetLongField(thiz,
                      field.instanceId,
                      (jlong)(intptr_t )p_obj);
}

int init(JNIEnv *env, jobject thiz, jstring url){
    LOGI("nativeInit ");
    const char *convertUrl = env->GetStringUTFChars(url, 0);
    Player *player = new Player(convertUrl, &field);

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

#define GET_CLASS(clazz, str, b_globlal) do { \
                (clazz) = env->FindClass((str)); \
                if (!(clazz)) { \
                LOGE("FindClass(%s) failed", (str)); \
                return -1; \
            } \
                if (b_globlal) { \
                (clazz) = (jclass) env->NewGlobalRef((clazz)); \
                if (!(clazz)) { \
                LOGE("NewGlobalRef(%s) failed", (str)); \
                return -1; \
            } \
            } \
        } while (0)

#define GET_ID(get, id, clazz, str, args) do { \
           (id) = env->get((clazz), (str), (args)); \
            if (!(id)) { \
            LOGE(#get"(%s) failed", (str)); \
            return -1; \
            } \
        } while (0)

        //함수 사이즈 제대로 받게끔 수정해야함
#define GetMethod(className, sMethod) \
        if(env->RegisterNatives(className, sMethod, methodLength) < 0){ \
            return -1; \
        } \

    GET_CLASS(field.mediaClass, "medialibrary/Medialibrary", true);
    GetMethod(field.mediaClass, sMethod);

//    GET_ID(get, id, clazz, str, args) do {
        field.instanceId = env->GetFieldID(field.mediaClass, "instanceId", "J");
            if (!(field.instanceId)) {
            LOGE("faile");
            return -1;
            }

//    GET_ID(GetFieldID,
//           field.instanceId,
//           field.mediaClass,
//           "instanceId", "J");

    return JNI_VERSION_1_6;
}
