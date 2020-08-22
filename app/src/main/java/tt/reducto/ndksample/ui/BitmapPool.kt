package tt.reducto.ndksample.ui

import android.graphics.Bitmap
import android.graphics.BitmapFactory
import androidx.core.graphics.BitmapCompat

/**
 * ……。
 *
 * <p>......。</p>
 * <ul><li></li></ul>
 * <br>
 * <strong>Time</strong>&nbsp;&nbsp;&nbsp;&nbsp;2020/8/13 20:12<br>
 * <strong>CopyRight</strong>&nbsp;&nbsp;&nbsp;&nbsp;2020, tt.reducto<br>
 *
 * @version  : 1.0.0
 * @author   : hetao
 */
class BitmapPool {

    fun getARGB8888Bitmap(w: Int, h: Int): Bitmap {
        return Bitmap.createBitmap(w, h, Bitmap.Config.ARGB_8888)
    }
}