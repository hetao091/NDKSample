package tt.reducto.ndksample.jni

import android.graphics.Bitmap
import tt.reducto.ndksample.JniArray

/**
 * ……。
 *
 * <p>......。</p>
 * <ul><li></li></ul>
 * <br>
 * <strong>Time</strong>&nbsp;&nbsp;&nbsp;&nbsp;2020/8/21 16:13<br>
 * <strong>CopyRight</strong>&nbsp;&nbsp;&nbsp;&nbsp;2020, tt.reducto<br>
 *
 * @version  : 1.0.0
 * @author   : hetao
 */

private class NDKOpsCreator {
    companion object {
        private inline fun <reified T : BaseOps> getOps(clz: Class<T>): T? {
            var ops: T? = null
            try {
                // 利用反射获取空构造创建对象
                ops = Class.forName(clz.name).newInstance() as T
            } catch (e: Exception) {
                e.printStackTrace()
            }
            return ops
        }

        /**
         *
         */
        fun createStringOps(): StringTypeOps = getOps(StringTypeOps::class.java)
            ?: throw NullPointerException("找不到 StringTypeOps() 类")

        /**
         *
         */
        fun createBitmapOps(): BitmapOps = getOps(BitmapOps::class.java)
            ?: throw NullPointerException("找不到 BitmapOps() 类")
    }
}

object NDKHandler {

    //
    private var stringOps: StringTypeOps = NDKOpsCreator.createStringOps()
    //
    private val getBitmapOps = NDKOpsCreator.createBitmapOps()

    fun intPlus(a: Int, b: Int): String? = stringOps.plus(a, b)

    // 字符串拼接
    fun splicingString(str: String?): String? = stringOps.splicingString(str)

    // 字符串截取
    fun splitString(str: String?): String? = stringOps.splitString(str)

    // 直接字符串指针
    fun splicingStringCritical(str: String?): String? = stringOps.splicingStringCritical(str)


    // 字符串反转
    fun reverseString(str: String?): String? = stringOps.reverseString(str)

    //
    // Java 传递 数组 到 Native 进行数组求和
    fun intArraySum(intArray: IntArray): Int = stringOps.intArraySum(intArray)

    // 获得中文字符串
    fun chineseString(str: String?): ByteArray = stringOps.chineseString(str)

    // 获取JNI中创建的对象数组
    fun getNewObjectArray(): Array<JniArray> = stringOps.getNewObjectArray()

    // 获取对象数组中的值
    fun getObjectArrayElement(jniArray: Array<JniArray>): String? =
        stringOps.getObjectArrayElement(jniArray)

    fun testException() = stringOps.exception()
    /**********************************************/


    /**********************************************/



    fun rotateBitmap(bitmap: Bitmap, ops: Int): Bitmap =
        getBitmapOps.rotateBitmap(bitmap, ops)

    fun addBitmapFilter(bitmap: Bitmap) = getBitmapOps.addBitmapFilter(bitmap)

}