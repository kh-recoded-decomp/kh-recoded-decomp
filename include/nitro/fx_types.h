/* Fixed-point scalar types, with the NitroSDK's names: fx16 is 1.3.12, fx32 is 1.19.12, fx64 is
 * 1.51.12 and fx64c is 1.31.32. */
#ifndef NITRO_FX_TYPES_H
#define NITRO_FX_TYPES_H

#include "nitro/types.h"

typedef s16 fx16;
typedef s32 fx32;
typedef s64 fx64;
typedef s64 fx64c;

/* A 3D vector of fx32. */
typedef struct VecFx32 {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

#endif
