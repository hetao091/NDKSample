package tt.reducto.ndksample.jni

import android.graphics.Bitmap
import tt.reducto.ndksample.jni.BaseOps

/**
 * bitmap 操作。
 *
 * <p>......。</p>
 * <ul><li></li></ul>
 * <br>
 * <strong>Time</strong>&nbsp;&nbsp;&nbsp;&nbsp;2020/8/10 13:12<br>
 * <strong>CopyRight</strong>&nbsp;&nbsp;&nbsp;&nbsp;2020, tt.reducto<br>
 *
 * @version  : 1.0.0
 * @author   : hetao
 */
class BitmapOps : BaseOps() {

    // 顺时针旋转 90° 的操作
    external fun rotateBitmap(bitmap: Bitmap, ops: Int): Bitmap
    // 滤镜
    external fun addBitmapFilter(bitmap: Bitmap)

    external fun handleBitmapForSinglePixel(bitmap: Bitmap)
}