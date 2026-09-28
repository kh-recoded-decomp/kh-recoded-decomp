#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    u32 slotA;
    u32 slotB;
    u32 freeFlag;
    u8 pad_14[0x30];
    u32 registration;
    u8 pad_48[0x10];
    u8 engineObject[1];
} ScreenState;

extern void func_ov001_020715ac(u32 arg0);
extern int Obj_Release_0204eff8(void *object);
extern int ZeroHalfThenFree_0202cd78(void *arg0);
extern void func_0202a1c4(void *block);
extern ScreenState *g_screenState_020b6f64;

void DestroyScreenState_020b6ac4(void)
{
    ScreenState *state;

    state = g_screenState_020b6f64;
    func_ov001_020715ac(state->registration);
    Obj_Release_0204eff8(state->engineObject);
    ZeroHalfThenFree_0202cd78((void *)state->slotA);
    ZeroHalfThenFree_0202cd78((void *)state->slotB);
    if (state->freeFlag != 0) {
        func_0202a1c4((void *)state->freeFlag);
    }
    g_screenState_020b6f64 = (ScreenState *)0;
}
