package tt.reducto.ndksample.ui

import android.graphics.*
import android.os.Bundle
import android.util.Log
import androidx.appcompat.app.AppCompatActivity
import kotlinx.android.synthetic.main.activity_bitmap.*
import tt.reducto.ndksample.jni.NDKHandler
import tt.reducto.ndksample.R
import java.nio.ByteBuffer


/**
 * ……。
 *
 * <p>......。</p>
 * <ul><li></li></ul>
 * <br>
 * <strong>Time</strong>&nbsp;&nbsp;&nbsp;&nbsp;2020/8/12 17:49<br>
 * <strong>CopyRight</strong>&nbsp;&nbsp;&nbsp;&nbsp;2020, tt.reducto<br>
 *
 * @version  : 1.0.0
 * @author   : hetao
 *
 */

const val ROTATE_90 = 0
const val ROTATE_180 = 1
const val MIRROR = 2

class BitmapOpsAty : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_bitmap)
        val bitmap = BitmapFactory.decodeResource(resources, R.drawable.image5)

        val tempBitmap = Bitmap.createBitmap(1, 1, Bitmap.Config.ARGB_8888)
        val canvas = Canvas(tempBitmap)
        val paint = Paint()
        paint.style = Paint.Style.FILL
        paint.color = Color.rgb(0x11,0x22,0x33)
        canvas.drawRect(0f, 0f, tempBitmap.width.toFloat(), tempBitmap.height.toFloat(), paint)

        val byteSize = tempBitmap.allocationByteCount
        val byteBuffer: ByteBuffer = ByteBuffer.allocateDirect(byteSize)
        tempBitmap.copyPixelsToBuffer(byteBuffer)
        byteBuffer.rewind()
        val out = ByteArray(4)
        byteBuffer[out, 0, out.size]
        val pixel = tempBitmap.getPixel(0, 0)
        val a = Color.alpha(pixel)
        val r = Color.red(pixel)
        val g = Color.green(pixel)
        val b = Color.blue(pixel)
        Log.d("pixel = ", "$pixel")
        Log.d("pixel = ", "a= ${a},r= ${r},g=${g }, b=${b}")
        Log.d(
            "pixel 16 = ",
            "a= ${a.toString(16)},r= ${r.toString(16)},g=${g.toString(16)}, b=${b.toString(16)}"
        )
        for (element in out) {
            Log.d("out old= ", "$element")
            Log.d("out = ", element.toString(16))
        }


        img_rotate.setImageBitmap(bitmap)

        // 测试。
        NDKHandler.makeBitmapForSinglePixel(tempBitmap)

        bt_bitmap_rotate_90.setOnClickListener {

            NDKHandler.rotateBitmap(bitmap, ROTATE_90).let {
                img_rotate.setImageBitmap(it)
            }
        }


        bt_bitmap_rotate_180.setOnClickListener {
            NDKHandler.rotateBitmap(bitmap, ROTATE_180).let {
                img_rotate.setImageBitmap(it)
            }

        }

        bt_bitmap_mirror.setOnClickListener {
            NDKHandler.rotateBitmap(bitmap, MIRROR).let {
                img_rotate.setImageBitmap(it)
            }

        }

        bt_bitmap_bw.setOnClickListener {
            NDKHandler.addBitmapFilter(bitmap).let {
                img_rotate.setImageBitmap(bitmap)
            }
        }

        bt_bitmap_pointer_rotate_90.setOnClickListener {
            NDKHandler.rotateBitmapWithPointer(bitmap, ROTATE_90).let {
                img_rotate.setImageBitmap(bitmap)
            }
        }

    }
}