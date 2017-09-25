//
// Created by jiangkun on 2017/8/11.
//
#include <string.h>
#include <jni.h>
#include <pthread.h>
#include <assert.h>
#include "Info.h"


JavaVM *javaVM;

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    javaVM = vm;
    return JNI_VERSION_1_6;
}


jobject g_clz;
jobject g_instance;
jmethodID g_methodID;


void loadClass(JNIEnv *pEnv);

void *newThread(void *methodID) {
    JNIEnv *env;
    Info info;
    info.log("start in new thread");

    int stat = javaVM->GetEnv((void **) &env, JNI_VERSION_1_6);
    if (stat != JNI_OK) {
        stat = javaVM->AttachCurrentThread(&env, NULL);
        if (JNI_OK != stat) {
            return NULL;
        }
    }
    if (env == NULL) {
        info.log("env is null");
        return NULL;
    }

    jstring str = env->NewStringUTF("newThread");
    info.log("before call method");
    if (g_instance == NULL) {
        info.log("g_instance is null");
        return NULL;
    }
    g_methodID = *(jmethodID *) methodID;
    if (g_methodID == NULL) {
        info.log("g_methodID is null");
        return NULL;
    }

    for (int i = 0; i < 10; ++i) {
        env->CallVoidMethod(g_instance, g_methodID, str);
    }
    env->DeleteLocalRef(str);
    env->DeleteGlobalRef(g_clz);
    env->DeleteGlobalRef(g_instance);
    javaVM->DetachCurrentThread();
    return NULL;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_hellojnicallback_MainActivity_newThread(JNIEnv *env, jobject instance) {


    loadClass(env);

    g_instance = env->NewGlobalRef(instance);
    jclass clz = env->GetObjectClass(instance);
    g_methodID = env->GetMethodID(clz, "onNewThreadCallBack", "(Ljava/lang/String;)V");
    g_clz = env->NewGlobalRef(clz);

    jstring str = env->NewStringUTF("before new thread");
    env->CallVoidMethod(instance, g_methodID, str);


    pthread_t threadInfo_;
    pthread_attr_t threadAttr_;

    pthread_attr_init(&threadAttr_);
    pthread_attr_setdetachstate(&threadAttr_, PTHREAD_CREATE_DETACHED);

    int result = pthread_create(&threadInfo_, &threadAttr_, newThread, &g_methodID);
    assert(result == 0);//如果它的条件返回错误，则终止程序执行

    (void) result;
}

void loadClass(JNIEnv *env) {
    Info info;
    jclass clz = env->FindClass("com/example/hellojnicallback/JniHandler");
    if (clz == NULL) {
        info.log("can not use find class in this thread. ");
    }

}
