#include "nitro/types.h"

extern void func_ov002_02064394(void); /* PXI_Init */
extern void ClosePanelAndQueueScene(void); /* ClosePanelAndQueueScene */
extern void func_ov002_02062dd8(void);
extern void func_ov002_02062ddc(void);
extern void LoadPanelOverlay14(void);
extern void func_ov002_02062dfc(void);
extern void UnloadPanelOverlay14(void);
extern void UpdatePanelBanner(void); /* UpdatePanelBanner */
extern void LoadPanelOverlay13(void);
extern void PollPanelOverlay13(void); /* PollPanelOverlay13 */
extern void UnloadPanelOverlay13(void);
extern void func_ov013_0206c9d4(void);
extern void func_ov002_02062f60(void);
extern void func_ov002_02062f80(void);
extern void func_ov002_02062f84(void);
extern void func_ov002_02062ec8(void);
extern void func_ov002_02062ecc(void); /* OSi_IrqDma0 */
extern void func_ov002_02062edc(void);
extern void LoadPanelOverlay15(void);
extern void PollPanelOverlay15(void); /* PollPanelOverlay15 */
extern void UnloadPanelOverlay15(void);
extern void func_ov015_0206c5dc(void);
extern void func_ov002_02062d94(void); /* PXI_Init */

void (*gPanelSceneStateHandlers[25])(void) = {
    func_ov002_02064394, /* PXI_Init */
    ClosePanelAndQueueScene, /* ClosePanelAndQueueScene */
    func_ov002_02062dd8,
    func_ov002_02062ddc,
    NULL,
    LoadPanelOverlay14,
    func_ov002_02062dfc,
    UnloadPanelOverlay14,
    UpdatePanelBanner, /* UpdatePanelBanner */
    LoadPanelOverlay13,
    PollPanelOverlay13, /* PollPanelOverlay13 */
    UnloadPanelOverlay13,
    func_ov013_0206c9d4,
    func_ov002_02062f60,
    func_ov002_02062f80,
    func_ov002_02062f84,
    NULL,
    func_ov002_02062ec8,
    func_ov002_02062ecc, /* OSi_IrqDma0 */
    func_ov002_02062edc,
    NULL,
    LoadPanelOverlay15,
    PollPanelOverlay15, /* PollPanelOverlay15 */
    UnloadPanelOverlay15,
    func_ov015_0206c5dc,
};

void (*gPanelSceneInitialHandler[1])(void) = {
    func_ov002_02062d94, /* PXI_Init */
};
