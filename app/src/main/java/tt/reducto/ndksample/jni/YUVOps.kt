package tt.reducto.ndksample.jni

/**
 * YUV操作。
 *
 * <p>......。</p>
 * <ul><li></li></ul>
 * <br>
 * <strong>Time</strong>&nbsp;&nbsp;&nbsp;&nbsp;2020/8/26 15:17<br>
 * <strong>CopyRight</strong>&nbsp;&nbsp;&nbsp;&nbsp;2020, tt.reducto<br>
 *
 * @version  : 1.0.0
 * @author   : hetao
 */
class YUVOps:BaseOps() {

    // NV21转I420
    external fun NV21ToI420(input: ByteArray?, output: ByteArray?, width: Int, height: Int)
    // 旋转I420
    external fun RotateI420(
        input: ByteArray?,
        output: ByteArray?,
        width: Int,
        height: Int,
        rotation: Int
    )

    // NV21转换I420并顺时针旋转90度,可以替换前两个方法
    external fun NV21ToI420andRotate90Clockwise(
        input: ByteArray?,
        output: ByteArray?,
        width: Int,
        height: Int
    )

}