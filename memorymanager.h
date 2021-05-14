#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H
#include <stdint.h>
#include <list>
#include "memorysegment.h"
#include <vector>

class Cartridge;
class MemorySegment;
class MemoryManager
{
public:
    MemoryManager();
    MemorySegment *operator[](size_t i);
    MemorySegment *getSegment(size_t i);


private:
    struct MemoryBlock{
        size_t size, lowerVal;
        std::vector<MemorySegment&> segemts;
        MemoryBlock(size_t segmentSize):segemts(segmentSize) {}
        MemoryBlock(size_t segmentSize, size_t low):segemts(segmentSize), lowerVal(low) {}
    };
    std::list<MemoryBlock&> memBlocks;

};

#endif // MEMORYMANAGER_H
