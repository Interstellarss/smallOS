/*
 * 
 */

#ifndef __GDT_H
#define __GDT_H

#include "types.h"
class GlobalDescriptorTable{
    public:
        class SegmentDescriptor{    
            public:
                SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t type);
                uint32_t Base();
                uint32_t Limit();
            private:
                uint16_t seg_limit;
                uint16_t base_low;
                uint8_t base_high;
                uint8_t type;
                uint8_t flag_limit_high;
                uint8_t base_super;

        } __attribute__((packed)); /*this way data will not be aligned through compiler*/
    
    private:

        SegmentDescriptor nullSegmentDescriptor;

        SegmentDescriptor unusedSegmentDescriptor;

        SegmentDescriptor codeSegmentSelector;

        SegmentDescriptor dataSegmentSelector;
    
    public:
        GlobalDescriptorTable();
        ~GlobalDescriptorTable();

        uint16_t CodeSegmentDescriptor();
        uint16_t DataSegmentDescriptor();

};

#endif

