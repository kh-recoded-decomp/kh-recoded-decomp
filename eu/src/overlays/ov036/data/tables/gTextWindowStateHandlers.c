#include "nitro/types.h"

extern void TextWindowState_IdleNoOp(void);
extern void OpenQueuedTextWindow(void);
extern void LoadTextWindowFrame(void); /* LoadTextWindowFrame */
extern void PlaceTextWindowFrame(void);
extern void StepPanelFade(void);
extern void LayoutTextWindow(void);
extern void UpdateTextWindowTyping(void); /* UpdateTextWindowTyping */
extern void TextWindowState_WaitPageAdvanceNoOp(void);
extern void AdvanceTextWindowPage(void); /* AdvanceTextWindowPage */
extern void StepPanelFadeOut(void);
extern void CloseTextWindowEntry(void); /* CloseTextWindowEntry */
extern void UpdateTextWindowTail_020c12e8(void);
extern void HandleScrollMenuInput(void);
extern void TextWindowState_WaitPrimaryFadeOut(void);

void (*const gTextWindowStateHandlers[14])(void) = {
    TextWindowState_IdleNoOp,
    OpenQueuedTextWindow,
    LoadTextWindowFrame, /* LoadTextWindowFrame */
    PlaceTextWindowFrame,
    StepPanelFade,
    LayoutTextWindow,
    UpdateTextWindowTyping, /* UpdateTextWindowTyping */
    TextWindowState_WaitPageAdvanceNoOp,
    AdvanceTextWindowPage, /* AdvanceTextWindowPage */
    StepPanelFadeOut,
    CloseTextWindowEntry, /* CloseTextWindowEntry */
    UpdateTextWindowTail_020c12e8,
    HandleScrollMenuInput,
    TextWindowState_WaitPrimaryFadeOut,
};
