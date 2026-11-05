#include "nitro/types.h"

extern void HandleEntryConfirmInput(void);
extern void ShowNextQueuedPopup(void);
extern void ReportTopPopup_HandleState0Noop(void);
extern void OpenPopupWindow_020c1e38(void);
extern void GrowPopupWindow(void);
extern void ShowPopupFrame(void);
extern void ShrinkPopupWindow(void);
extern void HidePopupWindow(void);

void (*const data_ov091_020c2a10[8])(void) = {
    ReportTopPopup_HandleState0Noop,
    ShowNextQueuedPopup,
    OpenPopupWindow_020c1e38,
    GrowPopupWindow,
    ShowPopupFrame,
    HandleEntryConfirmInput,
    ShrinkPopupWindow,
    HidePopupWindow,
};
