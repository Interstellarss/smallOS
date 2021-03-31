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

InterruptManager::InterruptManager(GlobalDescriptorTable* gdt){
    uint16_t codeSegment = gdt -> CodeSegmentDescriptor();

    const uint8_t IDT_INTERRUPT_GATE = 0xe;

    

}


uint32_t InterruptManager::handleInterrupt(uint8_t interruptNumber, uint32_t esp){
    printf("interrupt");
    return esp;
}


void InterruptManager::HandleInterruptRequest0x00(){}

void InterruptManager::HandleException0x00(){}
