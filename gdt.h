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

    SegmentDescriptor nullSegmentDescriptor;

    SegmentDescriptor unusedSegmentDescriptor;

    SegmentDescriptor codeSegmentDescriptor;

    SegmentDescriptor dataSegmentDescriptor;

    public:
        GlobalDescriptorTable();
        ~GlobalDescriptorTable();


  
};

#endif

