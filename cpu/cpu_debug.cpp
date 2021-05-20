#include "cpu_debug.h"
#include <QDebug>
using namespace cppb;

cpu_debug::cpu_debug(CPU &cpu) : cpu(cpu)
{
    for(int i = 0; i!=0x100; i++){
        instructionInfo[i] = {"NOT INFO", 0};
    }


    instructionInfo[0x00] = { "NOP", 0 };
    instructionInfo[0x01] = { "LD BC, U16", 2 };
    instructionInfo[0x02] = { "LD (BC), A", 0 };
    instructionInfo[0x03] = { "INC BC", 0 };
    instructionInfo[0x04] = { "INC B", 0 };
    instructionInfo[0x05] = { "DEC B", 0 };
    instructionInfo[0x06] = { "LD B, U8", 0 };
    instructionInfo[0x07] = { "RLCA", 0 };
    instructionInfo[0x08] = { "LD (U8), SP", 0 };
    instructionInfo[0x09] = { "ADD HL, BC", 0 };
    instructionInfo[0x0a] = { "LD A, (BC)", 0 };
    instructionInfo[0x0b] = { "DEC BC", 0 };
    instructionInfo[0x0c] = { "INC C", 0 };
    instructionInfo[0x0d] = { "DEC C", 0 };
    instructionInfo[0x0e] = { "LD C, U8", 0 };
    instructionInfo[0x0f] = { "RRCA", 0 };
    instructionInfo[0x10] = { "STOP", 0 };
    instructionInfo[0x11] = { "LD DE, U16", 2 };
    instructionInfo[0x12] = { "LD (DE), A", 0 };
    instructionInfo[0x13] = { "INC DE", 0 };
    instructionInfo[0x14] = { "INC D", 0 };
    instructionInfo[0x15] = { "DEC D", 0 };
    instructionInfo[0x16] = { "LD D, U8", 0 };
    instructionInfo[0x17] = { "RLA", 0 };
    instructionInfo[0x18] = { "JR U8", 1 };
    instructionInfo[0x19] = { "ADD HL, DE", 0 };
    instructionInfo[0x1a] = { "LD A, (DE)", 0 };
    instructionInfo[0x1b] = { "DEC DE", 0 };
    instructionInfo[0x1c] = { "INC E", 0 };
    instructionInfo[0x1d] = { "DEC E", 0 };
    instructionInfo[0x1e] = { "LD E, U8", 0 };
    instructionInfo[0x1f] = { "RRA", 0 };
    instructionInfo[0x20] = { "JR NZ, U8", 0 };
    instructionInfo[0x21] = { "LD HL, U16", 0 };
    instructionInfo[0x22] = { "LD (HL+), A", 0 };
    instructionInfo[0x23] = { "INC HL", 0 };
    instructionInfo[0x24] = { "INC H", 0 };
    instructionInfo[0x25] = { "DEC H", 0 };
    instructionInfo[0x26] = { "LD H, U8", 0 };
    instructionInfo[0x27] = { "DAA", 0 };
    instructionInfo[0x28] = { "JR Z, U8", 0 };
    instructionInfo[0x29] = { "ADD HL, HL", 0 };
    instructionInfo[0x2a] = { "LD A, (HL+)", 0 };
    instructionInfo[0x2b] = { "DEC HL", 0 };
    instructionInfo[0x2c] = { "INC L", 0 };
    instructionInfo[0x2d] = { "DEC L", 0 };
    instructionInfo[0x2e] = { "LD L, U8", 0 };
    instructionInfo[0x2f] = { "CPL", 0 };
    instructionInfo[0x30] = { "JR NC, U8", 0 };
    instructionInfo[0x31] = { "LD SP, U16", 0 };
    instructionInfo[0x32] = { "LD (HL-), A", 0 };
    instructionInfo[0x33] = { "INC SP", 0 };
    instructionInfo[0x34] = { "INC (HL)", 0 };
    instructionInfo[0x35] = { "DEC (HL)", 0 };
    instructionInfo[0x36] = { "LD (HL), U8", 0 };
    instructionInfo[0x37] = { "SCF", 0 };
    instructionInfo[0x38] = { "JR C, U8", 0 };
    instructionInfo[0x39] = { "ADD HL, SP", 0 };
    instructionInfo[0x3a] = { "LD A, (HL-)", 0 };
    instructionInfo[0x3b] = { "DEC SP", 0 };
    instructionInfo[0x3c] = { "INC A", 0 };
    instructionInfo[0x3d] = { "DEC A", 0 };
    instructionInfo[0x3e] = { "LD A, U8", 0 };
    instructionInfo[0x3f] = { "CCF", 0 };
    instructionInfo[0x40] = { "LD B, B", 0 };
    instructionInfo[0x41] = { "LD B, C", 0 };
    instructionInfo[0x42] = { "LD B, D", 0 };
    instructionInfo[0x43] = { "LD B, E", 0 };
    instructionInfo[0x44] = { "LD B, H", 0 };
    instructionInfo[0x45] = { "LD B, L", 0 };
    instructionInfo[0x46] = { "LD B, (HL)", 0 };
    instructionInfo[0x47] = { "LD B, A", 0 };
    instructionInfo[0x48] = { "LD C, B", 0 };
    instructionInfo[0x49] = { "LD C, C", 0 };
    instructionInfo[0x4a] = { "LD C, D", 0 };
    instructionInfo[0x4b] = { "LD C, E", 0 };
    instructionInfo[0x4c] = { "LD C, H", 0 };
    instructionInfo[0x4d] = { "LD C, L", 0 };
    instructionInfo[0x4e] = { "LD C, (HL)", 0 };
    instructionInfo[0x4f] = { "LD C, A", 0 };
    instructionInfo[0x50] = { "LD D, B", 0 };
    instructionInfo[0x51] = { "LD D, C", 0 };
    instructionInfo[0x52] = { "LD D, D", 0 };
    instructionInfo[0x53] = { "LD D, E", 0 };
    instructionInfo[0x54] = { "LD D, H", 0 };
    instructionInfo[0x55] = { "LD D, L", 0 };
    instructionInfo[0x56] = { "LD D, (HL)", 0 };
    instructionInfo[0x57] = { "LD D, A", 0 };
    instructionInfo[0x58] = { "LD E, B", 0 };
    instructionInfo[0x59] = { "LD E, C", 0 };
    instructionInfo[0x5a] = { "LD E, D", 0 };
    instructionInfo[0x5b] = { "LD E, E", 0 };
    instructionInfo[0x5c] = { "LD E, H", 0 };
    instructionInfo[0x5d] = { "LD E, L", 0 };
    instructionInfo[0x5e] = { "LD E, (HL)", 0 };
    instructionInfo[0x5f] = { "LD E, A", 0 };
    instructionInfo[0x60] = { "LD H, B", 0 };
    instructionInfo[0x61] = { "LD H, C", 0 };
    instructionInfo[0x62] = { "LD H, D", 0 };
    instructionInfo[0x63] = { "LD H, E", 0 };
    instructionInfo[0x64] = { "LD H, H", 0 };
    instructionInfo[0x65] = { "LD H, L", 0 };
    instructionInfo[0x66] = { "LD H, (HL)", 0 };
    instructionInfo[0x67] = { "LD H, A", 0 };
    instructionInfo[0x68] = { "LD L, B", 0 };
    instructionInfo[0x69] = { "LD L, C", 0 };
    instructionInfo[0x6a] = { "LD L, D", 0 };
    instructionInfo[0x6b] = { "LD L, E", 0 };
    instructionInfo[0x6c] = { "LD L, H", 0 };
    instructionInfo[0x6d] = { "LD L, L", 0 };
    instructionInfo[0x6e] = { "LD L, (HL)", 0 };
    instructionInfo[0x6f] = { "LD L, A", 0 };
    instructionInfo[0x70] = { "LD (HL), B", 0 };
    instructionInfo[0x71] = { "LD (HL), C", 0 };
    instructionInfo[0x72] = { "LD (HL), D", 0 };
    instructionInfo[0x73] = { "LD (HL), E", 0 };
    instructionInfo[0x74] = { "LD (HL), H", 0 };
    instructionInfo[0x75] = { "LD (HL), L", 0 };
    instructionInfo[0x76] = { "HALT", 0 };
    instructionInfo[0x77] = { "LD (HL), A", 0 };
    instructionInfo[0x78] = { "LD A, B", 0 };
    instructionInfo[0x79] = { "LD A, C", 0 };
    instructionInfo[0x7a] = { "LD A, D", 0 };
    instructionInfo[0x7b] = { "LD A, E", 0 };
    instructionInfo[0x7c] = { "LD A, H", 0 };
    instructionInfo[0x7d] = { "LD A, L", 0 };
    instructionInfo[0x7e] = { "LD A, (HL)", 0 };
    instructionInfo[0x7f] = { "LD A, A", 0 };
    instructionInfo[0x80] = { "ADD A, B", 0 };
    instructionInfo[0x81] = { "ADD A, C", 0 };
    instructionInfo[0x82] = { "ADD A, D", 0 };
    instructionInfo[0x83] = { "ADD A, E", 0 };
    instructionInfo[0x84] = { "ADD A, H", 0 };
    instructionInfo[0x85] = { "ADD A, L", 0 };
    instructionInfo[0x86] = { "ADD A, (HL)", 0 };
    instructionInfo[0x87] = { "ADD A, A", 0 };
    instructionInfo[0x88] = { "ADC A, B", 0 };
    instructionInfo[0x89] = { "ADC A, C", 0 };
    instructionInfo[0x8a] = { "ADC A, D", 0 };
    instructionInfo[0x8b] = { "ADC A, E", 0 };
    instructionInfo[0x8c] = { "ADC A, H", 0 };
    instructionInfo[0x8d] = { "ADC A, L", 0 };
    instructionInfo[0x8e] = { "ADC A, (HL)", 0 };
    instructionInfo[0x8f] = { "ADC A, A", 0 };
    instructionInfo[0x90] = { "SUB B", 0 };
    instructionInfo[0x91] = { "SUB C", 0 };
    instructionInfo[0x92] = { "SUB D", 0 };
    instructionInfo[0x93] = { "SUB E", 0 };
    instructionInfo[0x94] = { "SUB H", 0 };
    instructionInfo[0x95] = { "SUB L", 0 };
    instructionInfo[0x96] = { "SUB (HL)", 0 };
    instructionInfo[0x97] = { "SUB A", 0 };
    instructionInfo[0x98] = { "SBC A, B", 0 };
    instructionInfo[0x99] = { "SBC A, C", 0 };
    instructionInfo[0x9a] = { "SBC A, D", 0 };
    instructionInfo[0x9b] = { "SBC A, E", 0 };
    instructionInfo[0x9c] = { "SBC A, H", 0 };
    instructionInfo[0x9d] = { "SBC A, L", 0 };
    instructionInfo[0x9e] = { "SBC A, (HL)", 0 };
    instructionInfo[0x9f] = { "SBC A, A", 0 };
    instructionInfo[0xa0] = { "AND B", 0 };
    instructionInfo[0xa1] = { "AND C", 0 };
    instructionInfo[0xa2] = { "AND D", 0 };
    instructionInfo[0xa3] = { "AND E", 0 };
    instructionInfo[0xa4] = { "AND H", 0 };
    instructionInfo[0xa5] = { "AND L", 0 };
    instructionInfo[0xa6] = { "AND (HL)", 0 };
    instructionInfo[0xa7] = { "AND A", 0 };
    instructionInfo[0xa8] = { "XOR B", 0 };
    instructionInfo[0xa9] = { "XOR C", 0 };
    instructionInfo[0xaa] = { "XOR D", 0 };
    instructionInfo[0xab] = { "XOR E", 0 };
    instructionInfo[0xac] = { "XOR H", 0 };
    instructionInfo[0xad] = { "XOR L", 0 };
    instructionInfo[0xae] = { "XOR (HL)", 0 };
    instructionInfo[0xaf] = { "XOR A", 0 };
    instructionInfo[0xb0] = { "OR B", 0 };
    instructionInfo[0xb1] = { "OR C", 0 };
    instructionInfo[0xb2] = { "OR D", 0 };
    instructionInfo[0xb3] = { "OR E", 0 };
    instructionInfo[0xb4] = { "OR H", 0 };
    instructionInfo[0xb5] = { "OR L", 0 };
    instructionInfo[0xb6] = { "OR (HL)", 0 };
    instructionInfo[0xb7] = { "OR A", 0 };
    instructionInfo[0xb8] = { "CP B", 0 };
    instructionInfo[0xb9] = { "CP C", 0 };
    instructionInfo[0xba] = { "CP D", 0 };
    instructionInfo[0xbb] = { "CP E", 0 };
    instructionInfo[0xbc] = { "CP H", 0 };
    instructionInfo[0xbd] = { "CP L", 0 };
    instructionInfo[0xbe] = { "CP (HL)", 0 };
    instructionInfo[0xbf] = { "CP A", 0 };
    instructionInfo[0xc0] = { "RET NZ", 0 };
    instructionInfo[0xc1] = { "POP BC", 0 };
    instructionInfo[0xc2] = { "JP NZ, U16", 2 };
    instructionInfo[0xc3] = { "JP U16", 2 };
    instructionInfo[0xc4] = { "CALL NZ, U16", 2 };
    instructionInfo[0xc5] = { "PUSH BC", 0 };
    instructionInfo[0xc6] = { "ADD A, U8", 1 };
    instructionInfo[0xc7] = { "RST 00h", 0 };
    instructionInfo[0xc8] = { "RET Z", 0 };
    instructionInfo[0xc9] = { "RET", 0 };
    instructionInfo[0xca] = { "JP Z, U16", 2 };
    instructionInfo[0xcb] = { "CB PREFIX", 0 };
    instructionInfo[0xcc] = { "CALL Z, U16", 2 };
    instructionInfo[0xcd] = { "CALL U16", 2 };
    instructionInfo[0xce] = { "ADC A, U8", 1 };
    instructionInfo[0xcf] = { "RST 08h", 0 };
    instructionInfo[0xd0] = { "RET NC", 0 };
    instructionInfo[0xd1] = { "POP DE", 0 };
    instructionInfo[0xd2] = { "JP NC, U16", 2 };
    instructionInfo[0xd4] = { "CALL NC, U16", 2 };
    instructionInfo[0xd5] = { "PUSH DE", 0 };
    instructionInfo[0xd6] = { "SUB A, U8", 1 };
    instructionInfo[0xd7] = { "RST 10h", 0 };
    instructionInfo[0xd8] = { "RET C", 0 };
    instructionInfo[0xd9] = { "RETI", 0 };
    instructionInfo[0xda] = { "JP C, U16", 2 };
    instructionInfo[0xdc] = { "CALL C, U16", 2 };
    instructionInfo[0xde] = { "SBC A, U8", 1 };
    instructionInfo[0xdf] = { "RST 18h", 0 };
    instructionInfo[0xe0] = { "LD ($FF00+U8), A", 1 };
    instructionInfo[0xe1] = { "POP HL", 0 };
    instructionInfo[0xe2] = { "LD ($FF00+C), A", 0 };
    instructionInfo[0xe5] = { "PUSH HL", 0 };
    instructionInfo[0xe6] = { "AND U8", 0 };
    instructionInfo[0xe7] = { "RST 20h", 0 };
    instructionInfo[0xe8] = { "ADD SP, U8", 1 };
    instructionInfo[0xe9] = { "JP HL", 0 };
    instructionInfo[0xea] = { "LD (U16), A", 2 };
    instructionInfo[0xee] = { "XOR A, U8", 1 };
    instructionInfo[0xef] = { "RST 28h", 0 };
    instructionInfo[0xf0] = { "LD A, ($FF00+U8)", 1 };
    instructionInfo[0xf1] = { "POP AF", 0 };
    instructionInfo[0xf2] = { "LD A, ($FF00+C)", 0 };
    instructionInfo[0xf3] = { "DI", 0 };
    instructionInfo[0xf5] = { "PUSH AF", 0 };
    instructionInfo[0xf6] = { "OR A, U8", 1 };
    instructionInfo[0xf7] = { "RST 30h", 0 };
    instructionInfo[0xf8] = { "LD HL,SP+i8", 1 };
    instructionInfo[0xf9] = { "LD SP,HL", 0 };
    instructionInfo[0xfa] = { "LD A, (U16)", 2 };
    instructionInfo[0xfb] = { "EI", 0 };
    instructionInfo[0xfe] = { "CP U8", 1 };
    instructionInfo[0xff] = { "RST 38h", 0 };
}

cpu_debug::InstructionInfo cpu_debug::getInfoOf(uint8_t inst)
{
    return instructionInfo[inst];
}

QStringList cpu_debug::getInfo(bool includeRegs, bool dissasm)
{
    QStringList list;
    if(includeRegs){
    QString regs = "Registros:";
    QString qsa = "a:  0x" + QString::number(cpu.registers.a,16);
    QString qsb = "b:  0x" + QString::number(cpu.registers.b,16);
    QString qsc = "c:  0x" + QString::number(cpu.registers.c,16);
    QString qsd = "d:  0x" + QString::number(cpu.registers.d,16);
    QString qse = "e:  0x" + QString::number(cpu.registers.e,16);
    QString qsf = "f:  0x" + QString::number(cpu.registers.f,16);
    QString qsh = "h:  0x" + QString::number(cpu.registers.h,16);
    QString qsl = "l:  0x" + QString::number(cpu.registers.l,16);
    QString qssp = "sp:  0x" + QString::number(cpu.sp_dir,16);
    QString qspc = "pc:  0x" + QString::number(cpu.pc_dir,16);
    QStringList listRegs({regs, qsa, qsb, qsc, qsd, qse, qsf, qsh, qsl, qssp, qspc});
    list += listRegs;
    }
    list.append("Memoria:");
    uint8_t memInstructionCount = 0;
    for(uint16_t i = 0x100; i< 0x110; i++){
        MemorySegment *s = cpu.memory[i];
        uint8_t v = *s;
        QString instInfo = "";

        if(dissasm && memInstructionCount-- == 0){
            InstructionInfo info = instructionInfo[v];
            memInstructionCount = info.memory;
            instInfo += "\t" + info.description;
            qDebug() << instInfo << i;
        }

        list.append("0x" + QString::number(i,16) + ":  0x" + QString::number(v,16) + instInfo);
    }
    return list;

}

QStringList cpu_debug::getInfo(uint16_t to, uint16_t from, bool includeRegs, bool dissasm)
{
    QStringList list;
    if(includeRegs){
    QString regs = "Registros:";
    QString qsa = "a:  0x" + QString::number(cpu.registers.a,16);
    QString qsb = "b:  0x" + QString::number(cpu.registers.b,16);
    QString qsc = "c:  0x" + QString::number(cpu.registers.c,16);
    QString qsd = "d:  0x" + QString::number(cpu.registers.d,16);
    QString qse = "e:  0x" + QString::number(cpu.registers.e,16);
    QString qsf = "f:  0x" + QString::number(cpu.registers.f,16);
    QString qsh = "h:  0x" + QString::number(cpu.registers.h,16);
    QString qsl = "l:  0x" + QString::number(cpu.registers.l,16);
    QString qssp = "sp:  0x" + QString::number(cpu.sp_dir,16);
    QString qspc = "pc:  0x" + QString::number(cpu.pc_dir,16);
    QStringList listRegs({regs, qsa, qsb, qsc, qsd, qse, qsf, qsh, qsl, qssp, qspc});
    list += listRegs;
    }
    list.append("Memoria: (" + QString::number(from, 16) + " -- " + QString::number(to, 16) +")");

    uint8_t memInstructionCount = 0;
    for(uint16_t i = 0; i<=from - to; i++){
        MemorySegment *s = cpu.memory[i + to];
        uint8_t v = *s;
        QString instInfo = "";

        if(dissasm && memInstructionCount-- == 0){
            InstructionInfo info = instructionInfo[v];
            memInstructionCount = info.memory;
            instInfo += "\t" + info.description;
            qDebug() << instInfo << i;
        }
        list.append("0x" + QString::number(i + to,16) + ":  0x" + QString::number(v,16) + instInfo);
    }
    return list;


}
