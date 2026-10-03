#include "nitro/types.h"

typedef struct HealthStats {
    u16 pad0;
    u16 current;
    u16 max;
} HealthStats;

typedef struct BigObject {
    u8 pad_000[0x1d4];
    HealthStats *health;
} BigObject;

extern s32 ScaleValueByPercentField_020a7650(BigObject *obj, s32 value);
extern BOOL func_ov021_020a75ec(BigObject *obj, int delta);

void ApplyScaledHealthDelta_020a7620(BigObject *obj, s32 amount, BOOL force)
{
    s32 scaled = ScaleValueByPercentField_020a7650(obj, amount);
    if (obj->health->current != 0 || force) {
        func_ov021_020a75ec(obj, (s16)((scaled + 0xfff) >> 12));
    }
}
