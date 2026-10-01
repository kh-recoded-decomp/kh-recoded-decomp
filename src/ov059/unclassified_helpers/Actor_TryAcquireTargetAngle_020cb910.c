#include "nitro/types.h"

typedef struct Actor {
    u8 pad_000[0x930];
    u8 targetIndex;
    u8 pad_931[0x31];
    s16 targetAngle;
} Actor;

extern void *func_ov001_0206db78(u8 index);
extern s32 func_02050014(u32 handle, s32 flag);
extern BOOL func_ov021_020a7504(void *target);
extern u16 QuantizeSummedAngle_020cd334(void *angles);
extern const s16 data_0205356c[];

BOOL Actor_TryAcquireTargetAngle_020cb910(Actor *actor)
{
    void *target = func_ov001_0206db78(actor->targetIndex);
    u16 angle;

    if (func_02050014(actor->targetIndex, 10) == 0) {
        return FALSE;
    }
    if (func_ov021_020a7504(target)) {
        angle = QuantizeSummedAngle_020cd334(target);
        if (data_0205356c[angle >> 4] > -data_0205356c[0x200]) {
            actor->targetAngle = angle;
            return TRUE;
        }
    }
    return FALSE;
}
