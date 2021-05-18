#ifndef CPU_H
#define CPU_H


#include <stdint.h>
#include <functional>
#include <qstringlist.h>
#include "../memory/memorymanager.h"


#define F_ZERO 0x80
#define F_NEG 0x40
#define F_HALF 0x20
#define F_CARRY 0x10

namespace cppb
{


    class CPU
    {
    private:

        typedef std::function<void()> instruction;

        MemoryManager memory;

        instruction instructions[256];
        instruction cb_instructions[256];


        union regs
        {
            uint8_t regs[8];
            struct {
                uint8_t a;
                uint8_t f;
                uint8_t b;
                uint8_t c;
                uint8_t d;
                uint8_t e;
                uint8_t h;
                uint8_t l;
            };
            struct {
                uint16_t af;
                uint16_t bc;
                uint16_t de;
                uint16_t hl;
            };
            struct {
                uint8_t :8;

                uint8_t : 4;//0 allways
                uint8_t carry : 1;
                uint8_t half_c : 1;
                uint8_t neg : 1;
                uint8_t zero: 1;

                uint32_t :32;
                uint16_t : 16;
            };


        };

        union InterruptMask{
            uint8_t mask;
            struct {
                uint8_t v_blank: 1;
                uint8_t lcd_start: 1;
                uint8_t timer: 1;
                uint8_t serial: 1;
                uint8_t joypad: 1;
                uint8_t: 3;
            };
        };

        void clearAllFlags();
        void clearFlags(uint8_t flags);
        void setAllFlags();
        void setFlags(uint8_t flags);

        //8-bit load
        void load(MemorySegment* dst, uint8_t src);

        //16-bit load
        void load_16(MemorySegment* dst, uint16_t src);
        void push(uint16_t val);
        void pop(MemorySegment* dst);
        void jmp(uint16_t val);

        //8-bit alu
        uint8_t inc(uint8_t value);
        uint8_t dec(uint8_t value);
        void add(uint8_t value);
        void adc(uint8_t value);
        void sbc(uint8_t value);
        void sub(uint8_t value);
        void and_op(uint8_t value);
        void or_op(uint8_t value);
        void xor_op(uint8_t value);
        void cp(uint8_t value);

        //16-bit alu
        void add_hl(uint16_t value);
        void add_sp(int8_t value);
        uint16_t inc16(uint16_t value);
        uint16_t dec16(uint16_t value);

        //Misc
        void swap(MemorySegment* dst);
        void daa();
        void cpl();
        void ccf();
        void scf();

        //Rotates and shifts
        void rlc(MemorySegment* val);
        void rl(MemorySegment* val);
        void rrc(MemorySegment* val);
        void rr(MemorySegment* val);
        void sla(MemorySegment* val);
        void sra(MemorySegment* val);
        void srl(MemorySegment* val);

        //Bit opcodes
        void bit(uint8_t b, uint8_t val);
        void set(uint8_t b, MemorySegment *val);
        void res(uint8_t b, MemorySegment *val);


        uint16_t pc_dir;
        uint16_t sp_dir;

    public:
        //Debugging
        QStringList getInfo(bool includeRegs = false);
        QStringList getInfo(uint16_t to, uint16_t from, bool includeRegs = false);

        //Cicle run
        void ejec();

        CPU();
        regs registers;

        //States
        bool halt = false;
        bool stop = false;
        bool intr = false;




        //Registers
        MemorySegment_Register8 a;
        MemorySegment_Register8 b;
        MemorySegment_Register8 c;
        MemorySegment_Register8 d;
        MemorySegment_Register8 e;
        MemorySegment_Register8 f;
        MemorySegment_Register8 h;
        MemorySegment_Register8 l;
        MemorySegment_Register16 af;
        MemorySegment_Register16 bc;
        MemorySegment_Register16 de;
        MemorySegment_Register16 hl;
        MemorySegment_Register16 sp;
        MemorySegment_Register16 pc;

        //Interrupt Handling
        InterruptMask checkInterrupts();

    };

}



#endif // CPU_H
