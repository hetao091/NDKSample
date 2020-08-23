package tt.reducto.ndksample

import android.content.Intent
import android.os.Bundle
import android.util.Log
import android.view.Menu
import android.view.MenuInflater
import android.view.MenuItem
import androidx.appcompat.app.AppCompatActivity
import kotlinx.android.synthetic.main.activity_main.*
import tt.reducto.ndksample.jni.NDKHandler
import tt.reducto.ndksample.jni.StringTypeOps
import tt.reducto.ndksample.ui.BitmapOpsAty


class MainActivity : AppCompatActivity() {

    private val tmpStr = "hello from jni中文"
    private val ops = NDKHandler

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)


        //
        // 求和操作就是一般的类型相加的整数
        tv_main_plus.setOnClickListener {
            // 求和操作
            tv_main_plus.text = ops.intPlus(10, 10)
        }

        tv_main_splicing.setOnClickListener {
            // 拼接操作
            tv_main_splicing.text = ops.splicingString(tmpStr) ?: ""
            // 6
        }
        //
        tv_main_reverse.setOnClickListener {
            // 翻转
            tv_main_reverse.text = ops.reverseString(tmpStr) ?: ""
        }

        tv_main_split.setOnClickListener {
            tv_main_split.text = ops.splitString(tmpStr) ?: ""
        }

        //
        tv_main_array_critical.setOnClickListener {
            //
            tv_main_array_critical.text =
                ops.splicingStringCritical("MainActivity") ?: ""
        }

        tv_main_array_sum.setOnClickListener {
            tv_main_array_sum.text = ops.intArraySum(intArrayOf(1, 2, 3, 4)).toString()
        }

        tv_main_splicing_chinese.setOnClickListener {
            val rr =ops.chineseString(tmpStr)
            val nn = String(rr, Charsets.UTF_8)
            tv_main_splicing_chinese.text = nn
        }

        tv_main_object_array.setOnClickListener {
            val tmp = arrayOf(JniArray(msg = "1"), JniArray(msg = "2"))
            val result = ops.getObjectArrayElement(tmp) ?: ""
            tv_main_object_array.text = result

        }

        tv_main_get_object_array.setOnClickListener {
            val result = ops.getNewObjectArray()
//            result.forEach {
            Log.d("get_object_array", result.size.toString())
//            }

            tv_main_get_object_array.text = result.contentToString()

        }

        tv_main_exception.setOnClickListener {
            try {
                ops.testException()
            }
//            catch (e: Throwable) {
//                Log.d("tv_main_object_array::","Throwable")
//                e.printStackTrace()
//            }
            catch (e: ArithmeticException) {
                Log.d("tv_main_object_array::", "ArithmeticException")
                e.printStackTrace()
            }
        }

    }


    override fun onCreateOptionsMenu(menu: Menu): Boolean {
        val inflater: MenuInflater = menuInflater
        inflater.inflate(R.menu.main_menu, menu)
        return true
    }

    override fun onOptionsItemSelected(item: MenuItem): Boolean {
        // Handle item selection
        return when (item.itemId) {
            R.id.menu_main_to_bitmap -> {
                val intent = Intent(this, BitmapOpsAty::class.java)
                startActivity(intent)
                true
            }
            R.id.help -> {

                true
            }
            else -> super.onOptionsItemSelected(item)
        }
    }

}