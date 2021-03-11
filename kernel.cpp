void printf(char* str){
    //0xb800 is the address for graphic card
    unsigned short* VideoMemory = (unsigned short*)0xb8000;
    for(int i = 0; str[i];i++){
        VideoMemory[i] = (VideoMemory[i] & 0xff00) | str[i];
    }
}


void kernelMain(void* nultiboot_structure, unsigned magicnumber){
    printf("hello world");
    while(1);
}

