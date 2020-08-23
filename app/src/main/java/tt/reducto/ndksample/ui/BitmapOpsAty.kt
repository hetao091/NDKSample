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

const val GRAY_SCALE = 1
const val RELIEF = 2

class BitmapOpsAty : AppCompatActivity() {

    private val ops = NDKHandler
    private lateinit var bitmap:Bitmap
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_bitmap)
        //
        setBitmap()
        img_rotate.setImageBitmap(bitmap)


        bt_bitmap_rotate_90.setOnClickListener {

            ops.rotateBitmap(bitmap, ROTATE_90).let {
                img_rotate.setImageBitmap(it)
            }
        }


        bt_bitmap_rotate_180.setOnClickListener {
            ops.rotateBitmap(bitmap, ROTATE_180).let {
                img_rotate.setImageBitmap(it)
            }

        }

        bt_bitmap_mirror.setOnClickListener {
            ops.rotateBitmap(bitmap, MIRROR).let {
                img_rotate.setImageBitmap(it)
            }

        }

        bt_bitmap_filter_gray.setOnClickListener {
            ops.addBitmapFilter(bitmap, GRAY_SCALE).let {
                img_rotate.setImageBitmap(bitmap)
            }
            setBitmap()
        }

        bt_bitmap_filter_relief.setOnClickListener {
            ops.addBitmapFilter(bitmap, RELIEF).let {
                img_rotate.setImageBitmap(bitmap)
            }
            setBitmap()
        }


    }

    private fun setBitmap(){
        bitmap = BitmapFactory.decodeResource(resources, R.drawable.image5)
    }


}