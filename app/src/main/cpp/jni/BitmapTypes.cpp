//
// Created by hetao on 2020/8/9.
//

#include <jni.h>

#include <android/bitmap.h>
#include <cstring>

#include <logutil.h>
#include <BitmapTypes.h>

// 创建bitmap public static Bitmap createBitmap (int width,int height,  Bitmap.Config config)

jobject createBitmap(JNIEnv *env, uint32_t width, uint32_t height) {
    static jclass cls = nullptr;
    if (cls == nullptr) {
        jclass localRefs = env->FindClass("android/graphics/Bitmap");
        if (localRefs == nullptr) {
            return nullptr;
        }
        cls = (jclass) env->NewGlobalRef(localRefs);
        env->DeleteLocalRef(localRefs);
        if (cls == nullptr) {
            return nullptr;
        }
    }

    static jmethodID mid = nullptr;
    if (mid == nullptr) {
        mid = env->GetStaticMethodID(cls, "createBitmap",
                                     "(IILandroid/graphics/Bitmap$Config;)Landroid/graphics/Bitmap;");
        if (mid == nullptr) {
            return nullptr;
        }
    }
    // 声明 格式
    jstring configName = env->NewStringUTF("ARGB_8888");
    jclass bitmapConfigClass = env->FindClass("android/graphics/Bitmap$Config");
    static jmethodID getBitmapFunction = nullptr;
    if (getBitmapFunction == nullptr) {
        getBitmapFunction = env->GetStaticMethodID(
                bitmapConfigClass, "valueOf",
                "(Ljava/lang/String;)Landroid/graphics/Bitmap$Config;");
        if (getBitmapFunction == nullptr) {
            return nullptr;
        }
    }


    jobject bitmapConfig = env->CallStaticObjectMethod(bitmapConfigClass,
                                                       getBitmapFunction, configName);

    jobject newBitmap = env->CallStaticObjectMethod(cls, mid,
                                                    width, height, bitmapConfig);
    return newBitmap;
}

jobject createBitmapByKotlin(JNIEnv *env, uint32_t width, uint32_t height) {
    static jclass cls = nullptr;
    if (cls == nullptr) {
        jclass localRefs = env->FindClass("tt/reducto/ndksample/ui/BitmapPool");
        if (localRefs == nullptr) {
            return nullptr;
        }
        cls = (jclass) env->NewGlobalRef(localRefs);
        env->DeleteLocalRef(localRefs);
        if (cls == nullptr) {
            return nullptr;
        }
    }

    static jmethodID createBitmapFunction = nullptr;
    if (createBitmapFunction == nullptr) {
        createBitmapFunction = env->GetMethodID(cls, "<init>", "()V");
        if (createBitmapFunction == nullptr) {
            return nullptr;
        }
    }


    jobject jobject1 = env->NewObject(cls, createBitmapFunction);
    static jmethodID mid = nullptr;
    if (mid == nullptr) {
        mid = env->GetMethodID(cls, "getARGB8888Bitmap",
                               "(II)Landroid/graphics/Bitmap;");
        if (mid == nullptr) {
            return nullptr;
        }
    }

    return env->CallObjectMethod(jobject1, mid, (int) width, (int) height);
}


extern "C"
JNIEXPORT jobject JNICALL
Java_tt_reducto_ndksample_jni_BitmapOps_rotateBitmap(JNIEnv *env, jobject thiz, jobject bitmap,
                                                     jint ops) {
    if (bitmap == nullptr) {
        LOGD("rotateBitmap - the  bitmap is null ")
        return nullptr;
    }

    // 检索获取bitmap信息
    AndroidBitmapInfo bitmapInfo;
    int ret = AndroidBitmap_getInfo(env, bitmap, &bitmapInfo);
    if (ANDROID_BITMAP_RESULT_SUCCESS != ret) {
        LOGD("AndroidBitmap_getInfo() bitmap failed ! error=%d", ret)
        return nullptr;
    }
    // 获得 Bitmap 的像素缓存指针：遍历从 Bitmap 内存 addrPtr 中读取像素数据
    void *addrPtr;
    ret = AndroidBitmap_lockPixels(env, bitmap, &addrPtr);
    if (ANDROID_BITMAP_RESULT_SUCCESS != ret) {
        LOGD("AndroidBitmap_lockPixels() bitmap failed ! error=%d", ret)
        return nullptr;
    }

    // 执行图片操作的逻辑
    // 获取宽高
    int mWidth = bitmapInfo.width;
    int mHeight = bitmapInfo.height;
    // 获取原生数据
    auto pixelArr = ((uint32_t *) addrPtr);
    // 矩阵 创建一个新的数组指针填充像素值
    auto *newBitmapPixels = new uint32_t[mWidth * mHeight];
    LOGD("bitmap width = %d", mWidth)
    LOGD("bitmap height = %d", mHeight)
    LOGD("bitmap format = %d", bitmapInfo.format)
    int temp = 0;
    switch (ops) {
        case 0:
            // 遍历矩阵，按照顺时针90度顺序扫描
            for (int x = 0; x < mWidth; x++) {
                for (int y = mHeight - 1; y >= 0; --y) {
                    newBitmapPixels[temp++] = pixelArr[mWidth * y + x];
                }
            }

            break;
        case 1:
            // 上下翻转
            for (int y = 0; y < mHeight; ++y) {
                for (int x = 0; x < mWidth; x++) {
                    uint32_t pixel = pixelArr[temp++];
                    newBitmapPixels[mWidth * (mHeight - 1 - y) + x] = pixel;
                }
            }
            break;
        case 2:
            // 镜像
            for (int y = 0; y < mHeight; ++y) {
                for (int x = mWidth - 1; x >= 0; x--) {
                    uint32_t pixel = pixelArr[temp++];
                    newBitmapPixels[mWidth * y + x] = pixel;
                }
            }
            break;
        default:
            break;
    }


    // 新建bitmap 注意这里 因为翻转90度后，矩阵即bitmap的宽高也要改变
    jobject newBitmap;
    int size = mWidth * mHeight;
    if (ops == 0) {
        newBitmap = createBitmap(env, mHeight, mWidth);
        void *resultBitmapPixels;
        //
        ret = AndroidBitmap_lockPixels(env, newBitmap, &resultBitmapPixels);
        if (ANDROID_BITMAP_RESULT_SUCCESS != ret) {
            LOGD("AndroidBitmap_lockPixels() newBitmap failed ! error=%d", ret)
            return nullptr;
        }

        // 写入新值
        memcpy((uint32_t *) resultBitmapPixels, newBitmapPixels, sizeof(uint32_t) * size);
        // 释放缓存指针
        AndroidBitmap_unlockPixels(env, newBitmap);
        // 释放内存
        delete[] newBitmapPixels;

        return newBitmap;
    } else {
//        newBitmap = createBitmap(env, mWidth, mHeight);
        memcpy((uint32_t *) addrPtr, newBitmapPixels, sizeof(uint32_t) * size);
        delete[] newBitmapPixels;
        // 释放缓存指针
        AndroidBitmap_unlockPixels(env, bitmap);
        return bitmap;
    }




}
extern "C"
JNIEXPORT void JNICALL
Java_tt_reducto_ndksample_jni_BitmapOps_addBitmapFilter(JNIEnv *env, jobject thiz, jobject bitmap) {
    if (bitmap == nullptr) {
        LOGD("rotateBitmap - the  bitmap is null ")
    }

    // 检索获取bitmap信息
    AndroidBitmapInfo bitmapInfo;
//    memset(&bitmapInfo , 0 , sizeof(bitmapInfo));
    int ret = AndroidBitmap_getInfo(env, bitmap, &bitmapInfo);
    if (ANDROID_BITMAP_RESULT_SUCCESS != ret) {
        LOGD("AndroidBitmap_getInfo() bitmap failed ! error=%d", ret)
    }
    // 获得 Bitmap 的像素缓存指针：遍历从 Bitmap 内存 addrPtr 中读取 BGRA 数据
    void *addrPtr;
    ret = AndroidBitmap_lockPixels(env, bitmap, &addrPtr);
    if (ANDROID_BITMAP_RESULT_SUCCESS != ret) {
        LOGD("AndroidBitmap_lockPixels() bitmap failed ! error=%d", ret)
    }

    // 执行图片操作的逻辑
    // 获取宽高
    uint32_t mWidth = bitmapInfo.width;
    uint32_t mHeight = bitmapInfo.height;
    // 矩阵 创建一个新的数组指针填充像素值
    // auto *newBitmapPixels = new uint32_t[mWidth * mHeight];
    LOGD("bitmap width = %d", mWidth)
    LOGD("bitmap height = %d", mHeight)
    LOGD("bitmap format = %d", bitmapInfo.format)

    // 获取原生数据
    auto pixelArr = ((uint32_t *) addrPtr);

    int a, r, g, b;
    // 不操作A
    // 遍历从 Bitmap 内存 addrPtr 中读取 BGRA 数据, 然后向 data 内存存储 BGR 数据
    for (int y = 0; y < mHeight; ++y) {

        for (int x = 0; x < mWidth; ++x) {
            // 这里定义成void,方便后续操作
            void *pixel = nullptr;
            // 24位
            if (bitmapInfo.format == ANDROID_BITMAP_FORMAT_RGBA_8888) {
                // 移动像素指针
                pixel = pixelArr + y * mWidth + x;
                //按照ABGR存储序列取值  获取指针对应的值
                uint32_t v = *((uint32_t *) pixel);
                a = BGR_8888_A(v);
                r = BGR_8888_R(v);
                g = BGR_8888_G(v);
                b = BGR_8888_B(v);

                // 平均值法
//                int sum = (r + g + b) / 3;
                //或者加权平均值法
                int sum = (int)(r * 0.3 + g * 0.59 + b * 0.11);

                *((uint32_t *) pixel) = MAKE_ABGR(a, sum, sum, sum);
            }
        }
    }

    // 释放缓存指针
    AndroidBitmap_unlockPixels(env, bitmap);
}