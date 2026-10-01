#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x8];
    u16 inputState;
    u8 pad_0a[0x58 - 0xa];
    BOOL inputEnabled;
    u8 pad_5c[0x19c - 0x5c];
    BOOL active;
    u8 pad_1a0[0x66d0 - 0x1a0];
    u64 startTick;
} Panel;

extern u16 data_020604fc;
extern int FS_UnloadOverlayImage_0204f5dc(void *input);
extern u32 func_0204f5ec(void *input);
extern s32 func_ov000_02061de8(Panel *panel, u32 buttons);
extern void HighlightPanelCursorLayer_02061d04(Panel *panel);
extern u64 OS_GetTick_02003fd4(void);
extern void SetPanelState_02061db0(Panel *panel, s32 state, u32 param1, u32 param2);
extern void StopSoundStreamAtIndex_0204deb0(int handleIndex, int fadeFrame);

s32 UpdatePanelInputWithTimeout_02062838(Panel *panel)
{
    s32 result = -1;

    FS_UnloadOverlayImage_0204f5dc(&panel->inputState);
    if (panel->inputEnabled) {
        result = func_ov000_02061de8(panel, func_0204f5ec(&panel->inputState));
    }
    if (!panel->active) {
        return result;
    }
    if (data_020604fc == 0) {
        panel->inputEnabled = TRUE;
    }
    HighlightPanelCursorLayer_02061d04(panel);
    /* Idle timeout of 105 seconds */
    if (result == -1 && OS_GetTick_02003fd4() >= panel->startTick + 0x346fce2) {
        SetPanelState_02061db0(panel, 1, 0x1e, 0);
        StopSoundStreamAtIndex_0204deb0(0, 0x1e);
        result = 0xc;
    }
    return result;
}
