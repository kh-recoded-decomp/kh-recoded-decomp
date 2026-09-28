#include "nitro/types.h"

extern u16 GetU16Field_020049f0(void);

u32 SelectCodeByFlag_02009278(void) {
    if (GetU16Field_020049f0() == 1) {
        return 7;
    }
    return 3;
}
