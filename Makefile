# sudo apt-get install g++ binutils libc6-dev-i386
# sudo apt-get install grub-efi-amd64
#this should replace "sudo apt-get install VirtualBox grub-legacy xorriso"

GCCPARAMS = -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -fno-pie
ASPARAMS = -32
LDPARAMS = -melf_i386

objects = loader.o gdt.o port.o interrupts.o interruptstubs.o kernel.o

#A potential problem here is called "undefined reference to _GLOBAL_OFFSET_TABLE"
#Something about _GLOBAL_OFFSET_TABLE :
#it is nomally dynamic linker lib, within this held structures that most program would share
#in windows is .dll file, while .so in linux.
#
#So when our gcc version is too high, so we have to turn off pie and pic manually.

%.o: %.cpp
	g++ $(GCCPARAMS) -c -o $@ $<

%.o: %.s
	as $(ASPARAMS) -o $@ $<

mykernel.bin: linker.ld $(objects)
	ld $(LDPARAMS) -T $< -o $@ $(objects)

install: mykernel.bin
	sudo cp $< /boot/mykernel.bin

mykernel.iso: mykernel.bin
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp $< iso/boot/
	echo 'set timeout=0'                      > iso/boot/grub/grub.cfg
	echo 'set default=0'                     >> iso/boot/grub/grub.cfg
	echo ''                                  >> iso/boot/grub/grub.cfg
	echo 'menuentry "my os" {' >> iso/boot/grub/grub.cfg
	echo '	multiboot /boot/mykernel.bin'    >> iso/boot/grub/grub.cfg
	echo '	boot'                            >> iso/boot/grub/grub.cfg
	echo '}'                                 >> iso/boot/grub/grub.cfg

	grub-mkrescue --output=$@ iso
	
	rm -rf iso

#run the os with virtual box if you have already created one and named "myos" before
run: mykernel.iso
	(killall virtualboxvm && sleep 1) || true
	virtualboxvm --startvm "myos" &


.PHONY: clean
clean:
	rm -rf ${objects} mykernel.bin mykernel.iso