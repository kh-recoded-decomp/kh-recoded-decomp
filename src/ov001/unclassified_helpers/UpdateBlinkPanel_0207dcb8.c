#include "nitro/types.h"

typedef struct BlinkFlags {
    s32 pendingA : 1;
    s32 pendingB : 1;
    s32 rest : 30;
} BlinkFlags;

typedef struct BlinkState {
    u8 pad_00[4];
    s32 active;
    s32 fading;
    u8 pad_0C[0x1a];
    u16 frame : 14;
    u16 mode : 2;
    BlinkFlags flags;
} BlinkState;

extern BlinkState *data_ov001_020a04d0;

extern int func_0202a7a4(void);
extern void TickBlinkTimer_0207db00(BlinkState *blink);
extern void func_ov001_0207db50(BlinkState *blink);
extern void func_ov001_0207d848(BlinkState *blink);

BOOL UpdateBlinkPanel_0207dcb8(void)
{
    BlinkState *blink = data_ov001_020a04d0;

    func_0202a7a4();
    if (blink->active != 0) {
        if (blink->flags.pendingB && blink->flags.pendingA) {
            blink->flags.pendingA = 0;
            blink->flags.pendingB = 0;
            blink->frame = 1;
        }
        TickBlinkTimer_0207db00(blink);
        func_ov001_0207db50(blink);
        func_ov001_0207d848(blink);
    } else if (blink->fading != 0) {
        func_ov001_0207d848(blink);
    }
    return FALSE;
}
