#include "interrupts.h"

void printf(const char*);

InterruptManager::GateDescriptor InterruptManager::interruptDescriptorTable[256];

void InterruptManager::SetInterruptDescriptorTableEntry(
    uint8_t interruptNumber,
    uint16_t codeSegementSelectorOffset,
    void (*handler)(),
    uint8_t DescriptorPrivilegeLevel,
    uint8_t DescriptorType){

        const uint8_t IDT_DESC_PRESENT = 0x80;

        interruptDescriptorTable[interruptNumber].handlerAddressLowBits = ((uint32_t)handler) & 0xffff;
        interruptDescriptorTable[interruptNumber].handlerAddressHighBis = ((uint32_t)handler >> 16) & 0xffff;

        interruptDescriptorTable[interruptNumber].gdt_codeSegmentSelector = codeSegementSelectorOffset;

        interruptDescriptorTable[interruptNumber].access = IDT_DESC_PRESENT | (DescriptorPrivilegeLevel << 5) | DescriptorType;

        interruptDescriptorTable[interruptNumber].reserved = 0;
}

InterruptManager::InterruptManager(uint16_t hardwareInterruptOffset, GlobalDescriptorTable* gdt){

    this->hardwareInterruptOffset = hardwareInterruptOffset;

    uint16_t codeSegment = gdt -> CodeSegmentDescriptor();

    const uint8_t IDT_INTERRUPT_GATE = 0xe;

    for(uint16_t i = 0; i < 256; i++){
        SetInterruptDescriptorTableEntry(i, codeSegment, &InterruptIgnore, 0, IDT_INTERRUPT_GATE);
    }    

   SetInterruptDescriptorTableEntry(0x00, codeSegment, &InterruptIgnore, 0, IDT_INTERRUPT_GATE); 
   SetInterruptDescriptorTableEntry(0x01, codeSegment, &InterruptIgnore, 0, IDT_INTERRUPT_GATE); 
   SetInterruptDescriptorTableEntry(0x02, codeSegment, &InterruptIgnore, 0, IDT_INTERRUPT_GATE); 
   SetInterruptDescriptorTableEntry(0x03, codeSegment, &InterruptIgnore, 0, IDT_INTERRUPT_GATE); 
   SetInterruptDescriptorTableEntry(0x04, codeSegment, &InterruptIgnore, 0, IDT_INTERRUPT_GATE); 
   SetInterruptDescriptorTableEntry(0x05, codeSegment, &InterruptIgnore, 0, IDT_INTERRUPT_GATE); 
   SetInterruptDescriptorTableEntry(0x06, codeSegment, &InterruptIgnore, 0, IDT_INTERRUPT_GATE); 
   SetInterruptDescriptorTableEntry(0x07, codeSegment, &InterruptIgnore, 0, IDT_INTERRUPT_GATE); 
   SetInterruptDescriptorTableEntry(0x08, codeSegment, &InterruptIgnore, 0, IDT_INTERRUPT_GATE); 
   SetInterruptDescriptorTableEntry(0x09, codeSegment, &InterruptIgnore, 0, IDT_INTERRUPT_GATE); 
   SetInterruptDescriptorTableEntry(0x0A, codeSegment, &InterruptIgnore, 0, IDT_INTERRUPT_GATE); 
   SetInterruptDescriptorTableEntry(0x0B, codeSegment, &InterruptIgnore, 0, IDT_INTERRUPT_GATE); 
   SetInterruptDescriptorTableEntry(0x0C, codeSegment, &InterruptIgnore, 0, IDT_INTERRUPT_GATE); 
   SetInterruptDescriptorTableEntry(0x0D, codeSegment, &InterruptIgnore, 0, IDT_INTERRUPT_GATE); 
   SetInterruptDescriptorTableEntry(0x0E, codeSegment, &InterruptIgnore, 0, IDT_INTERRUPT_GATE); 
   SetInterruptDescriptorTableEntry(0x0F, codeSegment, &InterruptIgnore, 0, IDT_INTERRUPT_GATE); 
   SetInterruptDescriptorTableEntry(0x10, codeSegment, &InterruptIgnore, 0, IDT_INTERRUPT_GATE); 
   SetInterruptDescriptorTableEntry(0x12, codeSegment, &InterruptIgnore, 0, IDT_INTERRUPT_GATE); 
   SetInterruptDescriptorTableEntry(0x13, codeSegment, &InterruptIgnore, 0, IDT_INTERRUPT_GATE); 

}



uint32_t InterruptManager::handleInterrupt(uint8_t interruptNumber, uint32_t esp){
    printf("interrupt");
    return esp;
}


void InterruptManager::HandleInterruptRequest0x00(){}

void InterruptManager::HandleException0x00(){}
