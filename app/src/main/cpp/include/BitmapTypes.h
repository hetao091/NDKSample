//
// Created by hetao on 2020/8/9.
//

#ifndef NDKSAMPLE_BITMAPTYPES_H
#define NDKSAMPLE_BITMAPTYPES_H


class BitmapTypes {

};

#define MAKE_BGR565(b, g, r) ((((r) >> 3) << 11) | (((g) >> 2) << 5) | ((b) >> 3))

#define MAKE_ABGR(a, b, g, r) (((a&0xff)<<24) | ((b & 0xff) << 16) | ((g & 0xff) << 8 ) | (r & 0xff))


#define BGR565_B(p) ((((p) & 0xF800) >> 11) << 3)
#define BGR565_G(p) ((((p) & 0x7E0 ) >> 5)  << 2)
#define BGR565_R(p) ( ((p) & 0x1F  )        << 3)

#define BGR_8888_A(p) ((p & (0xff<<24))   >> 24 )
#define BGR_8888_B(p) ((p & (0xff << 16)) >> 16 )
#define BGR_8888_G(p) ((p & (0xff << 8))  >> 8 )
#define BGR_8888_R(p) (p & (0xff) )

#endif //NDKSAMPLE_BITMAPTYPES_H
