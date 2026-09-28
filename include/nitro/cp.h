/* The divider and square-root coprocessor, as the library sources declare them (the NitroSDK / NitroSystem names). */
#ifndef NITRO_CP_H
#define NITRO_CP_H

#include "nitro/types.h"

struct CPContext;

typedef struct CPContext {
    u64 div_numer;
    u64 div_denom;
    u64 sqrt;
    u16 div_mode;
    u16 sqrt_mode;
} CPContext;

#define CP_DIV_32_32BIT_MODE 0

#endif
