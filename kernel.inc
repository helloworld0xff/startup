#--
# �ļ���kernel.inc
# �������ں�����
# ʱ�䣺2017-1-28
# ���ߣ�һָ��ɳ
#--

.equ	SECTION_SIZE�� 		0x200 						# ������С
.equ	BOOT_ADDR, 			0x7c00 						# ��ʼ��ַ
.equ 	KERNEL_ADDR, 		0x10000 					# kernel���ص�ַ
.equ	KERNEL_SEG,			0x1000
.equ 	STACK_BOOT_BP,		0x7c00						# bootջ�׵�ַ
.equ    KERNEL_SIZE,		0x3f8						# kernel size 512 clicks
.equ 	KERNEL_PER_SECS,	0x007f						# ÿ�ζ�ȡ������

# irq 
	
.equ 	IDT_ADDR, 			0x90000 					# �ж���������ַ
.equ 	IDT_SIZE,			0x800       				# �ж���������С 

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

.equ 	GDT_ADDR,			(IDT_ADDR + IDT_SIZE)		# ȫ������������ַ
.equ 	GDT_NUM,			9                           # ȫ������������
.equ 	GDT_SIZE,          	(GDT_NUM * 64)				# ȫ����������С
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
# video_mode:     .short 0    # ģʽ
# screen_x:       .short 0    # ˮƽ�ֱ���
# screen_y:       .short 0    # ��ֱ�ֱ���
# bits_per_pixel: .byte 0     # ÿ������ռ��bit
# memory_model:   .byte 0     # �ڴ�ģʽ
# phys_base_ptr:  .long 0     # �Դ��ַ

.equ	VIDEO_INFO_ADDR,		(GDT_ADDR + GDT_SIZE)		# video addr
.equ	VIDEO_INFO_OFFSET,		(VIDEO_INFO_ADDR - IDT_ADDR)

# sys pram
.equ	SYS_LOGO_ADDR,	0x100200   # logo addr
.equ	SYS_ZK_ADDR,	0x200000   # �ֿ��ַ
.equ	SYS_ZK_SEC_ADDR,	0x80
.equ    SYS_ZK_SECTS,	0x20B
.equ 	SYS_ZK_SIZE,	0x41560	   # �ֿ��С




