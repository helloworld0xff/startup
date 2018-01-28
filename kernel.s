#--
# 文件：kernel.s
# 描述：kernel
# 时间：2017-1-28
# 作者：一指流沙
#--
.include "kernel.inc"

.code16

.text
.global _start

_start:
	jmp		start_kernel

	
# 0. null
# 1. LDT
# 2. TSS
# 3. TLS1
# 4. TLS2
# 5. KERNEL_CS
# 6. KERNEL_DS
# 7. USR_CS
# 8. USR_DS	
install_gdt_desc:
	pushw	%ds
	movw	$GDT_ADDR>>4,	%bx
	movw	%bx,			%ds
	xorw	%bx,			%bx
	movl	$0x0,			(%bx)
	movl	$0x0,			4(%bx)
	addw	$8,				%bx
	
	movl    $0x0,			(%bx)
	movl	$0x0,			4(%bx)
	addw	$8,				%bx
	
	movl    $0x0,			(%bx)
	movl	$0x0,			4(%bx)
	addw	$8,				%bx
	
	movl    $0x0,			(%bx)
	movl	$0x0,			4(%bx)
	addw	$8,				%bx
	
	movl    $KERNEL_SS_LEFT, (%bx)
	movl	$KERNEL_SS_RIGHT, 4(%bx)
	addw	$8,				%bx
	
	movl	$KERNEL_CS_LEFT, (%bx)
	movl	$KERNEL_CS_RIGHT, 4(%bx)
	addw	$8,				%bx
	
	movl	$KERNEL_DS_LEFT, (%bx)
	movl	$KERNEL_DS_RIGHT, 4(%bx)
	addw	$8,				%bx

	movl    $0x0,			(%bx)
	movl	$0x0,			4(%bx)
	addw	$8,				%bx
	
	movl    $0x0,			(%bx)
	movl	$0x0,			4(%bx)

	pop		%ds
	ret
	
# 进入保护模式
entry_protect_mode:
	cli
	lgdt	gdt_ptr
1:
	inb		$0x64,	%al
	testb	$0x02,	%al
	jnz		1b
	movb	$0xdf,	%al
	outb	%al,	$0x64
	movl	%cr0,	%eax
	orl		$0x01,	%eax
	movl	%eax,	%cr0
	ret

read_disk_struct:   .word   0x0010      		# struct size
                    .word   0x007f	 			# blocks
					.word   0x0000      		# offset
                    .word   0x2000 				# section addr
                    .long   SYS_ZK_SEC_ADDR     # start lba
                    .long   0x0000  
	
# test zk
load_zk:
	lea		read_disk_struct,  	%si
	movb	$0x42,				%ah
	movb	$0x80,				%dl
	int 	$0x13
	
	movw	$(0x20000+0xfe00)>>4,	6(%si)
	movl	$SYS_ZK_SEC_ADDR+0x007f,	8(%si)
	movb	$0x42,				%ah
	movb	$0x80,				%dl
	int 	$0x13
	
	movw	$(0x20000+0xfe00*2)>>4,	6(%si)
	movl	$SYS_ZK_SEC_ADDR+0x007f*2,	8(%si)
	movb	$0x42,				%ah
	movb	$0x80,				%dl
	int 	$0x13
	
	movw	$(0x20000+0xfe00*3)>>4,	6(%si)
	movl	$SYS_ZK_SEC_ADDR+0x007f*3,	8(%si)
	movb	$0x42,				%ah
	movb	$0x80,				%dl
	int 	$0x13
	
	movw	$(0x20000+0xfe00*4)>>4,	6(%si)
	movl	$SYS_ZK_SEC_ADDR+0x007f*4,	8(%si)
	movb	$0x42,				%ah
	movb	$0x80,				%dl
	int 	$0x13
	ret

mv_kernel:
	pushw	%ds
	movw    $KERNEL_ADDR>>4, %ax
	movw	%ax,			%ds
	xorw	%di,			%di
	movw	$0x0,			%ax			
	movw	%ax,			%es
	xorw	%si,			%si
	movw	$0xfe00,		%cx
	rep
	movsb
	popw	%ds
	ret
	
start_kernel:
    movw    %cs,    %ax
    movw    %ax,    %ds
	call 	load_zk
	call	mv_kernel
	
	ljmp	$0x0, $entry_init
		
entry_init:
	call	install_gdt_desc
	call 	entry_protect_mode
	ljmpl	$KERNEL_CS_SECT, $protect_mode
			
gdt_ptr:    .word   GDT_SIZE
            .long   GDT_ADDR
			
.code32
protect_mode:	
	movw	$KERNEL_DS_SECT, %ax
	movw	%ax,			%ds
	movw	%ax,			%es
	movw	%ax,			%fs
	movw	%ax,			%gs	
	movw	$KERNEL_SS_SECT, %ax	# kernel ss 1K
	movw	%ax,			%ss
	xorl	%esp,			%esp
	xorl	%ebp,			%ebp
	#test video ram
#	movl	VIDEO_INFO_ADDR + 8,	%ebx
#	movl	$100,	%ecx
#	addl	$800,	%ebx
#d:
#	movb	$225, (%ebx)
#	inc 	%ebx
#	movb	$21, (%ebx)
#	inc 	%ebx
#	movb	$189, (%ebx)
#	inc 	%ebx
#	loop 	d
	#
	call 	INIT_Main
	
1:
	jmp 	1b

.align 4	
.data

    