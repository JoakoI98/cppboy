#ifndef CARTRIDGE_H
#define CARTRIDGE_H
#include <stdint.h>
#include "../memory/memorymanager.h"
#include "../memory/memoryblock.h"
#include "ROM.h"

namespace cppb
{


class Cartridge: public ROM
{
public:
    enum CartridgeTypes
    {
        CartridgeNoMBC,
        CartridgeMBC1,
        CartridgeMBC2,
        CartridgeMBC3,
        CartridgeMBC5,
        CartridgeMBC1Multi,
        CartridgeNotSupported
    };



    Cartridge();

    static Cartridge &GetROM();
    MemoryBlock &getBlock0(MemoryManager *manager, uint16_t lower = 0x0000);
    MemoryBlock &getBlock1(MemoryManager *manager, uint16_t lower = 0x4000);
    MemoryBlock &getRamBank(MemoryManager *manager, uint16_t lower = 0xA000);
    uint8_t ROMData[0x8000] = {0};

private:
    void CheckCartridgeType(int type);
    unsigned int Pow2Ceil(unsigned int n);

private:
    MemoryBlock *block0, *block1, *ramBank;
    void GatherMetadata();
    uint8_t *pTheROM;
    char szName[16];
    bool bCGB;
    bool bSGB;
    bool bBattery;
    bool bValidROM;
    bool bRTCPresent;
    bool bRumblePresent;
    int iVersion;
    int iROMSize;
    int iRAMSize;
    int iRAMBankCount;
    int iROMBankCount;
    int iTotalSize;
    CartridgeTypes type;



    // ROM interface
public:
    void ROMWrite(uint8_t val, uint16_t pos);
};
}
#endif // CARTRIDGE_H
