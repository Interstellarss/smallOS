#include "types.h"

void printf(char* str){
    //0xb800 is the address for graphic card
    static uint16_t* VideoMemory = (unsigned uint16_t*)0xb8000;
    for(int i = 0; str[i];i++){
        VideoMemory[i] = (VideoMemory[i] & 0xff00) | str[i];
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
    printf((char*)"hello world!");
    while(1);
}

