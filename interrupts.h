#ifndef __INTERRUPTS_H
#define __INTERRUPTS_H

#include "types.h"
#include "port.h"
#include "gdt.h"

class InterruptManager{
    protected:
        struct GateDescriptor{
            uint16_t handlerAddressLowBits;
            uint16_t gdt_codeSegmentSelector;
            uint8_t reserved;
            uint8_t access;
            uint16_t handlerAddressHighBis;

        }__attribute__((packed));

        static GateDescriptor interruptDescriptorTable[256];

        static void SetInterruptDescriptorTableEntry(
            uint8_t interruptNumber,
            uint16_t codeSegementSelectorOffset,
            void (*handler)(),
            uint8_t DescriptorPrivilegeLevel,
            uint8_t DescriptorType
        );

    public:

        InterruptManager(GlobalDescriptorTable* gdt);
        ~InterruptManager();

        static uint32_t handleInterrupt(uint8_t interruptNumber, uint32_t esp);

        static void HandleInterruptRequest0x00();
        static void HandleInterruptRequest0x01();
        static void HandleInterruptRequest0x02();
        static void HandleInterruptRequest0x03();
        static void HandleInterruptRequest0x04();
        static void HandleInterruptRequest0x05();
        static void HandleInterruptRequest0x06();
        static void HandleInterruptRequest0x07();
        static void HandleInterruptRequest0x08();
        static void HandleInterruptRequest0x09();
        static void HandleInterruptRequest0x0A();
        static void HandleInterruptRequest0x0B();
        static void HandleInterruptRequest0x0C();
        static void HandleInterruptRequest0x0D();
        static void HandleInterruptRequest0x0E();
        static void HandleInterruptRequest0x0F();
        static void HandleInterruptRequest0x31();

        static void HandleException0x00();
        static void HandleException0x01();
        static void HandleException0x02();
        static void HandleException0x03();
        static void HandleException0x04();
        static void HandleException0x05();
        static void HandleException0x06();
        static void HandleException0x07();
        static void HandleException0x08();
        static void HandleException0x09();
        static void HandleException0x0A();
        static void HandleException0x0B();
        static void HandleException0x0C();
        static void HandleException0x0D();
        static void HandleException0x0E();
        static void HandleException0x0F();
        static void HandleException0x10();
        static void HandleException0x11();
        static void HandleException0x12();
        static void HandleException0x13();


};




#endif 