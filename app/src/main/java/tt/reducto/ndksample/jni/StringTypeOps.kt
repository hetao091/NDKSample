package tt.reducto.ndksample.jni

import tt.reducto.ndksample.JniArray

/**
 * JNI函数。
 *
 * <p>......。</p>
 * <ul><li></li></ul>
 * <br>
 * <strong>Time</strong>&nbsp;&nbsp;&nbsp;&nbsp;2020/7/16 13:12<br>
 * <strong>CopyRight</strong>&nbsp;&nbsp;&nbsp;&nbsp;2020, tt.reducto<br>
 *
 * @version  : 1.0.0
 * @author   : hetao
 */
class StringTypeOps : BaseOps() {

    //  整数相加
    external fun plus(a: Int, b: Int): String

    // 字符串拼接
    external fun splicingString(str: String?): String?

    // 字符串截取
    external fun splitString(str: String?): String?

    // 直接字符串指针
    external fun splicingStringCritical(str: String?): String?


    // 字符串反转
    external fun reverseString(str: String?): String?

    //
    // Java 传递 数组 到 Native 进行数组求和
    external fun intArraySum(intArray: IntArray): Int

    // 获得中文字符串
    external fun chineseString(str: String?): ByteArray

    // 获取JNI中创建的对象数组
    external fun getNewObjectArray(): Array<JniArray>

    // 获取对象数组中的值
    external fun getObjectArrayElement(jniArray: Array<JniArray>): String?

    external fun exception()
}