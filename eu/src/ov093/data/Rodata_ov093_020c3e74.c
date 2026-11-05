#include "nitro/types.h"

extern void ClosePopupPanel(void);
extern void FadeInPopup(void);
extern void FadeOutPopup(void);
extern void OpenPopupWindow_020c3438(void);
extern void StartNextPopup(void);
extern void TrophyPopup_HandleState0Noop(void);
extern void OpenPopupMessage(void);
extern void WaitForPopupDismiss(void);

void *const data_ov093_020c3e74[9] = {
    (void *)TrophyPopup_HandleState0Noop,
    (void *)StartNextPopup,
    (void *)OpenPopupMessage,
    (void *)FadeInPopup,
    (void *)OpenPopupWindow_020c3438,
    (void *)WaitForPopupDismiss,
    (void *)FadeOutPopup,
    (void *)ClosePopupPanel,
    NULL,
};
