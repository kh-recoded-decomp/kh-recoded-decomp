#include "nitro/types.h"

typedef struct Actor {
    u8 pad_0000[0x930];
    u8 playerIndex;
    u8 pad_0931[7];
    u8 triggered : 8;
    u8 pad_0939[0x1704 - 0x939];
    s32 triggerTimer;
} Actor;

extern void *func_ov001_0206db78(u32 playerIndex);
extern BOOL func_ov021_020a752c(void *record, u16 mask);
extern u16 GetId10_020a755c(void *record);

void func_ov059_020c997c(Actor *actor)
{
    void *record = func_ov001_0206db78(actor->playerIndex);

    if (!func_ov021_020a752c(record, 0x400) && GetId10_020a755c(record) == 1 && !actor->triggered) {
        actor->triggered = 1;
        actor->triggerTimer = 0;
    }
}
