#include "memorysegment.h"

MemorySegment::operator uint16_t() const
{
    uint8_t next = *(manager.getSegment(i+1));
    uint16_t ret = ((uint16_t)(next << 8) & 0xff00) + (uint16_t)(val & 0x00ff);
    return ret;
}

void MemorySegment::operator=(const uint16_t &v)
{
    uint8_t l = (uint8_t)(v & 0x00ff);
    uint8_t h = (uint8_t)(((v & 0xff00) >> 8) & 0x00ff);
    val = l;
    MemorySegment next = *(manager.getSegment(i+1));
    next = h;
}

MemorySegment::operator size_t() const
{
    uint8_t next = *(manager.getSegment(i+1));
    uint16_t ret = ((uint16_t)(next << 8) & 0xff00) + (uint16_t)(val & 0x00ff);
    return (size_t)ret;
}
