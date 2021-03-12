void printf(char* str){
    //0xb800 is the address for graphic card
    unsigned short* VideoMemory = (unsigned short*)0xb8000;
    for(int i = 0; str[i];i++){
        VideoMemory[i] = (VideoMemory[i] & 0xff00) | str[i];
    }
}

/*since the name of the function will be replaced in C++, so our compiler could not find this function
  with out "extern "C"".

  Therefore, we add extern "C" here to make sure this part will compiled in the way C does.
*/
extern "C" void kernelMain(const void* nultiboot_structure, unsigned int magicnumber){
    printf("hello world");
    while(1);
}

