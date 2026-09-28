#include "nitro/types.h"

extern u32 func_02002ed8(void);

BOOL TestStatusBit28_02002f24(void) {
    u32 status;

    status = func_02002ed8();
    return (status & 0x10000000) != 0;
}
