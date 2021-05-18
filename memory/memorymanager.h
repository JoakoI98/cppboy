#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H
#include <stdint.h>
#include <list>
#include "memorysegment.h"
#include <vector>
#include "../cartridge/cartridge.h"
#include "memoryblock.h"
#include <exception>
namespace cppb
{




class MemoryManager
{
public:
    MemoryManager();
    MemorySegment *operator[](uint16_t i);
    MemorySegment *getSegment(uint16_t i);


private:

    std::list<MemoryBlock *> memBlocks;

};

class SegmentIndexingException : public std::exception{
public:
    SegmentIndexingException(uint16_t memory, MemoryBlock *block);
public:
    MemoryBlock *block;
    uint16_t memory;
};
}
#endif // MEMORYMANAGER_H
