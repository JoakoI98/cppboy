#ifndef ROM_H
#define ROM_H
#include <stdint.h>
namespace cppb {
class ROM
{
public:
    virtual void ROMWrite(uint8_t val, uint16_t pos) = 0;
};
}
#endif // ROM_H
