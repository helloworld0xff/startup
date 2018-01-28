#--
# 文件：kernel.inc
# 描述：内核配置
# 时间：2017-1-28
# 作者：一指流沙
#--

.equ	SECTION_SIZE是 		0x200 						# 扇区大小
.equ	BOOT_ADDR, 			0x7c00 						# 起始地址
.equ 	KERNEL_ADDR, 		0x10000 					# kernel加载地址
.equ	KERNEL_SEG,			0x1000
.equ 	STACK_BOOT_BP,		0x7c00						# boot栈底地址
.equ    KERNEL_SIZE,		0x3f8						# kernel size 512 clicks
.equ 	KERNEL_PER_SECS,	0x007f						# 每次读取扇区数

# irq 
	
.equ 	IDT_ADDR, 			0x90000 					# 中断向量表地址
.equ 	IDT_SIZE,			0x800       				# 中断向量表大小 

# gdt tables
#
# 0. null
# 1. LDT
# 2. TSS
# 3. TLS1
# 4. KERNEL_SS
# 5. KERNEL_CS
# 6. KERNEL_DS
# 7. USR_CS
# 8. USR_DS

.equ 	GDT_ADDR,			(IDT_ADDR + IDT_SIZE)		# 全局描述符表地址
.equ 	GDT_NUM,			9                           # 全局描述符个数
.equ 	GDT_SIZE,          	(GDT_NUM * 64)				# 全局描述符大小
.equ 	KERNEL_CS,			0xc098100000007f			# kernel cs
.equ	KERNEL_CS_LEFT,		0x0000007f
.equ	KERNEL_CS_RIGHT,	0x00c09800

.equ	KERNEL_DS,			0xcf92000000ffff			# kernel ds
.equ	KERNEL_DS_LEFT,		0x0000ffff
.equ	KERNEL_DS_RIGHT,	0x00cf9200

.equ	KERNEL_SS,			0x40960200000400
.equ	KERNEL_SS_LEFT,		0x00000400
.equ	KERNEL_SS_RIGHT,	0x00409602

.equ	KERNEL_SS_SECT,		0x0020
.equ 	KERNEL_CS_SECT,		0x0028
.equ	KERNEL_DS_SECT,		0x0030

# video pram
#
# video_mode:     .short 0    # 模式
# screen_x:       .short 0    # 水平分辨率
# screen_y:       .short 0    # 垂直分辨率
# bits_per_pixel: .byte 0     # 每个像素占用bit
# memory_model:   .byte 0     # 内存模式
# phys_base_ptr:  .long 0     # 显存地址

.equ	VIDEO_INFO_ADDR,		(GDT_ADDR + GDT_SIZE)		# video addr
.equ	VIDEO_INFO_OFFSET,		(VIDEO_INFO_ADDR - IDT_ADDR)

# sys pram
.equ	SYS_LOGO_ADDR,	0x100200   # logo addr
.equ	SYS_ZK_ADDR,	0x200000   # 字库地址
.equ	SYS_ZK_SEC_ADDR,	0x80
.equ    SYS_ZK_SECTS,	0x20B
.equ 	SYS_ZK_SIZE,	0x41560	   # 字库大小





