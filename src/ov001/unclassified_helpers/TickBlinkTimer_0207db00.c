#include "nitro/types.h"

typedef struct RecordPool RecordPool;

typedef struct BlinkState {
    u8 pad_00[0x24];
    u16 timer;
    u8 pad_26[2];
    u32 flags;
    u8 pad_2C[8];
    int vramOffset;
} BlinkState;

extern RecordPool *GetSceneTagTracker_020711b0(void);
extern int GFXi_EnqueueCommand_02014090(int command, int value, int address, int size);
extern void *FindActiveRecordById_020b8184(RecordPool *pool, u32 recordId);
extern void InvokeCallback40_020b8268(RecordPool *pool, void *record);

void TickBlinkTimer_0207db00(BlinkState *blink)
{
    RecordPool *pool = GetSceneTagTracker_020711b0();

    if (blink->timer == 0) {
        return;
    }
    if (blink->timer >= 6) {
        GFXi_EnqueueCommand_02014090(0xf, 0x1c2, blink->vramOffset + 2, 0xe);
        blink->timer = 0;
        blink->flags |= 2;
        InvokeCallback40_020b8268(pool, FindActiveRecordById_020b8184(pool, 0x137));
    } else {
        blink->timer++;
    }
}
