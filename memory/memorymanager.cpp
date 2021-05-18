#include "memorymanager.h"
#include <stdlib.h>
#include <string.h>
#include <QDebug>


using namespace cppb;

cppb::MemoryManager::MemoryManager()
{
    Cartridge& ROM = Cartridge::GetROM();
    MemoryBlock& bank0 = ROM.getBlock0(this);
    MemoryBlock& bank1 = ROM.getBlock1(this);

    bank0.lowerVal = 0;
    bank1.lowerVal = 0x4000;

    //8KB Video RAM
    MemoryBlock *VRAM = new MemoryBlock(0x2000, 0x8000);
    for(size_t i = 0; i !=0x2000; i++){
        MemorySegment *s = new MemorySegment(this, i + 0x8000);
        VRAM->segemts[i] = s;
    }

    MemoryBlock& eRAM = ROM.getRamBank(this);

    // 4KB ram0 ram1
    MemoryBlock *RAM0 = new MemoryBlock(0x1000, 0xC000);
    for(size_t i = 0; i !=0x1000; i++){
        MemorySegment *s = new MemorySegment(this,i + 0xC000);
        RAM0->segemts[i] = s;
    }
    MemoryBlock *RAM1 = new MemoryBlock(0x1000, 0xD000);
    for(size_t i = 0; i !=0x1000; i++){
        MemorySegment *s = new MemorySegment(this,i + 0xD000);
        RAM1->segemts[i] = s;
    }


    //Mirror RAM
    MemoryBlock *mirrorRAM = new MemoryBlock(0x1E00, 0xE000);
    for(size_t i = 0; i !=0x1000; i++){
        mirrorRAM->segemts[i] = RAM0->segemts[i];
    }
    for(size_t i = 0x1000; i !=0x1E00; i++){
        mirrorRAM->segemts[i] = RAM1->segemts[i-0x1000];
    }

    //OAM
    MemoryBlock *OAM = new MemoryBlock(0xA0, 0xFE00);
    for(size_t i = 0; i !=0xA0; i++){
        MemorySegment *s = new MemorySegment(this,i + 0xFE00);
        OAM->segemts[i] = s;
    }

    //Not usable
    MemoryBlock *ns = new MemoryBlock(0x60, 0xFEA0);
    for(size_t i = 0; i !=0x60; i++){
        MemorySegment *s = new MemorySegment(this,i + 0xFEA0);
        ns->segemts[i] = s;
    }

    //I/O
    MemoryBlock *IORegs = new MemoryBlock(0x80, 0xFF00);
    for(size_t i = 0; i !=0x80; i++){
        MemorySegment *s = new MemorySegment(this,i + 0xFF00);
        IORegs->segemts[i] = s;
    }

    //HRAM
    MemoryBlock *HRAM = new MemoryBlock(0x7F, 0xFF80);
    for(size_t i = 0; i !=0x7F; i++){
        MemorySegment *s = new MemorySegment(this,i + 0xFF80);
        HRAM->segemts[i] = s;
    }

    //INTERRUPT
    MemoryBlock *IREG = new MemoryBlock(0x01, 0xFFFF);
    MemorySegment *s = new MemorySegment(this, 0xFFFF);
    IREG->segemts[0] = s;

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

MemorySegment *cppb::MemoryManager::operator[](uint16_t i)
{
    return getSegment(i);
}




MemorySegment *cppb::MemoryManager::getSegment(uint16_t i)
{
    MemoryBlock *required = *memBlocks.begin();
    for(auto x: memBlocks){
        if(i >= x->lowerVal && i <= (x->lowerVal + x->size)){
            required = x;
        }
    }
    uint16_t pos = i - required->lowerVal;
    if(pos > required->size){
        qDebug() << "Error en indexado de segmento";
        throw SegmentIndexingException(i, required);
    }
    MemorySegment *segment = required->segemts[pos];
    return segment;
}



SegmentIndexingException::SegmentIndexingException(uint16_t memory, MemoryBlock *block): block(block), memory(memory)
{

}
