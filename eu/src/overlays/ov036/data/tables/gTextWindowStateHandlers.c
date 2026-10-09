#include "nitro/types.h"

extern void func_ov036_020bf6dc(void);
extern void OpenQueuedTextWindow(void);
extern void LoadTextWindowFrame(void); /* LoadTextWindowFrame */
extern void PlaceTextWindowFrame(void);
extern void StepPanelFade(void);
extern void LayoutTextWindow(void);
extern void UpdateTextWindowTyping(void); /* UpdateTextWindowTyping */
extern void func_ov036_020c0e30(void);
extern void AdvanceTextWindowPage(void); /* AdvanceTextWindowPage */
extern void StepPanelFadeOut(void);
extern void CloseTextWindowEntry(void); /* CloseTextWindowEntry */
extern void UpdateTextWindowTail_020c12e8(void);
extern void HandleScrollMenuInput(void);
extern void func_ov036_020c1d48(void);

void (*const gTextWindowStateHandlers[14])(void) = {
    func_ov036_020bf6dc,
    OpenQueuedTextWindow,
    LoadTextWindowFrame, /* LoadTextWindowFrame */
    PlaceTextWindowFrame,
    StepPanelFade,
    LayoutTextWindow,
    UpdateTextWindowTyping, /* UpdateTextWindowTyping */
    func_ov036_020c0e30,
    AdvanceTextWindowPage, /* AdvanceTextWindowPage */
    StepPanelFadeOut,
    CloseTextWindowEntry, /* CloseTextWindowEntry */
    UpdateTextWindowTail_020c12e8,
    HandleScrollMenuInput,
    func_ov036_020c1d48,
};
