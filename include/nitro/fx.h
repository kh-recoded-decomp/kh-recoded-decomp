/* Fixed-point math (the NitroSDK names). */
#ifndef NITRO_FX_H
#define NITRO_FX_H

#include "nitro/fx_types.h"

/* --- generated from the library sources' declarations --- */
#include "nitro/types.h"

struct Mtx22;
struct MtxFx43;
struct VecFx16;

typedef struct VecFx16 {
    fx16 x;
    fx16 y;
    fx16 z;
} VecFx16;

typedef struct Mtx22 {
    int m[4];
} Mtx22;

typedef struct MtxFx43 {
    fx32 _00, _01, _02;
    fx32 _10, _11, _12;
    fx32 _20, _21, _22;
    fx32 _30, _31, _32;
} MtxFx43;

typedef struct { int _00, _01, _10, _11; } MtxFx22;

#define FX_MUL(a, b) ((fx32)(((s64)(a) * (b)) >> 12))

#define FX32_SHIFT 12

typedef union {
        struct {
            fx32 _00, _01;
            fx32 _10, _11;
            fx32 _20, _21;
        };
        fx32 m[3][2];
        fx32 a[6];
    }
    MtxFx32;

#define FX32_ONE ((fx32) 0x0000000000001000L)         // 1.000000000000

typedef union {
        struct {
            fx32 _00, _01, _02;
            fx32 _10, _11, _12;
            fx32 _20, _21, _22;
        };
        fx32 m[3][3];
        fx32 a[9];
    } MtxFx33;

typedef union {
        struct {
            fx32 _00, _01, _02, _03;
            fx32 _10, _11, _12, _13;
            fx32 _20, _21, _22, _23;
            fx32 _30, _31, _32, _33;
        };
        fx32 m[4][4];
        fx32 a[16];
    } MtxFx44;

#endif
