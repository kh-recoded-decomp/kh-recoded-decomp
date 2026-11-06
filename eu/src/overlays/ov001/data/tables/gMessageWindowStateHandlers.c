#include "nitro/types.h"

extern void UpdateTweenedMessageWindow(void);
extern void UpdateMessageWindow(void); /* UpdateMessageWindow */
extern void CheckTimerExpired(void); /* CheckTimerExpired */
extern void MessageWindow_WaitForInputNoop(void); /* _fp_init */
extern void UpdateModeWidget(void); /* UpdateModeWidget */

void (*gMessageWindowStateHandlers[8])(void) = {
    NULL,
    NULL,
    NULL,
    UpdateTweenedMessageWindow,
    UpdateMessageWindow, /* UpdateMessageWindow */
    CheckTimerExpired, /* CheckTimerExpired */
    MessageWindow_WaitForInputNoop, /* _fp_init */
    UpdateModeWidget, /* UpdateModeWidget */
};
