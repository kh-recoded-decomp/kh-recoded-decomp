#include "nitro/types.h"

typedef struct {
    u8 pad00[0x3c];
    int active;
    u8 pad40[0x107 - 0x40];
    u8 timer;
} IdleToggleState;

extern BOOL IsFieldFlag13OrSessionFlagSet_020728e4(void);
extern signed char GetCtxModeByte_02068084(void);
extern BOOL func_ov001_020645c8(u32 id);
extern BOOL IsHudFlag7Set_020725bc(void);
extern BOOL IsFieldFlag10Set_020728c4(void);
extern BOOL IsFieldFlag8Set_020728a4(void);
extern BOOL func_ov001_020642a0(void);
extern u32 func_ov001_0207b3cc(void);
extern BOOL func_ov001_0207b338(u32 arg);
extern s32 func_ov001_02063a38(void);

void UpdateIdleTimerToggle_0207aec8(IdleToggleState *state) {
    if (IsFieldFlag13OrSessionFlagSet_020728e4()) {
        return;
    }
    if (GetCtxModeByte_02068084() == 5 && func_ov001_020645c8(0x3520)) {
        return;
    }
    if (IsHudFlag7Set_020725bc() || IsFieldFlag10Set_020728c4() || IsFieldFlag8Set_020728a4()) {
        return;
    }
    if (state->active == 0) {
        state->timer = 0;
    }
    if (state->active == 0 && func_ov001_020642a0()) {
        if (func_ov001_0207b3cc() != 2 && func_ov001_0207b338(2)) {
            state->active = 1;
        }
    } else if (state->active != 0 && !func_ov001_020642a0()) {
        if (state->timer >= 0x3c) {
            func_ov001_0207b338(func_ov001_02063a38() == 10);
            state->active = 0;
        } else {
            state->timer++;
        }
    }
}
