#include <jni.h>
#include <string>
#include <android/log.h>
#include <unistd.h>
#include <dlfcn.h>
#include "dobby.h"

#define  LOGD(...)  __android_log_print(ANDROID_LOG_INFO, "========= Debug =========   ", __VA_ARGS__)
#define TAG "xbsHook"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__)

extern "C" JNIEXPORT jstring JNICALL
Java_com_xbshook_xbsdobby_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "我没有被hook";
    return env->NewStringUTF(hello.c_str());
}

static jstring (*orgin_new_Java_com_xbshook_xbsdobby_MainActivity_stringFromJNI)(JNIEnv* env,jobject /* this */);

extern "C" JNIEXPORT jstring JNICALL
new_Java_com_xbshook_xbsdobby_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "我被hook修改了";
    return env->NewStringUTF(hello.c_str());
}

__attribute__((constructor)) static void ctor() {
    DobbyHook((void *) DobbySymbolResolver(nullptr, "Java_com_xbshook_xbsdobby_MainActivity_stringFromJNI"), (dobby_dummy_func_t) new_Java_com_xbshook_xbsdobby_MainActivity_stringFromJNI,(dobby_dummy_func_t*) &orgin_new_Java_com_xbshook_xbsdobby_MainActivity_stringFromJNI);
}

int JNI_OnLoad(JavaVM *vm, void *reserved) {
    LOGD("JNI_OnLoad execute...");
    return JNI_VERSION_1_6;
}