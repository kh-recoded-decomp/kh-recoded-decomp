#include "nitro/types.h"

extern BOOL IsModeSetOrFlag370aClear(void);
extern BOOL IsHudFlag7Set(void);
extern BOOL IsFieldFlag10Set(void);
extern void DrawFieldMenuPanel(void *menu, s32 arg);
extern void DrawPartyGaugeFrames(void *menu, s32 arg);

void func_ov001_020761a4(void *menu, s32 arg)
{
    if (!IsModeSetOrFlag370aClear() || IsHudFlag7Set() || IsFieldFlag10Set()) {
        DrawFieldMenuPanel(menu, arg);
    } else {
        DrawPartyGaugeFrames(menu, arg);
    }
}
