#include "nitro/types.h"

extern void AnimateOv002MenuBackgroundWrapper(void); /* PXI_Init */
extern void ClosePanelAndQueueScene(void); /* ClosePanelAndQueueScene */
extern void Ov002Panel_UpdateMode1Noop(void);
extern void Ov002Panel_LeaveMode1Noop(void);
extern void LoadPanelOverlay14(void);
extern void UpdateOv002ChildPanel(void);
extern void UnloadPanelOverlay14(void);
extern void UpdatePanelBanner(void); /* UpdatePanelBanner */
extern void LoadPanelOverlay13(void);
extern void PollPanelOverlay13(void); /* PollPanelOverlay13 */
extern void UnloadPanelOverlay13(void);
extern void DispatchOv013PendingPanelActions(void);
extern void SetPanelStateFlag0(void);
extern void Ov002Panel_UpdateMode4Noop(void);
extern void Ov002Panel_LeaveMode4Noop(void);
extern void Ov002Panel_EnterMode5Noop(void);
extern void SwitchOv002PanelToMode0(void); /* OSi_IrqDma0 */
extern void Ov002Panel_LeaveMode5Noop(void);
extern void LoadPanelOverlay15(void);
extern void PollPanelOverlay15(void); /* PollPanelOverlay15 */
extern void UnloadPanelOverlay15(void);
extern void UpdateWirelessMenuDisplayEffects(void);
extern void ReleaseOv002ContextResourcesWrapper(void); /* PXI_Init */

void (*gPanelSceneStateHandlers[25])(void) = {
    AnimateOv002MenuBackgroundWrapper, /* PXI_Init */
    ClosePanelAndQueueScene, /* ClosePanelAndQueueScene */
    Ov002Panel_UpdateMode1Noop,
    Ov002Panel_LeaveMode1Noop,
    NULL,
    LoadPanelOverlay14,
    UpdateOv002ChildPanel,
    UnloadPanelOverlay14,
    UpdatePanelBanner, /* UpdatePanelBanner */
    LoadPanelOverlay13,
    PollPanelOverlay13, /* PollPanelOverlay13 */
    UnloadPanelOverlay13,
    DispatchOv013PendingPanelActions,
    SetPanelStateFlag0,
    Ov002Panel_UpdateMode4Noop,
    Ov002Panel_LeaveMode4Noop,
    NULL,
    Ov002Panel_EnterMode5Noop,
    SwitchOv002PanelToMode0, /* OSi_IrqDma0 */
    Ov002Panel_LeaveMode5Noop,
    NULL,
    LoadPanelOverlay15,
    PollPanelOverlay15, /* PollPanelOverlay15 */
    UnloadPanelOverlay15,
    UpdateWirelessMenuDisplayEffects,
};

void (*gPanelSceneInitialHandler[1])(void) = {
    ReleaseOv002ContextResourcesWrapper, /* PXI_Init */
};
