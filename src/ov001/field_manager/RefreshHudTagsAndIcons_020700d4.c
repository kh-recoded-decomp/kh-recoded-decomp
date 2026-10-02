#include "nitro/types.h"

typedef struct HudScreen {
    u8 pad_000[0x1c];
    u8 tracker[0x60c - 0x1c];
    int slotIcons[2];
} HudScreen;

extern BOOL func_ov001_020645c8(u32 value);
extern int func_ov001_02064784(void);
extern signed char GetCtxModeByte_02068084(void);
extern void LoadSlotIconGraphics_0207001c(int slot, int iconId);
extern BOOL IsHudFlag7Set_020725bc(void);
extern BOOL IsHudFlag9Set_02072884(void);
extern BOOL IsFieldFlag8Set_020728a4(void);
extern BOOL IsFieldFlag10Set_020728c4(void);
extern void *FindActiveRecordById_020b8184(void *pool, u32 recordId);
extern void TagTracker_InvokeCallback_020b8210(void *tracker, void *record);

void RefreshHudTagsAndIcons_020700d4(HudScreen *hud)
{
    int i;

    TagTracker_InvokeCallback_020b8210(hud->tracker, FindActiveRecordById_020b8184(hud->tracker, 0x32));
    if (GetCtxModeByte_02068084() == 0 && func_ov001_020645c8(0x3520)) {
        return;
    }
    TagTracker_InvokeCallback_020b8210(hud->tracker, FindActiveRecordById_020b8184(hud->tracker, 7));
    TagTracker_InvokeCallback_020b8210(hud->tracker, FindActiveRecordById_020b8184(hud->tracker, 0));
    if (!IsHudFlag7Set_020725bc() && !IsFieldFlag10Set_020728c4() && !IsFieldFlag8Set_020728a4()
        && !IsHudFlag9Set_02072884() && (func_ov001_02064784() || !func_ov001_020645c8(0x3708))) {
        TagTracker_InvokeCallback_020b8210(hud->tracker, FindActiveRecordById_020b8184(hud->tracker, 10));
        TagTracker_InvokeCallback_020b8210(hud->tracker, FindActiveRecordById_020b8184(hud->tracker, 11));
    }
    for (i = 0; i < 2; i++) {
        if (hud->slotIcons[i] == -1) {
            return;
        }
        LoadSlotIconGraphics_0207001c(i, hud->slotIcons[i]);
    }
}
