#ifndef MEMORYSEGMENT_H
#define MEMORYSEGMENT_H
#include <stdint.h>
#include "memorymanager.h"


class MemoryManager;
class MemorySegment
{
public:
    MemorySegment(MemoryManager& manager, size_t i): manager(manager), i(i){
        i_set = true;
        manager_set = true;
    }
    MemorySegment(MemoryManager& manager): manager(manager){
        manager_set = true;
    }

    virtual operator uint8_t() const {return val;}
    virtual operator uint16_t() const;
    virtual operator size_t() const;

    virtual void operator=(const uint8_t& v) {val = v;}
    virtual void operator=(const uint16_t& v);
    virtual MemorySegment &operator+=(const uint8_t& a){
        val += a;
        return *this;
    }
    virtual MemorySegment &operator-=(const uint8_t& a){
        val -= a;
        return *this;
    }
    virtual MemorySegment &operator++(){
        val += 1;
        return *this;
    }
    virtual MemorySegment &operator--(){
        val -= 1;
        return *this;
    }
    virtual MemorySegment &operator++(int){
        val += 1;
        return *this;
    }
    virtual MemorySegment &operator--(int){
        val -= 1;
        return *this;
    }

    void setI(size_t i){
        if(!i_set){
            this->i = i;
            i_set = true;
        }
    }
    void setManager(MemoryManager &manager){
        if(!manager_set){
            this->manager = manager;
            manager_set = true;
        }
    }

private:
    MemoryManager& manager;
    size_t i;
    uint8_t val;
    bool i_set = false;
    bool manager_set = false;
};

class MemorySegment_Register8: public MemorySegment
{
public:
    MemorySegment_Register8(uint8_t *dir, MemoryManager& manager): MemorySegment(manager, 0), dir(dir){}

    virtual operator uint8_t() const {return *dir;}
    virtual operator uint16_t() const {return 0;}
    virtual operator size_t() const {return 0;}

    virtual void operator=(const uint8_t& v) {*dir = v;}
    virtual void operator=(const uint16_t& v){return;}


    virtual MemorySegment &operator+=(const uint8_t& a){
        *dir += a;
        return *this;
    }
    virtual MemorySegment &operator-=(const uint8_t& a){
        *dir -= a;
        return *this;
    }
    virtual MemorySegment &operator++(){
        *dir += 1;
        return *this;
    }
    virtual MemorySegment &operator--(){
        *dir -= 1;
        return *this;
    }
    virtual MemorySegment &operator++(int){
        *dir += 1;
        return *this;
    }
    virtual MemorySegment &operator--(int){
        *dir -= 1;
        return *this;
    }


private:
    uint8_t *dir;

};


class MemorySegment_Register16: public MemorySegment
{
public:
    MemorySegment_Register16(uint16_t *dir, MemoryManager& manager): MemorySegment(manager, 0), dir(dir){}

    virtual operator uint8_t() const {return 0;}
    virtual operator uint16_t() const {return *dir;}
    virtual operator size_t() const {return *dir;}

    virtual void operator=(const uint8_t& v) {return;}
    virtual void operator=(const uint16_t& v){*dir = v;}

    virtual MemorySegment &operator+=(const uint16_t& a){
        *dir += a;
        return *this;
    }
    virtual MemorySegment &operator-=(const uint16_t& a){
        *dir -= a;
        return *this;
    }
    virtual MemorySegment &operator++(){
        *dir += 1;
        return *this;
    }
    virtual MemorySegment &operator--(){
        *dir -= 1;
        return *this;
    }
    virtual MemorySegment &operator++(int){
        *dir += 1;
        return *this;
    }
    virtual MemorySegment &operator--(int){
        *dir -= 1;
        return *this;
    }

private:
    uint16_t *dir;

};

#endif // MEMORYSEGMENT_H
