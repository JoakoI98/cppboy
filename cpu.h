#ifndef CPU_H
#define CPU_H


#include <stdint.h>
#include <functional>

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

        uint8_t* memory;

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

        void clearAllFlags();
        void clearFlags(uint8_t flags);
        void setAllFlags();
        void setFlags(uint8_t flags);

        //8-bit load
        void load(uint8_t* dst, uint8_t src);

        //16-bit load
        void load_16(uint16_t* dst, uint16_t src);
        void push(uint16_t val);
        void pop(uint16_t* dst);
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
        void swap(uint8_t* dst);
        void daa();
        void cpl();
        void ccf();
        void scf();

        //Rotates and shifts
        void rlc(uint8_t* val);
        void rl(uint8_t* val);
        void rrc(uint8_t* val);
        void rr(uint8_t* val);
        void sla(uint8_t* val);
        void sra(uint8_t* val);
        void srl(uint8_t* val);

        //Bit opcodes
        void bit(uint8_t b, uint8_t val);
        void set(uint8_t b, uint8_t *val);
        void res(uint8_t b, uint8_t *val);

    public:
        CPU();
        regs registers;
        uint16_t pc = 0;
        uint16_t sp;
        bool halt;
        bool stop;
        bool intr;
        uint8_t& a = registers.a;
        uint8_t& b = registers.b;
        uint8_t& c = registers.c;
        uint8_t& d = registers.d;
        uint8_t& e = registers.e;
        uint8_t& f = registers.f;
        uint8_t& h = registers.h;
        uint8_t& l = registers.l;
        uint16_t& af = registers.af;
        uint16_t& bc = registers.bc;
        uint16_t& de = registers.de;
        uint16_t& hl = registers.hl;


    };

}



#endif // CPU_H
