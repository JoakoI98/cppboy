#include "memorysegment.h"
#include "memorymanager.h"
#include <QDebug>
using namespace cppb;

cppb::MemorySegment::operator uint16_t() const
{

    uint8_t next = *(manager->getSegment(i+1));
    uint16_t ret = ((uint16_t)(next << 8) & 0xff00) + (uint16_t)(val & 0x00ff);
    return ret;
}

void cppb::MemorySegment::operator=(const uint16_t &v)
{
    uint8_t l = (uint8_t)(v & 0x00ff);
    uint8_t h = (uint8_t)(((v & 0xff00) >> 8) & 0x00ff);
    val = l;
    MemorySegment next = *(manager->getSegment(i+1));
    next = h;
}

cppb::MemorySegment::operator size_t() const
{
    uint16_t next = *(manager->getSegment(i+1));
    uint16_t ret = ((uint16_t)(next << 8) & 0xff00) + (uint16_t)(val & 0x00ff);
    return (size_t)ret;
}

cppb::MemorySegment &cppb::MemorySegment::operator=(const cppb::MemorySegment&){
    return *this;
}

cppb::MemorySegment::MemorySegment(MemoryManager *manager,size_t i):manager(manager), i(i)
{
    i_set = true;
    manager_set = true;
}

cppb::MemorySegment::MemorySegment(MemoryManager *manager):manager(manager)
{
    manager_set = true;
}

void cppb::MemorySegment::setManager(MemoryManager *manager)
{
    if(!manager_set){
        this->manager = manager;
        manager_set = true;
    }
}

uint8_t MemorySegment::getVal() const
{
    return val;
}

cppb::MemorySegment_Register8::MemorySegment_Register8(uint8_t *dir, MemoryManager *manager): MemorySegment(manager, 0), dir(dir){}

