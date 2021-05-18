#include "cartridge.h"
#include <string.h>
#include <algorithm>
#include <QDebug>
#include "../memory/memorysegment_readonly.h"

#define Log(msg, ...)

cppb::Cartridge::Cartridge()
{
    ssize_t i = 0x100;
    ROMData[i++] = 0xFB;
    ROMData[i++] = 0x3E;
    ROMData[i++] = 0x02;
    ROMData[i++] = 0x01;
    ROMData[i++] = 0xFF;
    ROMData[i++] = 0xFF;
    ROMData[i++] = 0x02;
    ROMData[i++] = 0x01;
    ROMData[i++] = 0x0F;
    ROMData[i++] = 0xFF;
    ROMData[i++] = 0x02;
    ROMData[i++] = 0x00;
    ROMData[i++] = 0x00;
    ROMData[i++] = 0x00;

}

cppb::Cartridge &cppb::Cartridge::GetROM()
{
    return *(new Cartridge());
}

cppb::MemoryBlock &cppb::Cartridge::getBlock0(MemoryManager *manager, uint16_t lower)
{
    block0 = new MemoryBlock(0x4000, lower);
    for(size_t i = 0; i !=0x4000; i++){
        MemorySegment *s = new MemorySegment_ReadOnly(this, manager,i + lower, ROMData[i + lower]);
        block0->segemts[i] = s;
    }
    return *block0;
}

cppb::MemoryBlock &cppb::Cartridge::getBlock1(MemoryManager *manager, uint16_t lower)
{
    block1 = new MemoryBlock(0x4000, lower);
    for(size_t i = 0; i !=0x4000; i++){
        MemorySegment *s = new MemorySegment_ReadOnly(this, manager,i + lower, ROMData[i + lower]);
        block1->segemts[i] = s;
    }
    return *block1;
}

cppb::MemoryBlock &cppb::Cartridge::getRamBank(MemoryManager *manager, uint16_t lower)
{
    ramBank = new MemoryBlock(0x2000, lower);
    for(size_t i = 0; i !=0x2000; i++){
        MemorySegment *s = new MemorySegment(manager,i + lower);
        ramBank->segemts[i] = s;
    }
    return *ramBank;
}
void cppb::Cartridge::CheckCartridgeType(int type)
{
    if ((type != 0xEA) && (iROMSize == 0))
        type = 0;

    switch (type)
    {
        case 0x00:
            // NO MBC
        case 0x08:
            // ROM
            // SRAM
        case 0x09:
            // ROM
            // SRAM
            // BATT
            this->type = CartridgeNoMBC;
            break;
        case 0x01:
            // MBC1
        case 0x02:
            // MBC1
            // SRAM
        case 0x03:
            // MBC1
            // SRAM
            // BATT
        case 0xEA:
            // Hack to accept 0xEA as a MBC1 (Sonic 3D Blast 5)
        case 0xFF:
            // Hack to accept HuC1 as a MBC1
            this->type = CartridgeMBC1;
            break;
        case 0x05:
            // MBC2
            // SRAM
        case 0x06:
            // MBC2
            // SRAM
            // BATT
            this->type = CartridgeMBC2;
            break;
        case 0x0F:
            // MBC3
            // TIMER
            // BATT
        case 0x10:
            // MBC3
            // TIMER
            // BATT
            // SRAM
        case 0x11:
            // MBC3
        case 0x12:
            // MBC3
            // SRAM
        case 0x13:
            // MBC3
            // BATT
            // SRAM
        case 0xFC:
            // Game Boy Camera
            this->type = CartridgeMBC3;
            break;
        case 0x19:
            // MBC5
        case 0x1A:
            // MBC5
            // SRAM
        case 0x1B:
            // MBC5
            // BATT
            // SRAM
        case 0x1C:
            // RUMBLE
        case 0x1D:
            // RUMBLE
            // SRAM
        case 0x1E:
            // RUMBLE
            // BATT
            // SRAM
            this->type = CartridgeMBC5;
            break;
        case 0x0B:
            // MMMO1
        case 0x0C:
            // MMM01
            // SRAM
        case 0x0D:
            // MMM01
            // SRAM
            // BATT
        case 0x15:
            // MBC4
        case 0x16:
            // MBC4
            // SRAM
        case 0x17:
            // MBC4
            // SRAM
            // BATT
        case 0x22:
            // MBC7
            // BATT
            // SRAM
        case 0x55:
            // GG
        case 0x56:
            // GS3
        case 0xFD:
            // TAMA 5
        case 0xFE:
            // HuC3
            this->type = CartridgeNotSupported;
            Log("--> ** This cartridge is not supported. Type: %d", type);
            break;
        default:
            this->type = CartridgeNotSupported;
            Log("--> ** Unknown cartridge type: %d", type);
    }

    switch (type)
    {
        case 0x03:
        case 0x06:
        case 0x09:
        case 0x0D:
        case 0x0F:
        case 0x10:
        case 0x13:
        case 0x17:
        case 0x1B:
        case 0x1E:
        case 0x22:
        case 0xFD:
        case 0xFF:
            bBattery = true;
            break;
        default:
            bBattery = false;
    }

    switch (type)
    {
        case 0x0F:
        case 0x10:
            bRTCPresent = true;
            break;
        default:
            bRTCPresent = false;
    }

    switch (type)
    {
        case 0x1C:
        case 0x1D:
        case 0x1E:
            bRumblePresent = true;
            break;
        default:
            bRumblePresent = false;
    }
}

unsigned int cppb::Cartridge::Pow2Ceil(unsigned int n)
{
    --n;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    ++n;
    return n;
}


void cppb::Cartridge::GatherMetadata()
{
    char name[12] = {0};
    name[11] = 0;

    for (int i = 0; i < 11; i++)
    {
        name[i] = pTheROM[0x0134 + i];

        if (name[i] == 0)
        {
            break;
        }
    }

    strcpy(szName, name);

    bCGB = (pTheROM[0x143] == 0x80) || (pTheROM[0x143] == 0xC0);
    bSGB = (pTheROM[0x146] == 0x03);
    int type = pTheROM[0x147];
    iROMSize = pTheROM[0x148];
    iRAMSize = pTheROM[0x149];
    iVersion = pTheROM[0x14C];

    CheckCartridgeType(type);

    switch (iRAMSize)
    {
        case 0x00:
            iRAMBankCount = (this->type == Cartridge::CartridgeMBC2) ? 1 : 0;
            break;
        case 0x01:
        case 0x02:
            iRAMBankCount = 1;
            break;
        case 0x04:
            iRAMBankCount = 16;
            break;
        default:
            iRAMBankCount = 4;
            break;
    }

    iROMBankCount = std::max(Pow2Ceil(iTotalSize / 0x4000), 2u);

    bool presumeMultiMBC1 = ((type == 1) && (iRAMSize == 0) && (iROMBankCount == 64));

    if ((this->type == Cartridge::CartridgeMBC1) && presumeMultiMBC1)
    {
        this->type = Cartridge::CartridgeMBC1Multi;
        Log("Presumed Multi 64");
    }

    Log("Cartridge Size %d", iTotalSize);
    Log("ROM Name %s", szName);
    Log("ROM Version %d", iVersion);
    Log("ROM Type %X", type);
    Log("ROM Size %X", iROMSize);
    Log("ROM Bank Count %d", iROMBankCount);
    Log("RAM Size %X", iRAMSize);
    Log("RAM Bank Count %d", iRAMBankCount);

    switch (this->type)
    {
        case Cartridge::CartridgeNoMBC:
            Log("No MBC found");
            break;
        case Cartridge::CartridgeMBC1:
            Log("MBC1 found");
            break;
        case Cartridge::CartridgeMBC1Multi:
            Log("MBC1 Multi 64 found");
            break;
        case Cartridge::CartridgeMBC2:
            Log("MBC2 found");
            break;
        case Cartridge::CartridgeMBC3:
            Log("MBC3 found");
            break;
        case Cartridge::CartridgeMBC5:
            Log("MBC5 found");
            break;
        case Cartridge::CartridgeNotSupported:
            Log("Cartridge not supported!!");
            break;
        default:
            break;
    }

    if (bBattery)
    {
        Log("Battery powered RAM found");
    }

    if (pTheROM[0x143] == 0xC0)
    {
        Log("Game Boy Color only");
    }
    else if (bCGB)
    {
        Log("Game Boy Color supported");
    }

    if (bSGB)
    {
        Log("Super Game Boy supported");
    }

    int checksum = 0;

    for (int j = 0x134; j < 0x14E; j++)
    {
        checksum += pTheROM[j];
    }

    bValidROM = ((checksum + 25) & 0xFF) == 0;

    if (bValidROM)
    {
        Log("Checksum OK!");
    }
    else
    {
        Log("Checksum FAILED!!!");
    }

    return;
}

void cppb::Cartridge::ROMWrite(uint8_t val, uint16_t pos)
{
    qDebug() << "Se escribio en la ROM: " + QString::number(val,16) << " en la posicion: " << QString::number(pos,16);
}

