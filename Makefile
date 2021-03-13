# sudo apt-get install g++ binutils libc6-dev-i386

GCCPARAMS = -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -fno-pie
ASPARAMS = --32
LDPARAMS = -melf_i386 -no-pie

objects = loader.o kernel.o

#A potential problem here is called "undefined reference to _GLOBAL_OFFSET_TABLE"\
Something about _GLOBAL_OFFSET_TABLE :\
it is nomally dynamic linker lib, within this held structures that most program would share\
in windows is .dll file, while .so in linux\
\
So when our gcc version is too high, so we have to turn off pie and pic manually

%.o: %.cpp
	g++ $(GCCPARAMS) -c -o $@ $<

%.o: %.s
	as $(ASPARAMS) -o $@ $<

mykernel.bin: linker.ld $(objects)
	ld $(LDPARAMS) -T $< -o $@ $(objects)

install: mykernel.bin
	sudo cp $< /boot/mykernel.bin
