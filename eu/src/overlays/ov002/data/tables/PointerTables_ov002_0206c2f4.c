#include "nitro/types.h"

extern void AnimateOv002MenuBackgroundWrapper(void); /* PXI_Init */
extern void ClosePanelAndQueueScene(void); /* ClosePanelAndQueueScene */
extern void func_ov002_02062dd8(void);
extern void func_ov002_02062ddc(void);
extern void LoadPanelOverlay14(void);
extern void UpdateOv002ChildPanel(void);
extern void UnloadPanelOverlay14(void);
extern void UpdatePanelBanner(void); /* UpdatePanelBanner */
extern void LoadPanelOverlay13(void);
extern void PollPanelOverlay13(void); /* PollPanelOverlay13 */
extern void UnloadPanelOverlay13(void);
extern void DispatchOv013PendingPanelActions(void);
extern void SetPanelStateFlag0(void);
extern void func_ov002_02062f80(void);
extern void func_ov002_02062f84(void);
extern void func_ov002_02062ec8(void);
extern void SwitchOv002PanelToMode0(void); /* OSi_IrqDma0 */
extern void func_ov002_02062edc(void);
extern void LoadPanelOverlay15(void);
extern void PollPanelOverlay15(void); /* PollPanelOverlay15 */
extern void UnloadPanelOverlay15(void);
extern void func_ov015_0206c5dc(void);
extern void ReleaseOv002ContextResourcesWrapper(void); /* PXI_Init */

void (*gPanelSceneStateHandlers[25])(void) = {
    AnimateOv002MenuBackgroundWrapper, /* PXI_Init */
    ClosePanelAndQueueScene, /* ClosePanelAndQueueScene */
    func_ov002_02062dd8,
    func_ov002_02062ddc,
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
    func_ov002_02062f80,
    func_ov002_02062f84,
    NULL,
    func_ov002_02062ec8,
    SwitchOv002PanelToMode0, /* OSi_IrqDma0 */
    func_ov002_02062edc,
    NULL,
    LoadPanelOverlay15,
    PollPanelOverlay15, /* PollPanelOverlay15 */
    UnloadPanelOverlay15,
    func_ov015_0206c5dc,
};

void (*gPanelSceneInitialHandler[1])(void) = {
    ReleaseOv002ContextResourcesWrapper, /* PXI_Init */
};
