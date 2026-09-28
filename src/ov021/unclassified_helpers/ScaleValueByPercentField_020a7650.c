#include "nitro/types.h"

extern s32 func_02023dbc(s32 numerator, s32 denominator);
extern s32 FixedPointMultiply12(s32 left, s32 right);

typedef struct {
    u8 pad_000[0x1d4];
    u8 *unk_1d4;
} BigObject;

/* Result is computed but unused. */
void ScaleValueByPercentField_020a7650(BigObject *obj, s32 value)
{
    s32 fraction = func_02023dbc((u32)*(u16 *)(obj->unk_1d4 + 4) << 0xc, 100);
    FixedPointMultiply12(fraction, value);
}
