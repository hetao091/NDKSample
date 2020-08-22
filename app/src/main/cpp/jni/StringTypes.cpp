//
// Created by hetao on 2020/7/16.
//

#include <jni.h>
#include <string>
#include <iostream>
#include <logutil.h>
#include <array>

using namespace std;



// 全局变量作为缓存
// Java字符串的类和获取方法ID
jclass gStringClass;

jmethodID gmidStringInit;

jmethodID gmidStringGetBytes;

int isASCII(const char *chp) {
    char ch;
    jboolean flag = 1;
    ch = *chp++;
    while (ch) {
        if (ch & 0x80) {
            flag = 0;
            break;
        }
        ch = *chp++;
    }
    return flag;
}
// jstring to char*

char *JstringToPchar(JNIEnv *env, jstring jstr, const char *encoding) {
    char *rtn = nullptr;

    jstring jencoding;
    jencoding = env->NewStringUTF(encoding);
    jbyteArray barr = (jbyteArray) env->CallObjectMethod(jstr, gmidStringGetBytes, jencoding);
    jsize alen = env->GetArrayLength(barr);
    jbyte *ba = env->GetByteArrayElements(barr, nullptr);
    if (alen > 0) {
        //LOGI("alen = %d ",alen);
        rtn = (char *) malloc(alen + 1);
        memcpy(rtn, ba, alen);
        rtn[alen] = 0;
    }
    env->ReleaseByteArrayElements(barr, ba, 0);
    return rtn;

}



//char* to jstring

jstring PcharToJstring(JNIEnv *env, const char *pchar, const char *encoding) {
    jstring jencoding;

    jbyteArray bytes = env->NewByteArray(strlen(pchar));
    // 复制
    env->SetByteArrayRegion(bytes, 0, strlen(pchar), (jbyte *) pchar);
    // c
    jencoding = env->NewStringUTF(encoding);
    // 创建类
    return (jstring) env->NewObject(gStringClass, gmidStringInit, bytes, jencoding);

}

/**
 *
 * @param env
 * @param jstr
 * @return
 */
char *Jstring2CStr(JNIEnv *env, jstring jstr) {
    char *rtn = nullptr;
    //寻找 java里面String.class
    jclass clsstring = env->FindClass("java/lang/String");
    // 创建java字符串 "gb2312"
    jstring strencode = env->NewStringUTF("GB2312");
    //寻找到java String getbytes();
    jmethodID mid = env->GetMethodID(clsstring, "getBytes",
                                     "(Ljava/lang/String;)[B");
    // String .getByte("GB2312");
    jbyteArray barr = (jbyteArray) env->CallObjectMethod(jstr, mid,
                                                         strencode);
    //获取长度
    jsize alen = env->GetArrayLength(barr);
    jbyte *ba = env->GetByteArrayElements(barr, JNI_FALSE);

    //jbyteArray转为jbyte*
    if (alen > 0) {
        //"\0"
        rtn = (char *) malloc(alen + 1);
        memcpy(rtn, ba, alen);
        rtn[alen] = 0;
    }
    //释放掉
    env->ReleaseByteArrayElements(barr, ba, 0);
    return rtn;
}

/**
 * 抛出异常
 *
 * @param env
 * @param name
 * @param msg
 */
void throwByName(JNIEnv *env, const char *name, const char *msg) {
    jclass cls = env->FindClass(name);
    if (cls != nullptr) {
        // 在当前线程触发一个异常，并自定义输出异常信息
        LOGD("throwByName: ")
        env->ThrowNew(cls, msg);
    }
    /* 释放局部引用 */
    env->DeleteLocalRef(cls);
}


extern "C"
JNIEXPORT jstring JNICALL
Java_tt_reducto_ndksample_jni_StringTypeOps_plus(JNIEnv *env, jobject thiz, jint a, jint b) {
    jint sum = a + b;
    char buf[64];
    // 字符串格式化
    sprintf(buf, "%d", sum);
    return env->NewStringUTF(buf);
}

/**
 *  合并字符串
 */
extern "C"
JNIEXPORT jstring JNICALL
Java_tt_reducto_ndksample_jni_StringTypeOps_splicingString(JNIEnv *env, jobject thiz, jstring str) {


    // 通过FindClas( )，获取Java类的的jclass
    jclass String_clazz = env->FindClass("java/lang/String");
    // 获取java类的构造方法ID jmethodID和jfieldID指标可以存在C语言的全局变量中，既能跨函数共享，又能跨进程共享。
    // 用Java中String拼接字符的方法,concat()函数
    jmethodID concat_methodID = env->GetMethodID(String_clazz, "concat",
                                                 "(Ljava/lang/String;)Ljava/lang/String;");
    // 生成 jstring 类型的字符串
    jstring tmp = env->NewStringUTF(",--- 新的一天，从\"心\"开始");
    // 实例化java类并传递参数
    jobject str1 = env->CallObjectMethod(str, concat_methodID, tmp);
    const char *chars = env->GetStringUTFChars((jstring) str1, nullptr);

    if (chars == nullptr) {
        return nullptr;
    }
    printf("%s", chars);
    // 释放掉申请的 C 风格字符串的内存
    env->DeleteLocalRef(tmp);
    env->ReleaseStringUTFChars((jstring) str1, chars);

    // 返回 jstring 类型字符串
    return env->NewStringUTF(chars);

//    jstring result;
//    //
//    gStringClass = env->FindClass("java/lang/String");
//    if (gStringClass == nullptr) {
//        return nullptr;
//    }
//    //  public byte[] getBytes(java.lang.String) throws java.io.UnsupportedEncodingException;
//    gmidStringGetBytes = (env)->GetMethodID(gStringClass, "getBytes", "(Ljava/lang/String;)[B");
//    if (gmidStringGetBytes == nullptr) {
//        return nullptr;
//    }
//    //  public java.lang.String(byte[], java.lang.String) throws java.io.UnsupportedEncodingException;
//    //  //通过构造函数创建 String 对象,传入byte 和UTF-8 string=new String(byte[] "gb2312");
//    gmidStringInit = (env)->GetMethodID(gStringClass, "<init>", "([BLjava/lang/String;)V");
//    if (gmidStringInit == nullptr) {
//        return nullptr;
//    }
//    //char *myTest = "Hello from JNI !";
//
//    string myTest = " 你 Hello from JNI !";
//    //
//    if (isASCII(myTest.c_str())) {
//        LOGI("Is ASCII")
//        result = env->NewStringUTF(myTest.c_str());
//    } else {
//        LOGI("Is Not ASCII");
//        result = PcharToJstring(env, myTest.c_str(), "GBK");
//        char *outbuf;
//
//        outbuf = JstringToPchar(env, result, "UTF-8");
////        LOGI("strlen(outbuf) = %d",strlen(outbuf));
////        int i;
////        for(i = 0 ; i < strlen(outbuf);i++)
////            LOGI("outbuf[%d] = %x",i,outbuf[i]);
//        result = env->NewStringUTF(outbuf);
//        if (outbuf) {
//            free(outbuf);
//        }
//    }
//    return result;
}


/**
 *  截取字符串
 */
extern "C"
JNIEXPORT jstring JNICALL
Java_tt_reducto_ndksample_jni_StringTypeOps_splitString(JNIEnv *env, jobject thiz, jstring str) {
    // 获取长度
    jsize len = env->GetStringLength(str);

    jchar outputBuf[len / 2];
    // 截取一部分内容放到缓冲区
    env->GetStringRegion(str, 0, len / 2, outputBuf);
    // 从缓冲区中获取 Java 字符串
    return env->NewString(outputBuf, len / 2);
}




extern "C"
JNIEXPORT jstring JNICALL
Java_tt_reducto_ndksample_jni_StringTypeOps_splicingStringCritical(JNIEnv *env,
                                                               jobject thiz,
                                                               jstring str) {
    const jchar *c_str = nullptr;
    char buf[128] = "cpp ";
    char *pBuff = buf + 4;

    c_str = env->GetStringCritical(str, nullptr);
    if (c_str == nullptr) {
        // error handle
        return nullptr;
    }
    while (*c_str) {
        *pBuff++ = *c_str++;
    }
    //
    env->ReleaseStringCritical(str, c_str);
    //
    return env->NewStringUTF(buf);
}

/**
 *  计算遍历数组求和。
 */
extern "C"
JNIEXPORT jint JNICALL
Java_tt_reducto_ndksample_jni_StringTypeOps_intArraySum(JNIEnv *env, jobject thiz,
                                                    jintArray int_array) {
    // 声明
    jint *intArray;
    //
    int sum = 0;
    //
    intArray = env->GetIntArrayElements(int_array, nullptr);
    if (intArray == nullptr) {
        return 0;
    }
    // 得到数组的长度
    int length = env->GetArrayLength(int_array);
    for (int i = 0; i < length; ++i) {
        sum += intArray[i];
    }

    // 也可以通过 GetIntArrayRegion 获取数组内容
    jint buf[length];
    //
    env->GetIntArrayRegion(int_array, 0, length, buf);
    // 重置
    sum = 0;
    for (int i = 0; i < length; ++i) {
        sum += buf[i];
    }
    // 释放内存
    env->ReleaseIntArrayElements(int_array, intArray, 0);
    //
    return sum;
}


/**
 *  反转字符串
 */
extern "C"
JNIEXPORT jstring JNICALL
Java_tt_reducto_ndksample_jni_StringTypeOps_reverseString(JNIEnv *env,
                                                      jobject thiz, jstring str) {

    jsize mSize = env->GetStringLength(str);
    // 直接指向 Unicode 编码的字符串的指针
    const jchar *mStr = env->GetStringChars(str, nullptr);
    // 双指针
    jsize j = 0, i = mSize - 1;
    jchar jch_tmp[mSize];
    // 不同类型
    for (; j < mSize; ++j, --i) {
        jch_tmp[j] = mStr[i];
        cout << jch_tmp << endl;
    }
    env->ReleaseStringChars(str, mStr);
    // 将 Unicode 编码的 C/C++ 字符串转换为 Java 字符串
    return env->NewString(jch_tmp, mSize);
}



extern "C"
JNIEXPORT jbyteArray JNICALL
Java_tt_reducto_ndksample_jni_StringTypeOps_chineseString(JNIEnv *env, jobject thiz,
                                                      jstring str) {

//    jsize len =  env->GetArrayLength(byte_array);
//
//    jbyte *ba = env->GetByteArrayElements(byte_array, JNI_FALSE);
//
//    char *chars = new char[len + 1];
//    memset(chars, 0x0, len + 1);
//    memcpy(chars, ba, len);
//    // 释放
//    chars[len] = 0;
    gStringClass = env->FindClass("java/lang/String");
    if (gStringClass == nullptr) {
        return nullptr;
    }
    //  public byte[] getBytes(java.lang.String) throws java.io.UnsupportedEncodingException;
    gmidStringGetBytes = (env)->GetMethodID(gStringClass, "getBytes", "(Ljava/lang/String;)[B");
    if (gmidStringGetBytes == nullptr) {
        return nullptr;
    }

    const char *result = JstringToPchar(env, str, "UTF-8");

    string mStr = "，C++ 字符串";
    // 拼接
    string tmp = string(result) + mStr;
    result = tmp.c_str();
    jbyteArray byteArray1 = env->NewByteArray(strlen(result));
    env->SetByteArrayRegion(byteArray1, 0, strlen(result), (jbyte *) result);

//    env->ReleaseByteArrayElements(byte_array,ba,0);

    return byteArray1;
}



extern "C"
JNIEXPORT jstring JNICALL
Java_tt_reducto_ndksample_jni_StringTypeOps_getObjectArrayElement(JNIEnv *env, jobject thiz,
                                                              jobjectArray jni_array) {
    jobject arr;
    // 数组长度
    int size = env->GetArrayLength(jni_array);
    static jclass cls = nullptr;
    // 数组中对应的类
    if (cls == nullptr) {
        jclass localRefs = env->FindClass("tt/reducto/ndksample/JniArray");
        if (localRefs == nullptr) {
            return nullptr;
        }
        cls = (jclass) env->NewWeakGlobalRef(localRefs);
        env->DeleteLocalRef(localRefs);
        if (cls == nullptr) {
            return nullptr;
        }
    }

    static jfieldID fid = nullptr;
    // 类对应的字段描述
    // 从缓存中查找
    if (fid == nullptr) {
        fid = env->GetFieldID(cls, "msg", "Ljava/lang/String;");
        if (fid == nullptr) {
            return nullptr;
        }
    }
    jboolean isGC = env->IsSameObject(cls, nullptr);
    if (isGC) {
        LOGD("weak reference has been gc")
        return nullptr;
    } else {
        if (env->EnsureLocalCapacity(size) < 0) {
            //内存不足
            return nullptr;
        }
        jstring jstr;
        // 类的字段具体的值
        // 类字段具体值转换成 C/C++ 字符串
        const char *str = nullptr;
        string tmp;
        for (int i = 0; i < size; ++i) {
            // 得到数组中的每一个元素
            arr = env->GetObjectArrayElement(jni_array, i);
            // 每一个元素具体字段的值
            jstr = (jstring) (env->GetObjectField(arr, fid));

            str = env->GetStringUTFChars(jstr, nullptr);
            if (str == nullptr) {
                continue;
            }
            tmp += str;
            LOGD("str is %s", str)
            env->ReleaseStringUTFChars(jstr, str);
        }
        return env->NewStringUTF(tmp.c_str());
    }

}

extern "C"
JNIEXPORT  void JNICALL
Java_tt_reducto_ndksample_jni_StringTypeOps_exception
        (JNIEnv *env, jobject jobj) {

    jclass cls = env->FindClass("tt/reducto/ndksample/ExcTest");

    jmethodID mid = env->GetMethodID(cls, "<init>", "()V");
    jobject obj = env->NewObject(cls, mid);
    mid = env->GetMethodID(cls, "getNum", "()I");
    // 先初始化一个类，然后调用类方法，就如博客中描述的那样
    env->CallIntMethod(obj, mid);
    // 检查是否发生了异常，若用异常返回该异常的引用，否则返回NULL
    jthrowable exc;
    exc = env->ExceptionOccurred();

    if (exc) {
        // 打印异常调用异常对应的Java类的printStackTrace()函数
        env->ExceptionDescribe();
        // 清除引发的异常，在Java层不会打印异常的堆栈信息
        env->ExceptionClear();
        env->DeleteLocalRef(cls);
        env->DeleteLocalRef(obj);

        // 抛出一个自定义异常信息
        throwByName(env, "java/lang/ArithmeticException", "divide by zero");
    }

}

extern "C"
JNIEXPORT jobjectArray JNICALL
Java_tt_reducto_ndksample_jni_StringTypeOps_getNewObjectArray(JNIEnv *env, jobject thiz) {
    // 声明一个对象数组
    jobjectArray result;
    // 设置 数组长度
    int size = 5;
    //
    static jclass cls = nullptr;
    // 数组中对应的类
    if (cls == nullptr) {

        jclass localRefs = env->FindClass("tt/reducto/ndksample/JniArray");
        if (localRefs == nullptr) {
            return nullptr;
        }
        cls = (jclass) env->NewGlobalRef(localRefs);
        env->DeleteLocalRef(localRefs);
        if (cls == nullptr) {
            return nullptr;
        }
    } else{
        LOGD("use GlobalRef cached")
    }

    // 初始化一个对象数组，用指定的对象类型
    result = env->NewObjectArray(size, cls, nullptr);
    if (result == nullptr) {
        return nullptr;
    }

    static jmethodID mid = nullptr;
    if (mid == nullptr) {
        mid = env->GetMethodID(cls, "<init>", "(Ljava/lang/String;)V");
        if (mid == nullptr) {
            return nullptr;
        }
    } else {
        LOGD("use method cached")
    }
    char buf[64];
    for (int i = 0; i < size; ++i) {
        sprintf(buf,"%d",i);
        //
        jstring nameStr = env->NewStringUTF(buf);
        // 创建
        jobject jobjMyObj = env->NewObject(cls, mid, nameStr);
        env->SetObjectArrayElement(result, i, jobjMyObj);
        env->DeleteLocalRef(jobjMyObj);
    }

    return result;
}

