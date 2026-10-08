#include "nitro/types.h"

extern void ClosePopupPanel(void);
extern void FadeInPopup(void);
extern void FadeOutPopup(void);
extern void OpenPopupWindow_020c3438(void);
extern void StartNextPopup(void);
extern void func_ov093_020c31f4(void);
extern void OpenPopupMessage(void);
extern void func_ov093_020c34c4(void);

void *const data_ov093_020c3e74[9] = {
    (void *)func_ov093_020c31f4,
    (void *)StartNextPopup,
    (void *)OpenPopupMessage,
    (void *)FadeInPopup,
    (void *)OpenPopupWindow_020c3438,
    (void *)func_ov093_020c34c4,
    (void *)FadeOutPopup,
    (void *)ClosePopupPanel,
    NULL,
};
