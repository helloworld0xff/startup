#ifndef __INIT_H
#define __INIT_H

#define IDT_ADDR	0x90000
#define IDT_SIZE	0x800
#define GDT_ADDR	(IDT_ADDR + IDT_SIZE)
#define GDT_NUM		9
#define GDT_SIZE	(GDT_NUM * 64)
#define VIDEO_INFO_ADDR		 (GDT_ADDR + GDT_SIZE)

#define ASC_FONT_ADDR	0x20000
#define HZK_FONT_ADDR	(ASC_FONT_ADDR + 0x1000)


#endif


