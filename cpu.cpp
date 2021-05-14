#include "cpu.h"
#include "memorysegment.h"

#define read16 MemorySegment* val = memory[pc]; pc+=2
#define read8 MemorySegment* val = memory[pc]; pc+=1
#define read_16(x) MemorySegment* val =memory[x]
#define read_8(x) MemorySegment* val = memory[x]



#define r16 memory[pc]; pc+=2
#define r8 memory[pc]; pc+=1
#define r_16(x) memory[x]
#define r_8(x) memory[x]




cppb::CPU::CPU(): a(&(registers.a), memory), b(&(registers.b), memory), c(&(registers.c), memory),
    d(&(registers.d), memory), e(&(registers.e), memory), f(&(registers.f), memory),
    h(&(registers.h), memory), l(&(registers.l), memory), af(&(registers.af), memory),
    bc(&(registers.bc), memory), de(&(registers.de), memory), hl(&(registers.hl), memory),
    sp(&(pc_dir), memory), pc(&(sp_dir), memory)
{
    instructions[0x00] = [this] {return; };
    instructions[0x01] = [this](){
        read16;
        uint16_t v = *val;
        bc = v;
        return;
    };
    instructions[0x02] = [this]() {
        *memory[bc] = (uint8_t)a;
        return;
    };
    instructions[0x03] = [this]() {
        bc = inc16(bc);
        return;
    };
    instructions[0x04] = [this]() {
        b = inc(b);
        return;
    };
    instructions[0x05] = [this]() {
        b = dec(b);
        return;
    };
    instructions[0x06] = [this]() {
        read8;
        load(&b, *val);
        return;
    };
    instructions[0x07] = [this]() {
        rlc(&a);
        return;
    };
    instructions[0x08] = [this]() {
        read16;
        *memory[(uint16_t)*val] = (uint16_t)sp;
        return;
    };
    instructions[0x9] = [this]() {
        add_hl(bc);
        return;
    };
    instructions[0x0a] = [this]() {
        load(&a, *memory[bc]);
        return;
    };
    instructions[0x0b] = [this]() {
        bc = dec16(bc);
        return;
    };
    instructions[0x0c] = [this]() {
        c = inc(c);
        return;
    };
    instructions[0x0d] = [this]() {
        c = dec(c);
        return;
    };
    instructions[0x0e] = [this]() {
        read8;
        load(&c, *val);
        return;
    };
    instructions[0x0f] = [this]() {
        rrc(&a);
        return;
    };
    instructions[0x10] = [this] {
        halt = true;
        stop = true;
        return;
    };
    instructions[0x11] = [this]() {
        read16;
        load_16(&de, *val);
        return;
    };
    instructions[0x12] = [this]() {
        read_8((uint16_t)de);
        *val = (uint8_t)a;
        return;
    };
    instructions[0x13] = [this]() {
        de = inc16(de);
        return;
    };
    instructions[0x14] = [this]() {
        d = inc(d);
        return;
    };
    instructions[0x15] = [this]() {
        d = dec(d);
        return;
    };
    instructions[0x16] = [this]() {
        read8;
        load(&d, *val);
        return;
    };
    instructions[0x17] = [this]() {
        rl(&a);
        return;
    };
    instructions[0x18] = [this]() {
        read8;
        int v = static_cast<int>((uint8_t)*val);
        pc += v;
        return;
    };
    instructions[0x19] = [this]() {
        add_hl(de);
        return;
    };
    instructions[0x1a] = [this]() {
        load(&a, *memory[de]);
        return;
    };
    instructions[0x1b] = [this]() {
        de = dec16(de);
        return;
    };
    instructions[0x1c] = [this]() {
        e = inc(e);
        return;
    };
    instructions[0x1d] = [this]() {
        e = dec(e);
        return;
    };
    instructions[0x1e] = [this]() {
        read8;
        load(&d, *val);
        return;
    };
    instructions[0x1f] = [this]() {
        rr(&a);
        return;
    };
    instructions[0x20] = [this] {
        read8;
        int v = static_cast<int>((uint8_t)*val);
        if (!registers.zero) {
            pc += v;
        }
        return;
    };
    instructions[0x21] = [this]() {
        read16;
        load_16(&hl, *val);
        return;
    };
    instructions[0x22] = [this]() {
        read_8(hl);
        load(val, a);
        hl = inc16(hl);
        return;
    };
    instructions[0x23] = [this]() {
        hl = inc16(hl);
        return;
    };
    instructions[0x24] = [this]() {
        h = inc(h);
        return;
    };
    instructions[0x25] = [this]() {
        h = dec(h);
        return;
    };
    instructions[0x26] = [this]() {
        read8;
        load(&h, *val);
        return;
    };
    instructions[0x27] = [this]() {
        daa();
        return;
    };
    instructions[0x28] = [this]() {
        read8;
        int v = static_cast<int>((uint8_t)*val);
        if (registers.zero) {
            pc += v;
        }
        return;
    };
    instructions[0x29] = [this]() {
        add_hl(hl);
        return;
    };
    instructions[0x2a] = [this]() {
        read_8(hl);
        load(&a, *val);
        hl = inc16(hl);
        return;
    };
    instructions[0x2b] = [this]() {
        hl = dec16(hl);
        return;
    };
    instructions[0x2c] = [this]() {
        l = inc(l);
        return;
    };
    instructions[0x2d] = [this]() {
        l = dec(l);
        return;
    };
    instructions[0x2e] = [this]() {
        read8;
        load(&l, *val);
        return;
    };
    instructions[0x2f] = [this]() {
        cpl();
        return;
    };
    instructions[0x30] = [this] {
        read8;
        int v = static_cast<int>((uint8_t)*val);
        if (!registers.carry) {
            pc += v;
        }
        return;
    };
    instructions[0x31] = [this]() {
        read16;
        load_16(&sp, *val);
        return;
    };
    instructions[0x32] = [this]() {
        read_8(hl);
        load(val, a);
        hl = dec16(hl);
        return;
    };
    instructions[0x33] = [this]() {
        sp = inc16(sp);
        return;
    };
    instructions[0x34] = [this]() {
        read_8(hl);
        *val = inc(*val);
        return;
    };
    instructions[0x35] = [this]() {
        read_8(hl);
        *val = dec(*val);
        return;
    };
    instructions[0x36] = [this]() {
        read8;
        MemorySegment *to_write = r_8((uint16_t)hl);
        load(to_write, *val);
        return;
    };
    instructions[0x37] = [this]() {
        scf();
        return;
    };
    instructions[0x38] = [this]() {
        read8;
        int v = static_cast<int>((uint8_t)*val);
        if (registers.carry) {
            pc += v;
        }
        return;
    };
    instructions[0x39] = [this]() {
        add_hl(sp);
        return;
    };
    instructions[0x3a] = [this]() {
        read_8(hl);
        load(&a, *val);
        hl = dec16(hl);
        return;
    };
    instructions[0x3b] = [this]() {
        sp = dec16(sp);
        return;
    };
    instructions[0x3c] = [this]() {
        a = inc(a);
        return;
    };
    instructions[0x3d] = [this]() {
        a = dec(a);
        return;
    };
    instructions[0x3e] = [this]() {
        read8;
        load(&a, *val);
        return;
    };
    instructions[0x3f] = [this]() {
        ccf();
        return;
    };
    instructions[0x40] = [this] {
        load(&b, b);
        return;
    };
    instructions[0x41] = [this]() {
        load(&b, c);
        return;
    };
    instructions[0x42] = [this]() {
        load(&b, d);
        return;
    };
    instructions[0x43] = [this]() {
        load(&b, e);
        return;
    };
    instructions[0x44] = [this]() {
        load(&b, h);
        return;
    };
    instructions[0x45] = [this]() {
        load(&b, l);
        return;
    };
    instructions[0x46] = [this]() {
        read_8(hl);
        load(&b, *val);
        return;
    };
    instructions[0x47] = [this]() {
        load(&b, a);
        return;
    };
    instructions[0x48] = [this]() {
        load(&c, b);
        return;
    };
    instructions[0x49] = [this]() {
        load(&c, c);
        return;
    };
    instructions[0x4a] = [this]() {
        load(&c, d);
        return;
    };
    instructions[0x4b] = [this]() {
        load(&c, e);
        return;
    };
    instructions[0x4c] = [this]() {
        load(&c,h);
        return;
    };
    instructions[0x4d] = [this]() {
        load(&c, l);
        return;
    };
    instructions[0x4e] = [this]() {
        read_8(hl);
        load(&c, *val);
        return;
    };
    instructions[0x4f] = [this]() {
        load(&c, a);
        return;
    };
    instructions[0x50] = [this] {
        load(&d, b);
        return;
    };
    instructions[0x51] = [this]() {
        load(&d, c);
        return;
    };
    instructions[0x52] = [this]() {
        load(&d, d);
        return;
    };
    instructions[0x53] = [this]() {
        load(&d, e);
        return;
    };
    instructions[0x54] = [this]() {
        load(&d, h);
        return;
    };
    instructions[0x55] = [this]() {
        load(&d, l);
        return;
    };
    instructions[0x56] = [this]() {
        read_8(hl);
        load(&d, *val);
        return;
    };
    instructions[0x57] = [this]() {
        load(&d, a);
        return;
    };
    instructions[0x58] = [this]() {
        load(&e, b);
        return;
    };
    instructions[0x59] = [this]() {
        load(&e, c);
        return;
    };
    instructions[0x5a] = [this]() {
        load(&e, d);
        return;
    };
    instructions[0x5b] = [this]() {
        load(&e, e);
        return;
    };
    instructions[0x5c] = [this]() {
        load(&e, h);
        return;
    };
    instructions[0x5d] = [this]() {
        load(&e, l);
        return;
    };
    instructions[0x5e] = [this]() {
        read_8(hl);
        load(&e, *val);
        return;
    };
    instructions[0x5f] = [this]() {
        load(&e, a);
        return;
    };
    instructions[0x60] = [this] {
        load(&h, b);
        return;
    };
    instructions[0x61] = [this]() {
        load(&h, c);
        return;
    };
    instructions[0x62] = [this]() {
        load(&h, d);
        return;
    };
    instructions[0x63] = [this]() {
        load(&h, e);
        return;
    };
    instructions[0x64] = [this]() {
        load(&h, h);
        return;
    };
    instructions[0x65] = [this]() {
        load(&h, l);
        return;
    };
    instructions[0x66] = [this]() {
        read_8(hl);
        load(&h, *val);
        return;
    };
    instructions[0x67] = [this]() {
        load(&h, a);
        return;
    };
    instructions[0x68] = [this]() {
        load(&l, b);
        return;
    };
    instructions[0x69] = [this]() {
        load(&l, c);
        return;
    };
    instructions[0x6a] = [this]() {
        load(&l, d);
        return;
    };
    instructions[0x6b] = [this]() {
        load(&l, e);
        return;
    };
    instructions[0x6c] = [this]() {
        load(&l, h);
        return;
    };
    instructions[0x6d] = [this]() {
        load(&l, l);
        return;
    };
    instructions[0x6e] = [this]() {
        read_8(hl);
        load(&l, *val);
        return;
    };
    instructions[0x6f] = [this]() {
        load(&l, a);
        return;
    };
    instructions[0x70] = [this] {
        read_8(hl);
        load(val, b);
        return;
    };
    instructions[0x71] = [this]() {
        read_8(hl);
        load(val, c);
        return;
    };
    instructions[0x72] = [this]() {
        read_8(hl);
        load(val, d);
        return;
    };
    instructions[0x73] = [this]() {
        read_8(hl);
        load(val, e);
        return;
    };
    instructions[0x74] = [this]() {
        read_8(hl);
        load(val, h);
        return;
    };
    instructions[0x75] = [this]() {
        read_8(hl);
        load(val, l);
        return;
    };
    instructions[0x76] = [this]() {
        halt = true;
        return;
    };
    instructions[0x77] = [this]() {
        read_8(hl);
        load(val, a);
        return;
    };
    instructions[0x78] = [this]() {
        load(&a, b);
        return;
    };
    instructions[0x79] = [this]() {
        load(&a, c);
        return;
    };
    instructions[0x7a] = [this]() {
        load(&a, d);
        return;
    };
    instructions[0x7b] = [this]() {
        load(&a, e);
        return;
    };
    instructions[0x7c] = [this]() {
        load(&a, h);
        return;
    };
    instructions[0x7d] = [this]() {
        load(&a, l);
        return;
    };
    instructions[0x7e] = [this]() {
        read_8(hl);
        load(&a, *val);
        return;
    };
    instructions[0x7f] = [this]() {
        load(&a, a);
        return;
    };
    instructions[0x80] = [this] {
        add(b);
        return;
    };
    instructions[0x81] = [this]() {
        add(c);
        return;
    };
    instructions[0x82] = [this]() {
        add(d);
        return;
    };
    instructions[0x83] = [this]() {
        add(e);
        return;
    };
    instructions[0x84] = [this]() {
        add(h);
        return;
    };
    instructions[0x85] = [this]() {
        add(l);
        return;
    };
    instructions[0x86] = [this]() {
        read_8(hl);
        add(*val);
        return;
    };
    instructions[0x87] = [this]() {
        add(a);
        return;
    };
    instructions[0x88] = [this]() {
        adc(b);
        return;
    };
    instructions[0x89] = [this]() {
        adc(c);
        return;
    };
    instructions[0x8a] = [this]() {
        adc(d);
        return;
    };
    instructions[0x8b] = [this]() {
        adc(e);
        return;
    };
    instructions[0x8c] = [this]() {
        adc(h);
        return;
    };
    instructions[0x8d] = [this]() {
        adc(l);
        return;
    };
    instructions[0x8e] = [this]() {
        read_8(hl);
        adc(*val);
        return;
    };
    instructions[0x8f] = [this]() {
        adc(a);
        return;
    };
    instructions[0x90] = [this] {
        sub(b);
        return;
    };
    instructions[0x91] = [this]() {
        sub(c);
        return;
    };
    instructions[0x92] = [this]() {
        sub(d);
        return;
    };
    instructions[0x93] = [this]() {
        sub(e);
        return;
    };
    instructions[0x94] = [this]() {
        sub(h);
        return;
    };
    instructions[0x95] = [this]() {
        sub(l);
        return;
    };
    instructions[0x96] = [this]() {
        read_8(hl);
        sub(*val);
        return;
    };
    instructions[0x97] = [this]() {
        sub(a);
        return;
    };
    instructions[0x98] = [this]() {
        sbc(b);
        return;
    };
    instructions[0x99] = [this]() {
        sbc(c);
        return;
    };
    instructions[0x9a] = [this]() {
        sbc(d);
        return;
    };
    instructions[0x9b] = [this]() {
        sbc(e);
        return;
    };
    instructions[0x9c] = [this]() {
        sbc(h);
        return;
    };
    instructions[0x9d] = [this]() {
        sbc(l);
        return;
    };
    instructions[0x9e] = [this]() {
        read_8(hl);
        sbc(*val);
        return;
    };
    instructions[0x9f] = [this]() {
        sbc(a);
        return;
    };
    instructions[0xa0] = [this] {
        and_op(b);
        return;
    };
    instructions[0xa1] = [this]() {
        and_op(c);
        return;
    };
    instructions[0xa2] = [this]() {
        and_op(d);
        return;
    };
    instructions[0xa3] = [this]() {
        and_op(e);
        return;
    };
    instructions[0xa4] = [this]() {
        and_op(h);
        return;
    };
    instructions[0xa5] = [this]() {
        and_op(l);
        return;
    };
    instructions[0xa6] = [this]() {
        read_8(hl);
        and_op(*val);
        return;
    };
    instructions[0xa7] = [this]() {
        and_op(a);
        return;
    };
    instructions[0xa8] = [this]() {
        xor_op(b);
        return;
    };
    instructions[0xa9] = [this]() {
        xor_op(c);
        return;
    };
    instructions[0xaa] = [this]() {
        xor_op(d);
        return;
    };
    instructions[0xab] = [this]() {
        xor_op(e);
        return;
    };
    instructions[0xac] = [this]() {
        xor_op(h);
        return;
    };
    instructions[0xad] = [this]() {
        xor_op(l);
        return;
    };
    instructions[0xae] = [this]() {
        read_8(hl);
        xor_op(*val);
        return;
    };
    instructions[0xaf] = [this]() {
        xor_op(a);
        return;
    };
    instructions[0xb0] = [this] {
        or_op(b);
        return;
    };
    instructions[0xb1] = [this]() {
        or_op(c);
        return;
    };
    instructions[0xb2] = [this]() {
        or_op(d);
        return;
    };
    instructions[0xb3] = [this]() {
        or_op(e);
        return;
    };
    instructions[0xb4] = [this]() {
        or_op(h);
        return;
    };
    instructions[0xb5] = [this]() {
        or_op(l);
        return;
    };
    instructions[0xb6] = [this]() {
        read_8(hl);
        or_op(*val);
        return;
    };
    instructions[0xb7] = [this]() {
        or_op(a);
        return;
    };
    instructions[0xb8] = [this]() {
        cp(b);
        return;
    };
    instructions[0xb9] = [this]() {
        cp(c);
        return;
    };
    instructions[0xba] = [this]() {
        cp(d);
        return;
    };
    instructions[0xbb] = [this]() {
        cp(e);
        return;
    };
    instructions[0xbc] = [this]() {
        cp(h);
        return;
    };
    instructions[0xbd] = [this]() {
        cp(l);
        return;
    };
    instructions[0xbe] = [this]() {
        read_8(hl);
        cp(*val);
        return;
    };
    instructions[0xbf] = [this]() {
        cp(a);
        return;
    };
    instructions[0xc0] = [this] {
        if (!registers.zero)
            pop(&pc);
        return;
    };
    instructions[0xc1] = [this]() {
        pop(&bc);
        return;
    };
    instructions[0xc2] = [this]() {
        read16;
        if (!registers.zero)
            jmp(*val);
        return;
    };
    instructions[0xc3] = [this]() {
        read16;
        jmp(*val);
        return;
    };
    instructions[0xc4] = [this]() {
        read16;
        if (!registers.zero) {
            push(pc);
            jmp(*val); }
        return;
    };
    instructions[0xc5] = [this]() {
        push(bc);
        return;
    };
    instructions[0xc6] = [this]() {
        read8;
        add(*val);
        return;
    };
    instructions[0xc7] = [this]() {
        push(pc);
        pc = (uint16_t)0;
        return;
    };
    instructions[0xc8] = [this]() {
        if (registers.zero)
            pop(&pc);
        return;
    };
    instructions[0xc9] = [this]() {
        pop(&pc);
        return;
    };
    instructions[0xca] = [this]() {
        read16;
        if (registers.zero)
            jmp(*val);
        return;
    };
    instructions[0xcb] = [this]() {
        cp(e);
        return;
    };
    instructions[0xcc] = [this]() {
        read16;
        if (registers.zero) {
            push(pc);
            jmp(*val); }
        return;
    };
    instructions[0xcd] = [this]() {
        read16;
        push(pc);
        jmp(*val);
        return;
    };
    instructions[0xce] = [this]() {
        read8;
        adc(*val);
        return;
    };
    instructions[0xcf] = [this]() {
        push(pc);
        pc = (uint16_t)(0+0x08);
        return;
    };
    instructions[0xd0] = [this] {
        if (!registers.carry)
            pop(&pc);
        return;
    };
    instructions[0xd1] = [this]() {
        pop(&de);
        return;
    };
    instructions[0xd2] = [this]() {
        read16;
        if (!registers.carry)
            jmp(*val);
        return;
    };
    instructions[0xd3] = [this]() {
        return;
    };
    instructions[0xd4] = [this]() {
        read16;
        if (!registers.carry) {
            push(pc);
            jmp(*val);
        }
        return;
    };
    instructions[0xd5] = [this]() {
        push(de);
        return;
    };
    instructions[0xd6] = [this]() {
        read8;
        sub(*val);
        return;
    };
    instructions[0xd7] = [this]() {
        push(pc);
        pc = (uint16_t)(0+0x10);
        return;
    };
    instructions[0xd8] = [this]() {
        if (registers.carry)
            pop(&pc);
        return;
    };
    instructions[0xd9] = [this]() {
        pop(&pc);
        intr = true;
        return;
    };
    instructions[0xda] = [this]() {
        read16;
        if (registers.carry)
            jmp(*val);
        return;
    };
    instructions[0xdb] = [this]() {
        return;
    };
    instructions[0xdc] = [this]() {
        read16;
        if (registers.carry) {
            push(pc);
            jmp(*val);
        }
        return;
    };
    instructions[0xdd] = [this]() {
        return;
    };
    instructions[0xde] = [this]() {
        read8;
        sbc(*val);
        return;
    };
    instructions[0xdf] = [this]() {
        push(pc);
        pc = (uint16_t)(0 + 0x18);
        return;
    };
    instructions[0xe0] = [this] {
        read8;
        MemorySegment* to_push = r_8((uint16_t)(0xFF00 + (uint8_t)*val));
        *to_push = (uint8_t)a;
        return;
    };
    instructions[0xe1] = [this]() {
        pop(&hl);
        return;
    };
    instructions[0xe2] = [this]() {
        MemorySegment *val = r_8((uint16_t)(0xFF00 + (uint8_t)c));
        *val = (uint8_t)a;
        return;
    };
    instructions[0xe3] = [this]() {
        return;
    };
    instructions[0xe4] = [this]() {
        return;
    };
    instructions[0xe5] = [this]() {
        push(hl);
        return;
    };
    instructions[0xe6] = [this]() {
        read8;
        and_op(*val);
        return;
    };
    instructions[0xe7] = [this]() {
        push(pc);
        pc = (uint16_t)(0 + 0x20);
        return;
    };
    instructions[0xe8] = [this]() {
        read8;
        int v = static_cast<int>((uint8_t)*val);
        add_sp(v);
        return;
    };
    instructions[0xe9] = [this]() {
        pc = (uint16_t)hl;
        return;
    };
    instructions[0xea] = [this]() {
        return;
    };
    instructions[0xeb] = [this]() {
        return;
    };
    instructions[0xec] = [this]() {
        return;
    };
    instructions[0xed] = [this]() {
        return;
    };
    instructions[0xee] = [this]() {
        read8;
        xor_op(*val);
        return;
    };
    instructions[0xef] = [this]() {
        push(pc);
        pc = (uint16_t)(0 + 0x28);
        return;
    };
    instructions[0xf0] = [this] {
        read8;
        MemorySegment* to_push = r_8((uint16_t)(0xFF00 + (uint8_t)*val));
        a = (uint8_t)*to_push;
        return;
    };
    instructions[0xf1] = [this]() {
        pop(&af);
        return;
    };
    instructions[0xf2] = [this]() {
        MemorySegment *val = r_8((uint16_t)(0xFF00 + (uint8_t)c));
        a = (uint8_t)*val;
        return;
    };
    instructions[0xf3] = [this]() {
        intr = false;
        return;
    };
    instructions[0xf4] = [this]() {
        return;
    };
    instructions[0xf5] = [this]() {
        push(af);
        return;
    };
    instructions[0xf6] = [this]() {
        read8;
        or_op(*val);
        return;
    };
    instructions[0xf7] = [this]() {
        push(pc);
        pc = (uint16_t)(0 + 0x30);
        return;
    };
    instructions[0xf8] = [this]() {
        read8;
        int v = static_cast<int>((uint8_t)*val);
        int r = v + (uint16_t)sp;

        clearAllFlags();
        if (((uint16_t)sp ^ v ^ r) & 0x100)
            setFlags(F_CARRY);
        if (((uint16_t)sp ^ v ^ r) & 0x10)
            setFlags(F_HALF);
        hl = (uint16_t)r;
        return;
    };
    instructions[0xf9] = [this]() {
        sp = (uint16_t)hl;
        return;
    };
    instructions[0xfa] = [this]() {
        read16;
        MemorySegment* to_load = r_8((uint16_t)*val);
        a = (uint8_t)*to_load;
        return;
    };
    instructions[0xfb] = [this]() {
        intr = true;
        return;
    };
    instructions[0xfc] = [this]() {

        return;
    };
    instructions[0xfd] = [this]() {

        return;
    };
    instructions[0xfe] = [this]() {
        read8;
        cp(*val);
        return;
    };
    instructions[0xff] = [this]() {
        push(pc);
        pc = (uint16_t)(0 + 0x38);
        return;
    };



    //CB
    cb_instructions[0x00] = [this] {
        rlc(&b);
        return;
    };
    cb_instructions[0x01] = [this]() {
        rlc(&c);
        return;
    };
    cb_instructions[0x02] = [this]() {
        rlc(&d);
        return;
    };
    cb_instructions[0x03] = [this]() {
        rlc(&e);
        return;
    };
    cb_instructions[0x04] = [this]() {
        rlc(&h);
        return;
    };
    cb_instructions[0x05] = [this]() {
        rlc(&l);
        return;
    };
    cb_instructions[0x06] = [this]() {
        read_8(hl);
        rlc(val);
        return;
    };
    cb_instructions[0x07] = [this]() {
        rlc(&a);
        return;
    };
    cb_instructions[0x08] = [this]() {
        rrc(&b);
        return;
    };
    cb_instructions[0x09] = [this]() {
        rrc(&c);
        return;
    };
    cb_instructions[0x0a] = [this]() {
        rrc(&d);
        return;
    };
    cb_instructions[0x0b] = [this]() {
        rrc(&e);
        return;
    };
    cb_instructions[0x0c] = [this]() {
        rrc(&h);
        return;
    };
    cb_instructions[0x0d] = [this]() {
        rrc(&l);
        return;
    };
    cb_instructions[0x0e] = [this]() {
        read_8(hl);
        rrc(val);
        return;
    };
    cb_instructions[0x0f] = [this]() {
        rrc(&a);
        return;
    };
    cb_instructions[0x10] = [this] {
        rl(&b);
        return;
    };
    cb_instructions[0x11] = [this]() {
        rl(&c);
        return;
    };
    cb_instructions[0x12] = [this]() {
        rl(&d);
        return;
    };
    cb_instructions[0x13] = [this]() {
        rl(&e);
        return;
    };
    cb_instructions[0x14] = [this]() {
        rl(&h);
        return;
    };
    cb_instructions[0x15] = [this]() {
        rl(&l);
        return;
    };
    cb_instructions[0x16] = [this]() {
        read_8(hl);
        rl(val);
        return;
    };
    cb_instructions[0x17] = [this]() {
        rl(&a);
        return;
    };
    cb_instructions[0x18] = [this]() {
        rr(&b);
        return;
    };
    cb_instructions[0x19] = [this]() {
        rr(&c);
        return;
    };
    cb_instructions[0x1a] = [this]() {
        rr(&d);
        return;
    };
    cb_instructions[0x1b] = [this]() {
        rr(&e);
        return;
    };
    cb_instructions[0x1c] = [this]() {
        rr(&h);
        return;
    };
    cb_instructions[0x1d] = [this]() {
        rr(&l);
        return;
    };
    cb_instructions[0x1e] = [this]() {
        read_8(hl);
        rr(val);
        return;
    };
    cb_instructions[0x1f] = [this]() {
        rr(&a);
        return;
    };
    cb_instructions[0x20] = [this] {
        sla(&b);
        return;
    };
    cb_instructions[0x21] = [this]() {
        sla(&c);
        return;
    };
    cb_instructions[0x22] = [this]() {
        sla(&d);
        return;
    };
    cb_instructions[0x23] = [this]() {
        sla(&e);
        return;
    };
    cb_instructions[0x24] = [this]() {
        sla(&h);
        return;
    };
    cb_instructions[0x25] = [this]() {
        sla(&l);
        return;
    };
    cb_instructions[0x26] = [this]() {
        read_8(hl);
        sla(val);
        return;
    };
    cb_instructions[0x27] = [this]() {
        sla(&a);
        return;
    };
    cb_instructions[0x28] = [this]() {
        sra(&b);
        return;
    };
    cb_instructions[0x29] = [this]() {
        sra(&c);
        return;
    };
    cb_instructions[0x2a] = [this]() {
        sra(&d);
        return;
    };
    cb_instructions[0x2b] = [this]() {
        sra(&e);
        return;
    };
    cb_instructions[0x2c] = [this]() {
        sra(&h);
        return;
    };
    cb_instructions[0x2d] = [this]() {
        sra(&l);
        return;
    };
    cb_instructions[0x2e] = [this]() {
        read_8(hl);
        sra(val);
        return;
    };
    cb_instructions[0x2f] = [this]() {
        sra(&a);
        return;
    };
    cb_instructions[0x30] = [this] {
        swap(&b);
        return;
    };
    cb_instructions[0x31] = [this]() {
        swap(&c);
        return;
    };
    cb_instructions[0x32] = [this]() {
        swap(&d);
        return;
    };
    cb_instructions[0x33] = [this]() {
        swap(&e);
        return;
    };
    cb_instructions[0x34] = [this]() {
        swap(&h);
        return;
    };
    cb_instructions[0x35] = [this]() {
        swap(&l);
        return;
    };
    cb_instructions[0x36] = [this]() {
        read_8(hl);
        swap(val);
        return;
    };
    cb_instructions[0x37] = [this]() {
        swap(&a);
        return;
    };
    cb_instructions[0x38] = [this]() {
        srl(&b);
        return;
    };
    cb_instructions[0x39] = [this]() {
        srl(&c);
        return;
    };
    cb_instructions[0x3a] = [this]() {
        srl(&d);
        return;
    };
    cb_instructions[0x3b] = [this]() {
        srl(&e);
        return;
    };
    cb_instructions[0x3c] = [this]() {
        srl(&h);
        return;
    };
    cb_instructions[0x3d] = [this]() {
        srl(&l);
        return;
    };
    cb_instructions[0x3e] = [this]() {
        read_8(hl);
        srl(val);
        return;
    };
    cb_instructions[0x3f] = [this]() {
        srl(&a);
        return;
    };
    cb_instructions[0x40] = [this] {
        bit(0, b);
        return;
    };
    cb_instructions[0x41] = [this]() {
        bit(0, c);
        return;
    };
    cb_instructions[0x42] = [this]() {
        bit(0, d);
        return;
    };
    cb_instructions[0x43] = [this]() {
        bit(0, e);
        return;
    };
    cb_instructions[0x44] = [this]() {
        bit(0, h);
        return;
    };
    cb_instructions[0x45] = [this]() {
        bit(0, l);
        return;
    };
    cb_instructions[0x46] = [this]() {
        read_8(hl);
        bit(0, *val);
        return;
    };
    cb_instructions[0x47] = [this]() {
        bit(0, a);
        return;
    };
    cb_instructions[0x48] = [this]() {
        bit(1, b);
        return;
    };
    cb_instructions[0x49] = [this]() {
        bit(1, c);
        return;
    };
    cb_instructions[0x4a] = [this]() {
        bit(1, d);
        return;
    };
    cb_instructions[0x4b] = [this]() {
        bit(1, e);
        return;
    };
    cb_instructions[0x4c] = [this]() {
        bit(1, h);
        return;
    };
    cb_instructions[0x4d] = [this]() {
        bit(1, l);
        return;
    };
    cb_instructions[0x4e] = [this]() {
        read_8(hl);
        bit(1, *val);
        return;
    };
    cb_instructions[0x4f] = [this]() {
        bit(1, a);
        return;
    };
    cb_instructions[0x50] = [this] {
        bit(2, b);
        return;
    };
    cb_instructions[0x51] = [this]() {
        bit(2, c);
        return;
    };
    cb_instructions[0x52] = [this]() {
        bit(2, d);
        return;
    };
    cb_instructions[0x53] = [this]() {
        bit(2, e);
        return;
    };
    cb_instructions[0x54] = [this]() {
        bit(2, h);
        return;
    };
    cb_instructions[0x55] = [this]() {
        bit(2, l);
        return;
    };
    cb_instructions[0x56] = [this]() {
        read_8(hl);
        bit(2, *val);
        return;
    };
    cb_instructions[0x57] = [this]() {
        bit(2, a);
        return;
    };
    cb_instructions[0x58] = [this]() {
        bit(3, b);
        return;
    };
    cb_instructions[0x59] = [this]() {
        bit(3, c);
        return;
    };
    cb_instructions[0x5a] = [this]() {
        bit(3, d);
        return;
    };
    cb_instructions[0x5b] = [this]() {
        bit(3, e);
        return;
    };
    cb_instructions[0x5c] = [this]() {
        bit(3, h);
        return;
    };
    cb_instructions[0x5d] = [this]() {
        bit(3, l);
        return;
    };
    cb_instructions[0x5e] = [this]() {
        read_8(hl);
        bit(3, *val);
        return;
    };
    cb_instructions[0x5f] = [this]() {
        bit(3, a);
        return;
    };
    cb_instructions[0x60] = [this] {
        bit(4, b);
        return;
    };
    cb_instructions[0x61] = [this]() {
        bit(4, c);
        return;
    };
    cb_instructions[0x62] = [this]() {
        bit(4, d);
        return;
    };
    cb_instructions[0x63] = [this]() {
        bit(4, e);
        return;
    };
    cb_instructions[0x64] = [this]() {
        bit(4, h);
        return;
    };
    cb_instructions[0x65] = [this]() {
        bit(4, l);
        return;
    };
    cb_instructions[0x66] = [this]() {
        read_8(hl);
        bit(4, *val);
        return;
    };
    cb_instructions[0x67] = [this]() {
        bit(4, a);
        return;
    };
    cb_instructions[0x68] = [this]() {
        bit(5, b);
        return;
    };
    cb_instructions[0x69] = [this]() {
        bit(5, c);
        return;
    };
    cb_instructions[0x6a] = [this]() {
        bit(5, d);
        return;
    };
    cb_instructions[0x6b] = [this]() {
        bit(5, e);
        return;
    };
    cb_instructions[0x6c] = [this]() {
        bit(5, h);
        return;
    };
    cb_instructions[0x6d] = [this]() {
        bit(5, l);
        return;
    };
    cb_instructions[0x6e] = [this]() {
        read_8(hl);
        bit(5, *val);
        return;
    };
    cb_instructions[0x6f] = [this]() {
        bit(5, a);
        return;
    };
    cb_instructions[0x70] = [this] {
        bit(6, b);
        return;
    };
    cb_instructions[0x71] = [this]() {
        bit(6, c);
        return;
    };
    cb_instructions[0x72] = [this]() {
        bit(6, d);
        return;
    };
    cb_instructions[0x73] = [this]() {
        bit(6, e);
        return;
    };
    cb_instructions[0x74] = [this]() {
        bit(6, h);
        return;
    };
    cb_instructions[0x75] = [this]() {
        bit(6, l);
        return;
    };
    cb_instructions[0x76] = [this]() {
        read_8(hl);
        bit(6, *val);
        return;
    };
    cb_instructions[0x77] = [this]() {
        bit(6, a);
        return;
    };
    cb_instructions[0x78] = [this]() {
        bit(7, b);
        return;
    };
    cb_instructions[0x79] = [this]() {
        bit(7, c);
        return;
    };
    cb_instructions[0x7a] = [this]() {
        bit(7, d);
        return;
    };
    cb_instructions[0x7b] = [this]() {
        bit(7, e);
        return;
    };
    cb_instructions[0x7c] = [this]() {
        bit(7, h);
        return;
    };
    cb_instructions[0x7d] = [this]() {
        bit(7, l);
        return;
    };
    cb_instructions[0x7e] = [this]() {
        read_8(hl);
        bit(7, *val);
        return;
    };
    cb_instructions[0x7f] = [this]() {
        bit(7, a);
        return;
    };
    cb_instructions[0x80] = [this] {
        res(0, &b);
        return;
    };
    cb_instructions[0x81] = [this]() {
        res(0, &c);
        return;
    };
    cb_instructions[0x82] = [this]() {
        res(0, &d);
        return;
    };
    cb_instructions[0x83] = [this]() {
        res(0, &e);
        return;
    };
    cb_instructions[0x84] = [this]() {
        res(0, &h);
        return;
    };
    cb_instructions[0x85] = [this]() {
        res(0, &l);
        return;
    };
    cb_instructions[0x86] = [this]() {
        read_8(hl);
        res(0, val);
        return;
    };
    cb_instructions[0x87] = [this]() {
        res(0, &a);
        return;
    };
    cb_instructions[0x88] = [this]() {
        res(1, &b);
        return;
    };
    cb_instructions[0x89] = [this]() {
        res(1, &c);
        return;
    };
    cb_instructions[0x8a] = [this]() {
        res(1, &d);
        return;
    };
    cb_instructions[0x8b] = [this]() {
        res(1, &e);
        return;
    };
    cb_instructions[0x8c] = [this]() {
        res(1, &h);
        return;
    };
    cb_instructions[0x8d] = [this]() {
        res(1, &l);
        return;
    };
    cb_instructions[0x8e] = [this]() {
        read_8(hl);
        res(1, val);
        return;
    };
    cb_instructions[0x8f] = [this]() {
        res(1, &a);
        return;
    };
    cb_instructions[0x90] = [this] {
        res(2, &b);
        return;
    };
    cb_instructions[0x91] = [this]() {
        res(2, &c);
        return;
    };
    cb_instructions[0x92] = [this]() {
        res(2, &d);
        return;
    };
    cb_instructions[0x93] = [this]() {
        res(2, &e);
        return;
    };
    cb_instructions[0x94] = [this]() {
        res(2, &h);
        return;
    };
    cb_instructions[0x95] = [this]() {
        res(2, &l);
        return;
    };
    cb_instructions[0x96] = [this]() {
        read_8(hl);
        res(2, val);
        return;
    };
    cb_instructions[0x97] = [this]() {
        res(2, &a);
        return;
    };
    cb_instructions[0x98] = [this]() {
        res(3, &b);
        return;
    };
    cb_instructions[0x99] = [this]() {
        res(3, &c);
        return;
    };
    cb_instructions[0x9a] = [this]() {
        res(3, &d);
        return;
    };
    cb_instructions[0x9b] = [this]() {
        res(3, &e);
        return;
    };
    cb_instructions[0x9c] = [this]() {
        res(3, &h);
        return;
    };
    cb_instructions[0x9d] = [this]() {
        res(3, &l);
        return;
    };
    cb_instructions[0x9e] = [this]() {
        read_8(hl);
        res(3, val);
        return;
    };
    cb_instructions[0x9f] = [this]() {
        res(3, &a);
        return;
    };
    cb_instructions[0xa0] = [this] {
        res(4, &b);
        return;
    };
    cb_instructions[0xa1] = [this]() {
        res(4, &c);
        return;
    };
    cb_instructions[0xa2] = [this]() {
        res(4, &d);
        return;
    };
    cb_instructions[0xa3] = [this]() {
        res(4, &e);
        return;
    };
    cb_instructions[0xa4] = [this]() {
        res(4, &h);
        return;
    };
    cb_instructions[0xa5] = [this]() {
        res(4, &l);
        return;
    };
    cb_instructions[0xa6] = [this]() {
        read_8(hl);
        res(4, val);
        return;
    };
    cb_instructions[0xa7] = [this]() {
        res(4, &a);
        return;
    };
    cb_instructions[0xa8] = [this]() {
        res(5, &b);
        return;
    };
    cb_instructions[0xa9] = [this]() {
        res(5, &c);
        return;
    };
    cb_instructions[0xaa] = [this]() {
        res(5, &d);
        return;
    };
    cb_instructions[0xab] = [this]() {
        res(5, &e);
        return;
    };
    cb_instructions[0xac] = [this]() {
        res(5, &h);
        return;
    };
    cb_instructions[0xad] = [this]() {
        res(5, &l);
        return;
    };
    cb_instructions[0xae] = [this]() {
        read_8(hl);
        res(5, val);
        return;
    };
    cb_instructions[0xaf] = [this]() {
        res(5, &a);
        return;
    };
    cb_instructions[0xb0] = [this] {
        res(6, &b);
        return;
    };
    cb_instructions[0xb1] = [this]() {
        res(6, &c);
        return;
    };
    cb_instructions[0xb2] = [this]() {
        res(6, &d);
        return;
    };
    cb_instructions[0xb3] = [this]() {
        res(6, &e);
        return;
    };
    cb_instructions[0xb4] = [this]() {
        res(6, &h);
        return;
    };
    cb_instructions[0xb5] = [this]() {
        res(6, &l);
        return;
    };
    cb_instructions[0xb6] = [this]() {
        read_8(hl);
        res(6, val);
        return;
    };
    cb_instructions[0xb7] = [this]() {
        res(6, &a);
        return;
    };
    cb_instructions[0xb8] = [this]() {
        res(7, &b);
        return;
    };
    cb_instructions[0xb9] = [this]() {
        res(7, &c);
        return;
    };
    cb_instructions[0xba] = [this]() {
        res(7, &d);
        return;
    };
    cb_instructions[0xbb] = [this]() {
        res(7, &e);
        return;
    };
    cb_instructions[0xbc] = [this]() {
        res(7, &h);
        return;
    };
    cb_instructions[0xbd] = [this]() {
        res(7, &l);
        return;
    };
    cb_instructions[0xbe] = [this]() {
        read_8(hl);
        res(7, val);
        return;
    };
    cb_instructions[0xbf] = [this]() {
        res(7, &a);
        return;
    };
    cb_instructions[0xc0] = [this] {
        set(0, &b);
        return;
    };
    cb_instructions[0xc1] = [this]() {
        set(0, &c);
        return;
    };
    cb_instructions[0xc2] = [this]() {
        set(0, &d);
        return;
    };
    cb_instructions[0xc3] = [this]() {
        set(0, &e);
        return;
    };
    cb_instructions[0xc4] = [this]() {
        set(0, &h);
        return;
    };
    cb_instructions[0xc5] = [this]() {
        set(0, &l);
        return;
    };
    cb_instructions[0xc6] = [this]() {
        read_8(hl);
        set(0, val);
        return;
    };
    cb_instructions[0xc7] = [this]() {
        set(0, &a);
        return;
    };
    cb_instructions[0xc8] = [this]() {
        set(1, &b);
        return;
    };
    cb_instructions[0xc9] = [this]() {
        set(1, &c);
        return;
    };
    cb_instructions[0xca] = [this]() {
        set(1, &d);
        return;
    };
    cb_instructions[0xcb] = [this]() {
        set(1, &e);
        return;
    };
    cb_instructions[0xcc] = [this]() {
        set(1, &h);
        return;
    };
    cb_instructions[0xcd] = [this]() {
        set(1, &l);
        return;
    };
    cb_instructions[0xce] = [this]() {
        read_8(hl);
        set(1, val);
        return;
    };
    cb_instructions[0xcf] = [this]() {
        set(1, &a);
        return;
    };
    cb_instructions[0xd0] = [this] {
        set(2, &b);
        return;
    };
    cb_instructions[0xd1] = [this]() {
        set(2, &c);
        return;
    };
    cb_instructions[0xd2] = [this]() {
        set(2, &d);
        return;
    };
    cb_instructions[0xd3] = [this]() {
        set(2, &e);
        return;
    };
    cb_instructions[0xd4] = [this]() {
        set(2, &h);
        return;
    };
    cb_instructions[0xd5] = [this]() {
        set(2, &l);
        return;
    };
    cb_instructions[0xd6] = [this]() {
        read_8(hl);
        set(2, val);
        return;
    };
    cb_instructions[0xd7] = [this]() {
        set(2, &a);
        return;
    };
    cb_instructions[0xd8] = [this]() {
        set(3, &b);
        return;
    };
    cb_instructions[0xd9] = [this]() {
        set(3, &c);
        return;
    };
    cb_instructions[0xda] = [this]() {
        set(3, &d);
        return;
    };
    cb_instructions[0xdb] = [this]() {
        set(3, &e);
        return;
    };
    cb_instructions[0xdc] = [this]() {
        set(3, &h);
        return;
    };
    cb_instructions[0xdd] = [this]() {
        set(3, &l);
        return;
    };
    cb_instructions[0xde] = [this]() {
        read_8(hl);
        set(3, val);
        return;
    };
    cb_instructions[0xdf] = [this]() {
        set(3, &a);
        return;
    };
    cb_instructions[0xe0] = [this] {
        set(4, &b);
        return;
    };
    cb_instructions[0xe1] = [this]() {
        set(4, &c);
        return;
    };
    cb_instructions[0xe2] = [this]() {
        set(4, &d);
        return;
    };
    cb_instructions[0xe3] = [this]() {
        set(4, &e);
        return;
    };
    cb_instructions[0xe4] = [this]() {
        set(4, &h);
        return;
    };
    cb_instructions[0xe5] = [this]() {
        set(4, &l);
        return;
    };
    cb_instructions[0xe6] = [this]() {
        read_8(hl);
        set(4, val);
        return;
    };
    cb_instructions[0xe7] = [this]() {
        set(4, &a);
        return;
    };
    cb_instructions[0xe8] = [this]() {
        set(5, &b);
        return;
    };
    cb_instructions[0xe9] = [this]() {
        set(5, &c);
        return;
    };
    cb_instructions[0xea] = [this]() {
        set(5, &d);
        return;
    };
    cb_instructions[0xeb] = [this]() {
        set(5, &e);
        return;
    };
    cb_instructions[0xec] = [this]() {
        set(5, &h);
        return;
    };
    cb_instructions[0xed] = [this]() {
        set(5, &l);
        return;
    };
    cb_instructions[0xee] = [this]() {
        read_8(hl);
        set(5, val);
        return;
    };
    cb_instructions[0xef] = [this]() {
        set(5, &a);
        return;
    };
    cb_instructions[0xf0] = [this] {
        set(6, &b);
        return;
    };
    cb_instructions[0xf1] = [this]() {
        set(6, &c);
        return;
    };
    cb_instructions[0xf2] = [this]() {
        set(6, &d);
        return;
    };
    cb_instructions[0xf3] = [this]() {
        set(6, &e);
        return;
    };
    cb_instructions[0xf4] = [this]() {
        set(6, &h);
        return;
    };
    cb_instructions[0xf5] = [this]() {
        set(6, &l);
        return;
    };
    cb_instructions[0xf6] = [this]() {
        read_8(hl);
        set(6, val);
        return;
    };
    cb_instructions[0xf7] = [this]() {
        set(6, &a);
        return;
    };
    cb_instructions[0xf8] = [this]() {
        set(7, &b);
        return;
    };
    cb_instructions[0xf9] = [this]() {
        set(7, &c);
        return;
    };
    cb_instructions[0xfa] = [this]() {
        set(7, &d);
        return;
    };
    cb_instructions[0xfb] = [this]() {
        set(7, &e);
        return;
    };
    cb_instructions[0xfc] = [this]() {
        set(7, &h);
        return;
    };
    cb_instructions[0xfd] = [this]() {
        set(7, &l);
        return;
    };
    cb_instructions[0xfe] = [this]() {
        read_8(hl);
        set(7, val);
        return;
    };
    cb_instructions[0xff] = [this]() {
        set(7, &a);
        return;
    };
}

void cppb::CPU::clearAllFlags()
{
    f = (uint8_t)((uint8_t)f & 0x0f);
}

void cppb::CPU::clearFlags(uint8_t flags)
{
    f = (uint8_t)((uint8_t)f &(~flags));
}

void cppb::CPU::setAllFlags()
{
    f = (uint8_t)((uint8_t)f | 0xF0);
}

void cppb::CPU::setFlags(uint8_t flags)
{
    f = (uint8_t)((uint8_t)f |flags);
}

void cppb::CPU::load(MemorySegment* dst, uint8_t src)
{
    *dst = src;
}

void cppb::CPU::load_16(MemorySegment* dst, uint16_t src)
{
    *dst = src;
}

void cppb::CPU::push(uint16_t val)
{
    MemorySegment* mem = memory[--sp];
    *mem = (uint8_t)((val & 0xFF00) >> 8);
    mem = memory[--sp];
    *mem = (uint8_t)(val & 0x00FF);
}

void cppb::CPU::pop(MemorySegment* dst)
{
    uint8_t l, h;
    MemorySegment* mem = memory[sp++];
    l = *mem;
    mem = memory[sp++];
    h = *mem;
    *dst = (uint16_t)((uint16_t)(h << 8) + l);
}

void cppb::CPU::jmp(uint16_t val)
{
    pc = val;
}

uint8_t cppb::CPU::inc(uint8_t value)
{
    clearFlags(F_HALF | F_ZERO | F_NEG);
    if ((value & 0x0f) == 0x0f) registers.half_c = 1;

    uint8_t r = value+1;

    if (r == 0) registers.zero = 1;

    return r;
}

uint8_t cppb::CPU::dec(uint8_t value)
{

    clearFlags(F_HALF | F_ZERO | F_NEG);

    uint8_t r = value - 1;

    if ((r & 0x0f) == 0x0f) registers.half_c = 1;


    if (r == 0)  registers.zero = 1;

    registers.neg = 1;

    return r;
}

void cppb::CPU::add(uint8_t value)
{
    clearAllFlags();

    int result = (uint8_t)a + value;

    int carrys = (uint8_t)a ^ value ^ result;

    if (result == 0) setFlags(F_ZERO);

    if (carrys & 0x100) setFlags(F_CARRY);
    if (carrys & 0x10) setFlags(F_HALF);

    a = static_cast<uint8_t>(result);

    registers.neg = 0;
}

void cppb::CPU::adc(uint8_t value)
{
    int result = (uint8_t)a + value + registers.carry;
    clearAllFlags();


    if (result == 0)
        setFlags(F_ZERO);


    if (result > 0xFF)
        setFlags(F_CARRY);

    if (static_cast<unsigned int>((uint8_t)a & 0x0F) + static_cast<unsigned int>(value & 0x0F) + static_cast<unsigned int>(registers.carry) > 0x0F)
        setFlags(F_HALF);

    setFlags(F_NEG);
    a = static_cast<uint8_t>(result);
}

void cppb::CPU::sbc(uint8_t value)
{
    int result = (uint8_t)a - value - registers.carry;
    clearAllFlags();
    if (result == 0)
        setFlags(F_ZERO);
    if (result < 0)
        setFlags(F_CARRY);
    if (static_cast<int>((uint8_t)a & 0x0F) - static_cast<int>(value & 0x0F) - static_cast<int>(registers.carry) < 0)
        setFlags(F_HALF);
    a = static_cast<uint8_t>(result);
}

void cppb::CPU::sub(uint8_t value)
{
    int result = (uint8_t)a - value;

    int carrys = (uint8_t)a ^ value ^ result;

    clearAllFlags();

    if (result == 0) setFlags(F_ZERO);

    if (carrys & 0x100) setFlags(F_CARRY);
    if (carrys & 0x10) setFlags(F_HALF);

    a = static_cast<uint8_t>(result);

    registers.neg = 1;

}

void cppb::CPU::and_op(uint8_t value)
{
    a = (uint8_t)((uint8_t)a & value);
    clearAllFlags();
    setFlags(F_HALF);
    if ((uint8_t)a == 0) setFlags(F_ZERO);
}

void cppb::CPU::or_op(uint8_t value)
{
    a = (uint8_t)((uint8_t)a | value);
    clearAllFlags();
    if ((uint8_t)a == 0) setFlags(F_ZERO);
}

void cppb::CPU::xor_op(uint8_t value)
{
    a = (uint8_t)((uint8_t)a ^ value);
    clearAllFlags();
    if ((uint8_t)a == 0) setFlags(F_ZERO);
}

void cppb::CPU::cp(uint8_t value)
{
    int result = (uint8_t)a - value;
    clearAllFlags();
    int carrys = (uint8_t)a ^ value ^ result;

    if (result == 0) setFlags(F_ZERO);

    if (carrys & 0x100) setFlags(F_CARRY);
    if (carrys & 0x10) setFlags(F_HALF);

    registers.neg = 1;

}

void cppb::CPU::add_hl(uint16_t value)
{
    clearFlags(F_NEG | F_CARRY | F_HALF);

    int result = (uint16_t)hl + value;

    int carrys = (uint16_t)hl ^ value ^ result;


    if (carrys & 0x10000) setFlags(F_CARRY);
    if (carrys & 0x1000) setFlags(F_HALF);

    hl = static_cast<uint16_t>(result);

    registers.neg = 0;
}

void cppb::CPU::add_sp(int8_t value)
{
    int result = (uint16_t)sp + value;
    clearAllFlags();
    if ((((uint16_t)sp ^ value ^ (result & 0xFFFF)) & 0x100) == 0x100)
    {
        setFlags(F_CARRY);
    }
    if ((((uint16_t)sp ^ value ^ (result & 0xFFFF)) & 0x10) == 0x10)
    {
        setFlags(F_HALF);
    }
    sp = static_cast<uint16_t> (result);
}

uint16_t cppb::CPU::inc16(uint16_t value)
{
    return value + 1;
}

uint16_t cppb::CPU::dec16(uint16_t value)
{
    return value - 1;
}

void cppb::CPU::swap(MemorySegment* dst)
{
    clearAllFlags();
    uint8_t val = *dst;
    uint8_t h = (val & 0xF0) >> 4;
    uint8_t l = (val & 0x0F);

    uint8_t r = (l << 4) + h;

    if (r == 0) setFlags(F_ZERO);
    *dst = r;

}

void cppb::CPU::daa()
{
    int a_r = static_cast<int>((uint8_t)a);

    if (!registers.neg)
    {
        if (registers.half_c || ((a_r & 0xF) > 9))
            a_r += 0x06;

        if (registers.carry || (a_r > 0x9F))
            a_r += 0x60;
    }
    else
    {
        if (registers.half_c)
            a_r = (a_r - 6) & 0xFF;

        if (registers.carry)
            a_r -= 0x60;
    }

    clearFlags(F_CARRY | F_ZERO | F_HALF);

    if ((a_r & 0x100) == 0x100)
        setFlags(F_CARRY);

    a_r &= 0xFF;

    if (a_r == 0) setFlags(F_ZERO);

    this->a = (uint8_t)a_r;
}

void cppb::CPU::cpl()
{
    a = (uint8_t)(~((uint8_t)a));
    setFlags(F_HALF | F_NEG);
}

void cppb::CPU::ccf()
{
    registers.carry = ~registers.carry;
    clearFlags(F_HALF | F_NEG);
}

void cppb::CPU::scf()
{
    registers.carry = 1;
    clearFlags(F_HALF | F_NEG);
}

void cppb::CPU::rlc(MemorySegment* val)
{
    clearAllFlags();
    uint8_t v = *val;
    registers.carry = v & 0x80;
    v = v << 1;
    v = v | registers.carry;
    if (v == 0) setFlags(F_ZERO);
    *val = v;
}

void cppb::CPU::rl(MemorySegment* val)
{
    uint8_t old_c = registers.carry;
    clearAllFlags();
    uint8_t v = *val;
    registers.carry = v & 0x80;
    v = v << 1;
    v = v | old_c;
    if (v == 0) setFlags(F_ZERO);
    *val = v;
}

void cppb::CPU::rrc(MemorySegment* val)
{
    clearAllFlags();
    uint8_t v = *val;
    registers.carry = v & 0x1;
    v = v >> 1;
    v = v | ((registers.carry & 0x1) <<7);
    if (v == 0) setFlags(F_ZERO);
    *val = v;
}

void cppb::CPU::rr(MemorySegment* val)
{

    uint8_t old_c = registers.carry;
    clearAllFlags();
    uint8_t v = *val;
    registers.carry = v & 0x1;
    v = v >> 1;
    v = v | ((old_c & 0x1) << 7);
    if (v == 0) setFlags(F_ZERO);
    *val = v;
}

void cppb::CPU::sla(MemorySegment* val)
{
    clearAllFlags();
    uint8_t v = *val;
    registers.carry = v & 0x80;
    v = v << 1;
    v = v & (uint8_t)(~0x1);
    if (v == 0) setFlags(F_ZERO);
    *val = v;
}

void cppb::CPU::sra(MemorySegment* val)
{
    clearAllFlags();
    uint8_t v = *val;
    registers.carry = v & 0x1;
    if (v & 0x80) {
        v = v >> 1;
        v |= 0x80;
    }
    else
        v = v >> 1;
    if (v == 0) setFlags(F_ZERO);
    *val = v;
}

void cppb::CPU::srl(MemorySegment* val)
{
    clearAllFlags();
    uint8_t v = *val;
    registers.carry = v & 0x1;
    v = v >> 1;
    v &= (uint8_t)(~0x80);
    if (v == 0) setFlags(F_ZERO);
    *val = v;
}

void cppb::CPU::bit(uint8_t b, uint8_t val)
{
    registers.zero = (val >> b) & 0x1;
    setFlags(F_HALF);
    clearFlags(F_NEG);
}

void cppb::CPU::set(uint8_t b, MemorySegment *val)
{
    uint8_t v = *val;
    v = v | (0x1 << b);
    *val = v;
}

void cppb::CPU::res(uint8_t b, MemorySegment* val)
{
    uint8_t v = *val;
    v = v & ~(0x1 << b);
    *val = v;
}

