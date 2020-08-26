# 设置构建本地库所需的最小版本
cmake_minimum_required(VERSION 3.4.1)

#############################################
# jni
add_library(
        # 设置库名字 即 SO 文件的名称
        TTNative
        # STATIC：静态库，是目标文件的归档文件，在链接其它目标的时候使用。
        # SHARED：动态库，会被动态链接，在运行时被加载。
        # MODULE：模块库，是不会被链接到其它目标中的插件，但是可能会在运行时使用dlopen-系列的函数动态链接。
        SHARED
        # 要编译的源代码文件
        jni/StringTypes.cpp
        jni/BitmapTypes.cpp
        jni/YuvTypes.cpp
)
# 添加yuv静态库
add_library(
        yuv_static
        STATIC
        IMPORTED
        )

# # 引入头文件
include_directories(${CMAKE_SOURCE_DIR}/include/)

include_directories(${CMAKE_SOURCE_DIR}/common/)

include_directories(
        ${CMAKE_SOURCE_DIR}/yuv/include/
        ${CMAKE_SOURCE_DIR}/yuv/include/libyuv/
        )

find_library(
        #
        log-lib
        #
        log)

set_target_properties(
        yuv_static
        PROPERTIES IMPORTED_LOCATION
        /Users/hetao/Documents/newSVNApp/NDKSample/app/src/main/jniLibs/${ANDROID_ABI}/libyuv_static.a)

# 关联 原生库能够调用 log 库中的函数
target_link_libraries(
        #自己的需要生成的动态库
        TTNative
        # 操作bitmap
        jnigraphics
        #yuv
        yuv_static
        # 链接log 库
        ${log-lib})

#############################################






