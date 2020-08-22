//
// Created by hetao on 2020/8/9.
//

#ifndef NDKSAMPLE_BITMAPTYPES_H
#define NDKSAMPLE_BITMAPTYPES_H


class BitmapTypes {

};

#define MAKE_RGB565(r, g, b) ((((r) >> 3) << 11) | (((g) >> 2) << 5) | ((b) >> 3))
#define MAKE_ARGB(a, r, g, b) ((a&0xff)<<24) | ((r&0xff)<<16) | ((g&0xff)<<8) | (b&0xff)
#define MAKE_ARGB_U(a, r, g, b) ((a&0xff)<<24) | ((r&0xff)<<16) | ((g&0xff)<<8) | (b&0xff)

#define RGB565_R(p) ((((p) & 0xF800) >> 11) << 3)
#define RGB565_G(p) ((((p) & 0x7E0 ) >> 5)  << 2)
#define RGB565_B(p) ( ((p) & 0x1F  )        << 3)

#define RGB8888_A(p) ((p & (0xff<<24))   >> 24 )
#define RGB8888_B(p) ((p & (0xff << 16)) >> 16 )
#define RGB8888_G(p) ((p & (0xff << 8))  >> 8 )
#define RGB8888_R(p) (p & (0xff) )

#endif //NDKSAMPLE_BITMAPTYPES_H
