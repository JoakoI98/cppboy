#include "memoryblock.h"

cppb::MemoryBlock::MemoryBlock(size_t segmentSize):segemts(segmentSize)
{

}

cppb::MemoryBlock::MemoryBlock(size_t segmentSize, size_t low):size(segmentSize), lowerVal(low),segemts(segmentSize)
{

}
