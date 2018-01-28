/*--
* 文件：types.h
* 描述：数据类型
* 时间：2017-1-28
* 作者：一指流沙
*/
#ifndef __TYPES_H
#define __TYPES_H

typedef int     BOOL_T;
typedef void	VOID;

typedef unsigned char       UCHAR;
typedef unsigned short      USHORT;
typedef unsigned int        ULONG_32;
typedef unsigned long long  DULONG;

typedef signed char         CHAR;
typedef signed short        SHORT;
typedef signed int          LONG_32;
typedef signed long long    DLONG;

#define TRUE_T    1
#define FALSE_T   0
#define NULL    ((void *)0)
#define IN
#define OUT
#define INOUT

#define POINT_VIDEO_ADDR(p,	x,	y)	((p)->pcVideoAddr + ((p)->ucBitsPerPixel / 8) * ((p)->usXPixels) * (y - 1) + ((p)->ucBitsPerPixel / 8) * x)
#define POINT_VIDEO_ADDR_EX(p,	x,	y)	((p)->pcVideoAddr + ((p)->ucBitsPerPixel / 4) * ((p)->usXPixels) * (y - 1) + ((p)->ucBitsPerPixel / 4) * x)	
#define RGB_R(x)	((UCHAR)((x & 0x00ff0000) >> 16))
#define RGB_G(x)	((UCHAR)((x & 0x0000ff00) >> 8))
#define RGB_B(x)	((UCHAR)((x & 0x000000ff)))

typedef struct tagRGB 
{
    UCHAR  ucR;
    UCHAR  ucG;
    UCHAR  ucB;
	UCHAR  ucBuf;
} RGB_S;

typedef struct tagXYPoint 
{
    LONG_32 lX;
    LONG_32 lY;
} XY_POINT_S;

typedef struct tagRect 
{
    LONG_32 lLeft;
    LONG_32 lTop;
    ULONG_32 ulWidth;
    ULONG_32 ulHeight;
} RECT_S;

typedef struct tagVideoInfo 
{
    USHORT usVideoMode;
    USHORT usXPixels;
    USHORT usYPixels;
    UCHAR  ucBitsPerPixel;
    UCHAR  ucMemoryModel;
    UCHAR *pcVideoAddr;
} VIDEO_INFO_S;

#endif

