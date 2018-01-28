#--
# 文件：boot.s
# 描述：boot
# 时间：2017-1-28
# 作者：一指流沙
#--

.include "kernel.inc"

.code16
.text
.global _start

_start:
    jmp boot_init
	
# 80*25*16, bg blue
init_screen:
    movw    $0x0600,    %ax
    movw    $0x0000,    %cx
    movw    $0x184f,    %dx
    movb    $0x01,      %dh
    int     $0x10
        
    ret

set_video_mode:
    movw    $(BOOT_ADDR + SECTION_SIZE),    %ax
    movw    %ax,    %es
    xorw    %di,    %di
	
    movw    $0x4f00,    %ax
    int     $0x10
    cmp     $0x004f,    %ax
    jne     set_video_0x03
    movw    %es:0x04(%di),  %ax
    cmp     $0x0200,    %ax
    jb      set_video_0x03
    
    movw    $0x4f01,    %ax
    movw    $0x115,     %cx
	int     $0x10
    cmpb    $0x00,      %ah
    jne     set_video_0x03
    cmpb    $0x4f,      %al
    jne     set_video_0x03
    movw    %es:(%di),      %ax
    andw    $0x0080,    %ax
    jz      set_video_0x03

	movw    $0x115,     video_mode
    movw    %es:0x12(%di),  %ax
    movw    %ax,        screen_x
    movw    %es:0x14(%di),  %ax
    movw    %ax,        screen_y
    movb    %es:0x19(%di),  %ah
    movb    %ah,        bits_per_pixel
	movb    %es:0x1b(%di),  %ah
    movb    %ah,        memory_model
    movl    %es:0x28(%di),  %eax
    movl    %eax,       phys_base_ptr

    movw    $0x115,     %bx
    addw    $0x4000,    %bx
    movw    $0x4f02,    %ax
    int     $0x10
    ret
	
# 默认80*25
set_video_0x03:
    movw    $0x0003,    %ax
    int     $0x10
	#TEST 1
	movw	$0xb800,	%ax
	movw	%ax,		%gs
	movb	$0x66,		%gs:0x2
	movb	$0xa4,		%gs:0x3
	#
    movw    $0x0003,    video_mode
    movw    $80,        screen_x
    movw    $25,        screen_y
    movl    $0xb8000,   phys_base_ptr  
	ret

# 从磁盘读kernel
read_disk_kernel:
	lea		read_disk_struct,  	%si
	movb	$0x42,				%ah
	movb	$0x80,				%dl
	int 	$0x13
	ret
	
cp_video_info:
	movw	$IDT_ADDR>>4,	%ax
	movw	%ax,		%es
	movw	$VIDEO_INFO_OFFSET,	%di
	
	movw	video_mode,	%ax
	movw	%ax,		%es:(%di)
	addw	$2,			%di
	
	movw	screen_x,	%ax
	movw	%ax,		%es:(%di)
	addw	$2,			%di
	
	movw	screen_y,	%ax
	movw	%ax,		%es:(%di)
	addw	$2,			%di
	
	movb	bits_per_pixel,	%al
	movb	%al,		%es:(%di)
	addw	$1,			%di
	
	movb	memory_model,	%al
	movb	%al,		%es:(%di)
	addw	$1,			%di
	
	movl	phys_base_ptr,	%eax
	movl	%eax,		%es:(%di)
	ret
	
boot_init:
    movw    %cs,    %ax
    movw    %ax,    %ds
    movw    %ax,    %ss
    movw    %ax,    %sp
    call    init_screen
	call	set_video_mode
	# TEST
	#
	call	cp_video_info
	call    read_disk_kernel
	ljmp	$KERNEL_SEG, $0x0

# 磁盘参数
read_disk_struct:   .word   0x0010      		# struct size
                    .word   KERNEL_PER_SECS	 	# blocks
					.word   0x0000      		# offset
                    .word   KERNEL_SEG 			# section addr
                    .long   0x0001      		# start lba
                    .long   0x0000  
					
video_mode:     .short 0    # 模式
screen_x:       .short 0    # 水平分辨率
screen_y:       .short 0    # 垂直分辨率
bits_per_pixel: .byte 0     # 每个像素占用bit
memory_model:   .byte 0     # 内存模式
phys_base_ptr:  .long 0     # 显存地址    

.org    0x1fe, 0x90
.word   0xaa55




