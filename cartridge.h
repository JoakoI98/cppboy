#ifndef CARTRIDGE_H
#define CARTRIDGE_H
#include <stdint.h>
#include "memorymanager.h"
#include "memoryblock.h"

namespace cppb
{


class Cartridge
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
    MemoryBlock &getBlock0();
    MemoryBlock &getBlock1();
    MemoryBlock &getRamBank();


private:
    void CheckCartridgeType(int type);
    unsigned int Pow2Ceil(unsigned int n);

private:
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


};
}
#endif // CARTRIDGE_H
