#ifndef MEMORYBLOCK_H
#define MEMORYBLOCK_H
#include <stdint.h>
#include <list>
#include <vector>
#include "memorysegment.h"

namespace cppb {
class MemoryBlock
{
public:
    size_t size, lowerVal;
    std::vector<MemorySegment*> segemts;
    MemoryBlock(size_t segmentSize);
    MemoryBlock(size_t segmentSize, size_t low);
};
}
#endif // MEMORYBLOCK_H
