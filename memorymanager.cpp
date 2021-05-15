#include "memorymanager.h"
#include <stdlib.h>
#include <string.h>

using namespace cppb;

cppb::MemoryManager::MemoryManager()
{
    Cartridge& ROM = Cartridge::GetROM();
    MemoryBlock& bank0 = ROM.getBlock0();
    MemoryBlock& bank1 = ROM.getBlock1();

    bank0.lowerVal = 0;
    bank1.lowerVal = 0x4000;

    //8KB Video RAM
    MemoryBlock *VRAM = new MemoryBlock(0x2000, 0x8000);
    for(size_t i = 0; i !=0x2000; i++){
        MemorySegment *s = new MemorySegment(this, i + 0x8000);
        VRAM->segemts[i] = s;
    }

    MemoryBlock& eRAM = ROM.getRamBank();

    // 4KB ram0 ram1
    MemoryBlock *RAM0 = new MemoryBlock(0x1000, 0xC000);
    for(size_t i = 0; i !=0x1000; i++){
        MemorySegment *s = new MemorySegment(this,i + 0xC000);
        VRAM->segemts[i] = s;
    }
    MemoryBlock *RAM1 = new MemoryBlock(0x1000, 0xD000);
    for(size_t i = 0; i !=0x1000; i++){
        MemorySegment *s = new MemorySegment(this,i + 0xD000);
        VRAM->segemts[i] = s;
    }


    //Mirror RAM
    MemoryBlock *mirrorRAM = new MemoryBlock(0x1E00, 0xE000);
    for(size_t i = 0; i !=0x1000; i++){
        VRAM->segemts[i] = RAM0->segemts[i];
    }
    for(size_t i = 0x1000; i !=0x1E00; i++){
        VRAM->segemts[i] = RAM1->segemts[i-0x1000];
    }

    //OAM
    MemoryBlock *OAM = new MemoryBlock(0xA0, 0xFE00);
    for(size_t i = 0; i !=0xA0; i++){
        MemorySegment *s = new MemorySegment(this,i + 0xFE00);
        VRAM->segemts[i] = s;
    }

    //Not usable
    MemoryBlock *ns = new MemoryBlock(0x60, 0xFEA0);
    for(size_t i = 0; i !=0x60; i++){
        MemorySegment *s = new MemorySegment(this,i + 0xFEA0);
        VRAM->segemts[i] = s;
    }

    //I/O
    MemoryBlock *IORegs = new MemoryBlock(0x80, 0xFF00);
    for(size_t i = 0; i !=0x80; i++){
        MemorySegment *s = new MemorySegment(this,i + 0xFF00);
        VRAM->segemts[i] = s;
    }

    //HRAM
    MemoryBlock *HRAM = new MemoryBlock(0x7F, 0xFF80);
    for(size_t i = 0; i !=0x7F; i++){
        MemorySegment *s = new MemorySegment(this,i + 0xFF80);
        VRAM->segemts[i] = s;
    }

    //INTERRUPT
    MemoryBlock *IREG = new MemoryBlock(0x01, 0xFFFF);
    MemorySegment *s = new MemorySegment(this, 0xFFFF);
    VRAM->segemts[0] = s;

    memBlocks.push_back(&bank0);
    memBlocks.push_back(&bank1);
    memBlocks.push_back(VRAM);
    memBlocks.push_back(&eRAM);
    memBlocks.push_back(RAM0);
    memBlocks.push_back(RAM1);
    memBlocks.push_back(mirrorRAM);
    memBlocks.push_back(OAM);
    memBlocks.push_back(ns);
    memBlocks.push_back(IORegs);
    memBlocks.push_back(HRAM);
    memBlocks.push_back(IREG);
}

MemorySegment *cppb::MemoryManager::operator[](size_t i)
{
    return getSegment(i);
}

MemorySegment *cppb::MemoryManager::getSegment(size_t i)
{
    auto it = memBlocks.begin();
    while(it != memBlocks.end() && i < (*it)->lowerVal) ++it;

    size_t pos = i - (*it)->lowerVal;
    MemorySegment *segment = (*it)->segemts[pos];
    return segment;
}


