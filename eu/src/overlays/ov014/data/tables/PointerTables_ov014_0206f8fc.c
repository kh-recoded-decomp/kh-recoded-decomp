#include "nitro/types.h"

extern void Ov014Panel_LeaveOpenStateNoop(void);
extern void Ov014Panel_EnterEditStateNoop(void);
extern void UpdatePanelEditInput(void);
extern void Ov014Panel_LeaveEditStateNoop(void);
extern void ResetPanelCloseStep(void);
extern void UpdatePanelCloseStep(void); /* UpdatePanelCloseStep */
extern void Ov014Panel_LeaveCloseStateNoop(void);
extern void UpdatePanelOpenStep(void); /* UpdatePanelOpenStep */

void (*gPanelLifecycleHandlers[7])(void) = {
    Ov014Panel_LeaveOpenStateNoop,
    Ov014Panel_EnterEditStateNoop,
    UpdatePanelEditInput,
    Ov014Panel_LeaveEditStateNoop,
    ResetPanelCloseStep,
    UpdatePanelCloseStep, /* UpdatePanelCloseStep */
    Ov014Panel_LeaveCloseStateNoop,
};

void (*gPanelOpenStepHandler[1])(void) = {
    UpdatePanelOpenStep, /* UpdatePanelOpenStep */
};
