#ifndef MEMORYSEGMENT_READONLY_H
#define MEMORYSEGMENT_READONLY_H
#include "../cartridge/ROM.h"
#include "memorysegment.h"
namespace cppb {


class MemorySegment_ReadOnly : public MemorySegment
{
public:
    MemorySegment_ReadOnly(ROM *RomMemory, MemoryManager *manager,size_t i);
    MemorySegment_ReadOnly(ROM *RomMemory, MemoryManager *manager,size_t i, uint8_t val);
    MemorySegment_ReadOnly(ROM *RomMemory, MemoryManager *manager);

    virtual void operator=(const uint8_t& v) {
        RomMemory->ROMWrite(v, i);
    }
    virtual MemorySegment &operator+=(const uint8_t& a){
        RomMemory->ROMWrite(a+val, i);
        return *this;
    }
    virtual MemorySegment &operator-=(const uint8_t& a){
        RomMemory->ROMWrite(val-a, i);
        return *this;
    }
    virtual MemorySegment &operator++(){
        RomMemory->ROMWrite(1+val, i);
        return *this;
    }
    virtual MemorySegment &operator--(){
        RomMemory->ROMWrite(val-1, i);
        return *this;
    }
    virtual MemorySegment &operator++(int){
        RomMemory->ROMWrite(val+1, i);
        return *this;
    }
    virtual MemorySegment &operator--(int){
        RomMemory->ROMWrite(val-1, i);
        return *this;
    }

    void writeToRom(uint8_t toWrite){
        if(!valSetted){
            valSetted = true;
            val = toWrite;
        }
    }

private:
    ROM *RomMemory;
    bool valSetted = false;
};
}
#endif // MEMORYSEGMENT_READONLY_H
