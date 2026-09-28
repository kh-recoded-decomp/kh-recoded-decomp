#include "nitro/types.h"

void SetFieldAt0x2c_02001b1c(int obj, u16 value) {
    *(u16 *)(obj + 0x2c) = value;
}
