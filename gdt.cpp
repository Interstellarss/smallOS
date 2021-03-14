#include "gdt.h"

GlobalDescriptorTable::GlobalDescriptorTable()
    : nullSegmentDescriptor(0,0,0),
    unusedSegmentDescriptor(0,0,0),
    codeSegmentDescriptor(0, 64 * 1024 * 1024, 0x9a),
    dataSegmentDescriptor(0, 64 * 1024 * 1024, 0x92){

    uint32_t i[2];

    i[1] = (uint32_t)this;

    i[0] = sizeof(GlobalDescriptorTable) << 16;
    //inline assembly here
    //"p": An operand that is for "load address" and "push address"
    asm volatile("lgdt (%0)": :"p" (((uint8_t *)i) + 2));


}
    