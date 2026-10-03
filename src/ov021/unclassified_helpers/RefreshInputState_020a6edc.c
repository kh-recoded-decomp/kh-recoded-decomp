#include "nitro/types.h"

typedef struct {
    u8 pad_00[4];
    u16 status;
    u8 pending;
    u8 pad_07;
    u32 flags;
    u16 pressed;
    u16 held;
    u16 repeat;
    u8 pad_12[5];
    u8 locked;
    u8 lockTimer;
} InputState;

extern u16 data_020604fc;
extern u16 data_02060500;
extern u32 func_ov021_020af3e8(void);
extern BOOL Camera_IsFlag3JustSet_020c298c(void);
extern int QuerySubModeStatus_020af3f4(void);

void RefreshInputState_020a6edc(InputState *state)
{
    BOOL query = TRUE;

    state->held = data_020604fc;
    state->pressed = data_02060500;
    state->repeat = 0;
    state->flags &= ~1;
    state->pending = 0;
    if (func_ov021_020af3e8() == 0) {
        if (state->locked) {
            query = FALSE;
        } else if (Camera_IsFlag3JustSet_020c298c()) {
            query = FALSE;
            state->locked = 1;
            state->lockTimer = 0;
        }
    }
    if (query) {
        state->status = QuerySubModeStatus_020af3f4();
    }
}
