#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H
#include <stdint.h>
#include <list>
#include "memorysegment.h"
#include <vector>
#include "cartridge.h"
#include "memoryblock.h"

namespace cppb
{




class MemoryManager
{
public:
    MemoryManager();
    MemorySegment *operator[](size_t i);
    MemorySegment *getSegment(size_t i);


private:

    std::list<MemoryBlock *> memBlocks;

};
}
#endif // MEMORYMANAGER_H
