#include "nitro/types.h"

typedef struct VariantEntry {
    u8 pad_00[5];
    s8 savedBits;
    u8 pad_06[2];
} VariantEntry;

typedef struct FieldObject {
    u8 pad_00[0x4E];
    u16 flags;
    u8 pad_50[0x10];
    VariantEntry *variants;
    u8 pad_64[0x18];
    s8 variantCount;
    s8 variantIndex;
    u8 pad_7E[3];
    u8 timer;
} FieldObject;

typedef struct FieldState {
    u8 pad_000[0x214];
    u32 flagsLow : 19;
    u32 variantPending : 1;
    u32 flagsHigh : 12;
} FieldState;

extern FieldState *data_ov001_020a0460;

extern u32 random_next_scaled_0202aa04(int range);
extern void FieldObject_SetSavedBits1To6_02084728(FieldObject *object, int bits);

void FieldObject_AdvanceRandomVariant_020846a4(FieldObject *object)
{
    u32 step;

    if (object->variantCount != 0) {
        step = random_next_scaled_0202aa04(object->variantCount - 1);
    } else {
        step = 0;
    }
    object->variantIndex = (object->variantIndex + 1 + step) % object->variantCount;
    FieldObject_SetSavedBits1To6_02084728(object, object->variants[object->variantIndex].savedBits);
    object->timer = 0;
    object->flags &= 0xFFEF;
    object->flags &= 0xFFDF;
    data_ov001_020a0460->variantPending = 0;
}
