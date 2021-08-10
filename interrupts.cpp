#include "interrupts.h"

void printf(const char*);

InterruptManager::GateDescriptor InterruptManager::interruptDescriptorTable[256];


InterruptManager* InterruptManager::ActivateInterruptManager = 0;

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

        interruptDescriptorTable[interruptNumber].access = IDT_DESC_PRESENT | ((DescriptorPrivilegeLevel & 3) << 5) | DescriptorType;

        interruptDescriptorTable[interruptNumber].reserved = 0;
}

InterruptManager::InterruptManager(uint16_t hardwareInterruptOffset, GlobalDescriptorTable* gdt)
    : programmableInterruptControllerMasterCommandPort(0x20),
    programmableInterruptControllerMasterDataPort(0x21), 
    programmableInterruptControllerSlaveCommandPort(0xA0),
    programmableInterruptControllerSlaveDataPort(0xA1)
{   

    this->hardwareInterruptOffset = hardwareInterruptOffset;

    uint16_t codeSegment = (gdt -> CodeSegmentSelector()) << 3;

    const uint8_t IDT_INTERRUPT_GATE = 0xe;

    for(uint8_t i = 255; i > 0; --i){
        //handlers[i] = 0;
        SetInterruptDescriptorTableEntry(i, codeSegment, &InterruptIgnore, 0, IDT_INTERRUPT_GATE);
    }    

    
    //SetInterruptDescriptorTableEntry(0, codeSegment, , 0, IDT_INTERRUPT_GATE);
    //InterruptDescriptorTablePointer idt;

    //idt.size = 256 * sizeof(GateDescriptor) - 1;
    //idt.base = (uint32_t)interruptDescriptorTable;

    SetInterruptDescriptorTableEntry(0x00, codeSegment, &HandleException0x00, 0, IDT_INTERRUPT_GATE); 
    SetInterruptDescriptorTableEntry(0x01, codeSegment, &HandleException0x01, 0, IDT_INTERRUPT_GATE); 
    SetInterruptDescriptorTableEntry(0x02, codeSegment, &HandleException0x02, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x03, codeSegment, &HandleException0x03, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x04, codeSegment, &HandleException0x04, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x05, codeSegment, &HandleException0x05, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x06, codeSegment, &HandleException0x06, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x07, codeSegment, &HandleException0x07, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x08, codeSegment, &HandleException0x08, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x09, codeSegment, &HandleException0x09, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x0A, codeSegment, &HandleException0x0A, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x0B, codeSegment, &HandleException0x0B, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x0C, codeSegment, &HandleException0x0C, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x0D, codeSegment, &HandleException0x0D, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x0E, codeSegment, &HandleException0x0E, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x0F, codeSegment, &HandleException0x0F, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x10, codeSegment, &HandleException0x10, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x11, codeSegment, &HandleException0x11, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x12, codeSegment, &HandleException0x12, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x13, codeSegment, &HandleException0x13, 0, IDT_INTERRUPT_GATE);


    SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x00, codeSegment, &HandleInterruptRequest0x00, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x01, codeSegment, &HandleInterruptRequest0x01, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x02, codeSegment, &HandleInterruptRequest0x02, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x03, codeSegment, &HandleInterruptRequest0x03, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x04, codeSegment, &HandleInterruptRequest0x04, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x05, codeSegment, &HandleInterruptRequest0x05, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x06, codeSegment, &HandleInterruptRequest0x06, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x07, codeSegment, &HandleInterruptRequest0x07, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x08, codeSegment, &HandleInterruptRequest0x08, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x09, codeSegment, &HandleInterruptRequest0x09, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x0A, codeSegment, &HandleInterruptRequest0x0A, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x0B, codeSegment, &HandleInterruptRequest0x0B, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x0C, codeSegment, &HandleInterruptRequest0x0C, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x0D, codeSegment, &HandleInterruptRequest0x0D, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x0E, codeSegment, &HandleInterruptRequest0x0E, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x0F, codeSegment, &HandleInterruptRequest0x0F, 0, IDT_INTERRUPT_GATE);

    programmableInterruptControllerMasterCommandPort.write(0x11);
    programmableInterruptControllerSlaveCommandPort.write(0x11);

    // remap
    programmableInterruptControllerMasterDataPort.write(hardwareInterruptOffset);
    programmableInterruptControllerSlaveDataPort.write(hardwareInterruptOffset+8);

    programmableInterruptControllerMasterDataPort.write(0x04);
    programmableInterruptControllerSlaveDataPort.write(0x02);

    programmableInterruptControllerMasterDataPort.write(0x01);
    programmableInterruptControllerSlaveDataPort.write(0x01);

    programmableInterruptControllerMasterDataPort.write(0x00);
    programmableInterruptControllerSlaveDataPort.write(0x00);

    InterruptDescriptorTablePointer idt_pointer;
    idt_pointer.size  = 256*sizeof(GateDescriptor) - 1;
    idt_pointer.base  = (uint32_t)interruptDescriptorTable;
    asm volatile("lidt %0" : : "m" (idt_pointer));



}

InterruptManager::~InterruptManager(){
    //Deactivate();
}

uint16_t InterruptManager::HardwareInterruptOffset()
{
    return hardwareInterruptOffset;
}

void InterruptManager::Activate(){
    if(ActivateInterruptManager != 0)
    {
        ActivateInterruptManager -> Deactivate();

    }

    ActivateInterruptManager = this;

    asm("sti");
}


void InterruptManager::Deactivate(){
    if(ActivateInterruptManager == this){
        ActivateInterruptManager = 0;
        asm("cli");
    }

}

uint32_t InterruptManager::HandleInterrupt(uint8_t interruptNumber, uint32_t esp){
    printf("interrupt");
    return esp;
}

