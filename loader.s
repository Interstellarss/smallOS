.set MAGIC, 0x1BADB002
.set FLAGS, (1<<0 | 1<<1)
.set CHECKSUM, -(MAGIC + FLAGS)

//use grub to load, so a multiboot structure is needed
.section .multiboot
  .long MAGIC
  .long FLAGS
  .long CHECKSUM


.extern _kernelMain
.extern _callConstructors


.section .text

.global loader
loader:
  mov $kernel_stack, %esp

  call callConstructors

  push %eax
  push %ebx
  call kernelMain 

_stop:
  cli
  hlt
  jmp _stop


.section .bss
.space 2*1024*1024

kernel_stack:
  