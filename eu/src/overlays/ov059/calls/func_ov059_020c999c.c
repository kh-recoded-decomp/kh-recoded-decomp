#define func_ov001_0206db78 GetPlayerControlState
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
extern BOOL HasFlagsAt0xe(void *record, u16 mask);
extern u16 SharedObject_GetId(void *record);

void func_ov059_020c999c(Actor *actor)
{
    void *record = func_ov001_0206db78(actor->playerIndex);

    if (!HasFlagsAt0xe(record, 0x400) && SharedObject_GetId(record) == 1 && !actor->triggered) {
        actor->triggered = 1;
        actor->triggerTimer = 0;
    }
}
