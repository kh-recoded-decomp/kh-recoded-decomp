#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x06];
    u16 flags;
    u8 pad_08[0x34];
    s8 mode;
} OverlayState;

extern OverlayState *g_activeState_020bc800;
extern void SetFieldEntriesPaused_0206e444(BOOL paused);
extern void PlaySoundChecked_0204d8d0(void *ptr, int arg);
extern BOOL IsEntryFlag2Active_020642d0(int index);
extern void func_0204d7f4(int value);
extern u32 func_ov001_0206e644(void);

s32 SelectNextState_020ba7f8(void)
{
    OverlayState *state = g_activeState_020bc800;

    if (state->flags & 0x4000) {
        SetFieldEntriesPaused_0206e444(TRUE);
        g_activeState_020bc800->flags |= 0x8000;
        return 14;
    }
    if (state->flags & 0x12) {
        return -1;
    }
    if (state->flags & 0x40) {
        PlaySoundChecked_0204d8d0(NULL, 0x4e);
        g_activeState_020bc800->flags |= 0x8000;
        return 13;
    }
    if (state->mode >= 0) {
        return 9;
    }
    if (IsEntryFlag2Active_020642d0(0)) {
        g_activeState_020bc800->flags |= 0x10;
        func_0204d7f4(0x20);
        return 11;
    }
    if (func_ov001_0206e644()) {
        SetFieldEntriesPaused_0206e444(TRUE);
        return 8;
    }
    return -1;
}



