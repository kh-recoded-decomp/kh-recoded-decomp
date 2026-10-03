#include "nitro/types.h"

extern void HandleEntryConfirmInput_020c2064(void);
extern void ShowNextQueuedPopup_020c1da4(void);
extern void func_ov091_020c1da0(void);
extern void func_ov091_020c1e18(void);
extern void func_ov091_020c1f38(void);
extern void func_ov091_020c1fe4(void);
extern void func_ov091_020c20dc(void);
extern void func_ov091_020c218c(void);

void (*const data_ov091_020c29f0[8])(void) = {
    func_ov091_020c1da0,
    ShowNextQueuedPopup_020c1da4,
    func_ov091_020c1e18,
    func_ov091_020c1f38,
    func_ov091_020c1fe4,
    HandleEntryConfirmInput_020c2064,
    func_ov091_020c20dc,
    func_ov091_020c218c,
};
