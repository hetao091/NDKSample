//
// Created by hetao on 2020/8/9.
//

#include <android/log.h>

#ifndef NDKSAMPLE_LOGUTIL_H
#define NDKSAMPLE_LOGUTIL_H


#define TAG "TTNative"


#define LOGI(FORMAT, ...) __android_log_print(ANDROID_LOG_INFO,TAG,FORMAT,##__VA_ARGS__);
#define LOGE(FORMAT, ...) __android_log_print(ANDROID_LOG_ERROR,TAG,FORMAT,##__VA_ARGS__);
#define LOGW(FORMAT, ...) __android_log_print(ANDROID_LOG_WARN,TAG,FORMAT,##__VA_ARGS__);
#define LOGD(FORMAT, ...) __android_log_print(ANDROID_LOG_DEBUG,TAG,FORMAT,##__VA_ARGS__);




#endif  // ANDROIDCPPSOLIB_LOGUTIL_H
