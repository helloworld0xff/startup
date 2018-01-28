#include "init.h"
#include "types.h"

/* test */
char a0=0x70;
char b0=0xa5;

const VIDEO_INFO_S *gpstVideoInfo = NULL;

VOID INIT_TestVideoInit(VOID)
{
	gpstVideoInfo = (VIDEO_INFO_S *)VIDEO_INFO_ADDR;
}

VOID INIT_TestVideo(VOID)
{
	UCHAR *pcRam = NULL;
	LONG_32 lIdx = 0;	
	
	/* 画线 Y, X */
	pcRam = POINT_VIDEO_ADDR(gpstVideoInfo, 2, 2);
	for (lIdx = 0; lIdx < 100; lIdx++)
	{
		pcRam[0] = 225;
		pcRam[1] = 21;
		pcRam[2] = 189;
		pcRam += 3;
	}

}

VOID INIT_TestSetPixel(IN LONG_32 lLeft, IN LONG_32 lTop, IN ULONG_32 ulRgb)
{
	UCHAR *pcRam = NULL;
		
	/* 画点 Y, X */
	pcRam = POINT_VIDEO_ADDR(gpstVideoInfo, lLeft, lTop);
	pcRam[0] = RGB_R(ulRgb);
	pcRam[1] = RGB_G(ulRgb);
	pcRam[2] = RGB_B(ulRgb);

}

VOID INIT_TestPrintAsc(IN CHAR cAsc, IN LONG_32 lLeft, IN LONG_32 lTop, IN ULONG_32 ulRgb)
{
	UCHAR *pAsc = NULL;
	LONG_32 lX = 0;
	LONG_32 lY = 0;
	UCHAR ucBit = 0;
	
	pAsc = (UCHAR *)(ASC_FONT_ADDR + cAsc * 16);
	for (lY = 0; lY < 18; lY++)
	{
		ucBit = 1 << 7;
		for (lX = 0; lX < 8; lX++)
		{
			if ((*pAsc) & ucBit)
			{
				INIT_TestSetPixel(lLeft + lX, lTop + lY, ulRgb);
			}	
			ucBit >>= 1;
		}
		pAsc++;
	}
}

////

VOID INIT_TestSetPixelEx(IN LONG_32 lLeft, IN LONG_32 lTop, IN ULONG_32 ulRgb)
{
	UCHAR *pcRam = NULL;
		
	/* 画点 Y, X */
	pcRam = POINT_VIDEO_ADDR_EX(gpstVideoInfo, lLeft, lTop);
	pcRam[0] = RGB_R(ulRgb);
	pcRam[1] = RGB_G(ulRgb);
	pcRam[2] = RGB_B(ulRgb);

}

VOID INIT_TestPrintAscEx(IN CHAR cAsc, IN LONG_32 lLeft, IN LONG_32 lTop, IN ULONG_32 ulRgb)
{
	UCHAR *pAsc = NULL;
	LONG_32 lX = 0;
	LONG_32 lY = 0;
	UCHAR ucBit = 0;
	
	pAsc = (UCHAR *)(ASC_FONT_ADDR + cAsc * 16);
	for (lY = 0; lY < 18; lY++)
	{
		ucBit = 1 << 7;
		for (lX = 0; lX < 8; lX++)
		{
			if ((*pAsc) & ucBit)
			{
				INIT_TestSetPixelEx(lLeft + lX, lTop + lY, ulRgb);
			}	
			ucBit >>= 1;
		}
		pAsc++;
	}
}

VOID INIT_TestPrintAscStringEx(IN CHAR *pcStr, IN LONG_32 lLeft, IN LONG_32 lTop, IN ULONG_32 ulRgb)
{
	CHAR *pcTmp = pcStr;
	LONG_32 lIdx = 0;
	
	while ('\0' != *pcTmp)
	{
		INIT_TestPrintAscEx(*pcTmp, lLeft + lIdx, lTop, ulRgb);
		pcTmp++;
		lIdx += 8;
	}
}

/////

VOID INIT_TestPrintAscString(IN CHAR *pcStr, IN LONG_32 lLeft, IN LONG_32 lTop, IN ULONG_32 ulRgb)
{
	CHAR *pcTmp = pcStr;
	LONG_32 lIdx = 0;
	
	while ('\0' != *pcTmp)
	{
		INIT_TestPrintAsc(*pcTmp, lLeft + lIdx, lTop, ulRgb);
		pcTmp++;
		lIdx += 8;
	}
}

VOID INIT_TestPrintHz(IN CHAR *szCh, IN LONG_32 lLeft, IN LONG_32 lTop, IN ULONG_32 ulRgb)
{
	ULONG_32 ulOffset = 0;
	LONG_32 lX = 0;
	LONG_32 lY = 0;
	UCHAR *pcHz = NULL;
	UCHAR ucBit = 0;

	ulOffset = (94*(((UCHAR)szCh[0] - 0xa0) -1 ) + (((UCHAR)szCh[1] - 0xa0) - 1)) * 32;
	pcHz = (UCHAR *)(HZK_FONT_ADDR + ulOffset);

	for (lY = 0; lY < 16; lY++)
	{
		ucBit = 1 << 7;
		for (lX = 0; lX < 16; lX++)
		{
			if (*(pcHz + (lX & 8 ? 1 : 0)) & ucBit)
			{
				INIT_TestSetPixel(lLeft + lX, lTop + lY, ulRgb);
			}
			if ((ucBit >>= 1) == 0)
			{
				ucBit = 1 << 7;
			}	
		}
		pcHz += 2;
	}

}

VOID INIT_TestPrintHzString(IN CHAR *pcStr, IN LONG_32 lLeft, IN LONG_32 lTop, IN ULONG_32 ulRgb)
{
	CHAR *pcTmp = pcStr;
	LONG_32 lIdx = 0;
	
	while ('\0' != *pcTmp)
	{
		INIT_TestPrintHz(pcTmp, lLeft + lIdx, lTop, ulRgb);
		pcTmp += 2;
		lIdx += 16;
	}
}

VOID INIT_Main(VOID)
{

	/* test */
	/*
	__asm__("movb  %0, 0xb8004;	\
			 movb  %1, 0xb8005; "
			:
			: "a"(a0), "b"(b0)
			:); 
	*/
	LONG_32 lLen = 0;
	ULONG_32 ulRgb0 = 0x90EE90;
	ULONG_32 ulRgb1 = 0xFF7F50;
	INIT_TestVideoInit();
	INIT_TestPrintAscStringEx("PbitOS", 160, 20, ulRgb0);
	INIT_TestPrintAscString("PbitOS(Hinux kernel......)", 40, 80, ulRgb1);
	INIT_TestPrintHzString("全球操作系统领导者！深夜时分，海康大华大楼，灯火通明如白昼！", 40+27*8, 80, ulRgb1);
	INIT_TestPrintHzString("写字楼里写字间，写字间里程序员；程序人员写程序，又拿程序换酒钱。", 40, 120, ulRgb1);
	INIT_TestPrintHzString("酒醉酒醒日复日，码来码去年复年；比尔能搞个微软，我咋不能捞点钱。", 40, 140, ulRgb1);
	INIT_TestPrintAscString("Loading ......", 10, 400, ulRgb1);
	
}


