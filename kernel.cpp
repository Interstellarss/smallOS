#include "types.h"
#include "gdt.h"
#include "interrupts.h"

void printf(const char* str){
    //0xb800 is the address for graphic card
    static uint16_t* VideoMemory = (uint16_t*)0xb8000;

    static uint8_t x = 0, y = 0;
    for(int i = 0; str[i];i++){

        switch (str[i])
        {
        case '\n':
            y++;
            x = 0;
            break;
        
        default:
            VideoMemory[80 * y + x] = (VideoMemory[80 * y + x] & 0xff00) | str[i];
            x++;
            break;
        }

        if(x >= 80){
            x = 0;
            y++;
        }

        if(y >= 25){
            for(y = 0; y < 25; y++){
                for(x = 0; x < 80; x++){
                    VideoMemory[80 * y + x] = (VideoMemory[ 80 * y + x] & 0xff00) | ' ';
                }
            }
            x = 0; y = 0;
        }
    
    }
}


/*since the name of the function will be replaced in C++, so our compiler could not find this function
  with out "extern "C"".

  Therefore, we add extern "C" here to make sure this part will compiled in the way C does.
*/
typedef void (*constructor)();

extern "C" constructor start_ctors;

extern "C" constructor end_ctors;

extern "C" void callConstructors(){
    for(constructor* i = &start_ctors; i != &end_ctors; i++){
        (*i)();
    }
}



extern "C" void kernelMain(const void* multiboot_structure, uint32_t magicnumber){
    printf("hello world!\n");
    //printf((char*)'\n');
    //printf("cc");

    GlobalDescriptorTable gdt;

    InterruptManager interrupts(0x20, &gdt);

    interrupts.Activate();

    while(1);
}

