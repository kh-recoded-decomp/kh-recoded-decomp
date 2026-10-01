#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScaleSource {
    u32 unk_00_0 : 18;
    u32 kind : 5;
    u32 unk_00_23 : 9;
    u32 unk_04_0 : 16;
    u32 level : 8;
    u32 unk_04_24 : 8;
    u8 pad_08[4];
    u16 divisor;
} ScaleSource;

typedef struct ScaleTarget {
    u8 pad_00[0x30];
    fx32 value;
} ScaleTarget;

extern fx32 FixedPointMultiply12_02006450(fx32 left, fx32 right);
extern s32 Div32_02023dbc(s32 dividend, s32 divisor);
extern s64 Mul64_02023d9c(s64 a, s64 b);

fx32 ScaleValueByLevelFactor_020bcbe0(ScaleSource *source, ScaleTarget *target) {
    fx32 factor;
    u32 level = source->level;

    if (level <= 1) {
        factor = 0x800;
    } else {
        factor = Div32_02023dbc(level * 0xB34, (u8)source->divisor) + 0x4CC;
        if (source->kind == 3) {
            factor = FixedPointMultiply12_02006450(factor, 0x1800);
        }
    }
    return (Mul64_02023d9c(target->value, factor) + 0x800) >> 12;
}
