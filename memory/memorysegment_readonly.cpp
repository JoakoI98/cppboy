#include "memorysegment_readonly.h"
using namespace cppb;
cppb::MemorySegment_ReadOnly::MemorySegment_ReadOnly(cppb::ROM *RomMemory, cppb::MemoryManager *manager):MemorySegment(manager), RomMemory(RomMemory)
{

}

cppb::MemorySegment_ReadOnly::MemorySegment_ReadOnly(cppb::ROM *RomMemory, cppb::MemoryManager *manager, size_t i): MemorySegment(manager, i), RomMemory(RomMemory)
{

}

MemorySegment_ReadOnly::MemorySegment_ReadOnly(ROM *RomMemory, MemoryManager *manager, size_t i, uint8_t val):MemorySegment(manager, i), RomMemory(RomMemory)
{
    valSetted = true;
    this->val = val;
}
