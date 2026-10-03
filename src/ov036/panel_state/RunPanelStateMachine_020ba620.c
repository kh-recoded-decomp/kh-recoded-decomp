#include "nitro/types.h"

typedef int (*PanelStateFn)(void);

typedef struct PanelWork {
    u8 pad_00[0x6];
    u16 flags;
    s32 state;
} PanelWork;

typedef struct PanelContext {
    u32 unk_00;
    PanelWork *work;
} PanelContext;

extern PanelContext data_ov036_020c3920;
extern PanelStateFn data_ov036_020c36d8[];
extern void UpdatePendingSlotScene_020bafa8(void);
extern void func_ov036_020bb284(int arg);
extern void func_ov036_020bb130(void);

int RunPanelStateMachine_020ba620(void)
{
    int next;

    do {
        data_ov036_020c3920.work->flags &= 0x7fff;
        next = data_ov036_020c36d8[data_ov036_020c3920.work->state]();
        if (next >= 0) {
            data_ov036_020c3920.work->state = next;
        }
    } while (data_ov036_020c3920.work->flags & 0x8000);
    UpdatePendingSlotScene_020bafa8();
    if (data_ov036_020c3920.work->flags & 8) {
        func_ov036_020bb284(0);
    }
    func_ov036_020bb130();
    return 0;
}
