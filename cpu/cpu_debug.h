#ifndef CPU_DEBUG_H
#define CPU_DEBUG_H
#include <string>
#include <stdint.h>
#include <QString>
#include "cpu.h"


namespace cppb {
class cpu_debug
{
public:
    struct InstructionInfo{
        QString description;
        uint8_t memory;
    };
    cpu_debug(CPU& cpu);
    InstructionInfo getInfoOf(uint8_t inst);

    QStringList getInfo(bool includeRegs = false, bool dissasm = false);
    QStringList getInfo(uint16_t to, uint16_t from, bool includeRegs = false, bool dissasm = false);

private:
    InstructionInfo instructionInfo[0x100];
    CPU& cpu;
};
}



#endif // CPU_DEBUG_H
