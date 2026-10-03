#include "nitro/types.h"

typedef struct {
    u8 pad_00000[0xc];
    u32 pending;
    u8 pad_00010[0x11ff4 - 0x10];
    s32 mode;
} MenuWork;

extern void func_ov077_020c5cc8(MenuWork *work);
extern void func_ov077_020c58e0(MenuWork *work);
extern void *func_ov039_020bc1bc(void);
extern void SetFlagGatedElementsVisible_020c9d7c(void *container, BOOL visible);

void SetModeTwoAndRefresh_020c4bb0(MenuWork *work)
{
    work->mode = 2;
    if (work->pending != 0) {
        func_ov077_020c5cc8(work);
        work->pending = 0;
        return;
    }
    func_ov077_020c58e0(work);
    SetFlagGatedElementsVisible_020c9d7c(func_ov039_020bc1bc(), TRUE);
}
