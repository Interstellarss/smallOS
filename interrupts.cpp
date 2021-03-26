#include "interrupts.h"

void printf(const char*);

uint32_t InterruptManager::handleInterrupt(uint8_t interruptNumber, uint32_t esp){
    printf("interrupt");
    return esp;
}

void InterruptManager::HandleInterruptRequest0x00(){}

void InterruptManager::HandleException0x00(){}
