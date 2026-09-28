#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x1d4];
    u8 *unk_1d4;
} BigObject;

typedef struct {
    u8 pad_000[0x178];
    s32 baseValue;
    u8 pad_17c[0x20];
    s8 bonusPercent;
} Actor;

extern BigObject *func_ov001_0206db5c(u32 handle);
extern s32 func_02023dbc(s32 numerator, s32 denominator);
extern s32 func_ov001_02075248(u32 handle);
extern s32 func_02050014(u32 handle, s32 flag);
extern s32 func_02050050(u32 handle, s32 flag);
extern s32 FixedPointMultiply12(s32 left, s32 right);
extern void func_ov021_020a75ec(BigObject *entity, s32 value);

/* Computes a level-scaled bonus value and applies it. */
void ComputeAndApplyLevelScaledValue_020d4d5c(Actor *actor, u32 handle)
{
    s32 flag;
    s32 bonus;
    BigObject *entity = func_ov001_0206db5c(handle);
    s32 levelFactor = (u32)*(u16 *)(entity->unk_1d4 + 8) * 0x1000;
    s32 scaledBase = func_02023dbc(actor->baseValue * (actor->bonusPercent + 100), 100);

    flag = func_ov001_02075248(handle);
    if ((flag != 0) && (flag = func_02050014(handle, 0x1c), flag != 0)) {
        bonus = FixedPointMultiply12(levelFactor, 0x280);
        levelFactor = levelFactor + bonus;
    }
    scaledBase = FixedPointMultiply12(scaledBase, levelFactor);
    flag = func_02050014(handle, 4);
    if (flag != 0) {
        bonus = func_02050050(handle, 4);
        bonus = func_02023dbc(scaledBase * bonus, 100);
        scaledBase = scaledBase + bonus;
    }
    flag = func_02050014(handle, 0x49);
    if (flag != 0) {
        bonus = FixedPointMultiply12(scaledBase, 0x480);
        scaledBase = scaledBase + bonus;
    }
    func_ov021_020a75ec(entity, (scaledBase << 4) >> 0x10);
}
