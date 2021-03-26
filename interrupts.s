.section .text
.extern _ZN16InterruptManager15handleInterruptEhj

.macro HandleInterruptRequest num
.global _ZN16InterruptManager26HandleInterruptRequest\num\()Ev
    movb $\num, (interruptnumber)
    jump int_bottom
.endm

.macro HandelException num
.global _ZN16InterruptManager19HandleException\num\()Ev
    movb $\num, (interruptnumber)
    jump int_bottom
.endm

HandleInterruptRequest 0x00
HandleInterruptRequest 0x01
HandleInterruptRequest 0x02
HandleInterruptRequest 0x03
HandleInterruptRequest 0x04
HandleInterruptRequest 0x05
HandleInterruptRequest 0x06
HandleInterruptRequest 0x07
HandleInterruptRequest 0x08
HandleInterruptRequest 0x09
HandleInterruptRequest 0x0A
HandleInterruptRequest 0x0B
HandleInterruptRequest 0x0C
HandleInterruptRequest 0x0D
HandleInterruptRequest 0x0E
HandleInterruptRequest 0x0F
HandleInterruptRequest 0x31

HandelException 0x00
HandelException 0x01
HandelException 0x02
HandelException 0x03
HandelException 0x04
HandelException 0x05
HandelException 0x06
HandelException 0x07
HandelException 0x08
HandelException 0x09
HandelException 0x0A
HandelException 0x0B
HandelException 0x0C
HandelException 0x0D
HandelException 0x0E
HandelException 0x0F
HandelException 0x10
HandelException 0x11
HandelException 0x12
HandelException 0x13




int_bottom:
    pusha
    pushl %ds
    pushl %es
    pushl %fs
    pushl %gs

    pushl %esp
    push (interruptnumber)
    
    call _ZN16InterruptManager15handleInterruptEhj
    
    movl %eax, %esp

    popl %gs
    popl %fs
    popl %es
    popl %ds
    popa

    iret

.data
    interruptnumber: .byte 0
