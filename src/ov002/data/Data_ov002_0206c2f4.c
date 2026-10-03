#include "nitro/types.h"

extern void ClosePanelAndQueueScene_02062da0(void);
extern void LoadPanelOverlay13_02062e48(void);
extern void LoadPanelOverlay14_02062de0(void);
extern void LoadPanelOverlay15_02062ee0(void);
extern void OSi_IrqDma0_02062ecc(void);
extern void PXI_Init_02062d94(void);
extern void PXI_Init_02064394(void);
extern void PollPanelOverlay13_02062e64(void);
extern void PollPanelOverlay15_02062efc(void);
extern void UnloadPanelOverlay13_02062e98(void);
extern void UnloadPanelOverlay14_02062e18(void);
extern void UnloadPanelOverlay15_02062f30(void);
extern void UpdatePanelBanner_0206cfa0(void);
extern void func_ov002_02062dd8(void);
extern void func_ov002_02062ddc(void);
extern void func_ov002_02062dfc(void);
extern void func_ov002_02062ec8(void);
extern void func_ov002_02062edc(void);
extern void func_ov002_02062f60(void);
extern void func_ov002_02062f80(void);
extern void func_ov002_02062f84(void);
extern void func_ov013_0206c9d4(void);
extern void func_ov015_0206c5dc(void);

void (*data_ov002_0206c2f8[25])(void) = {
    PXI_Init_02064394,
    ClosePanelAndQueueScene_02062da0,
    func_ov002_02062dd8,
    func_ov002_02062ddc,
    NULL,
    LoadPanelOverlay14_02062de0,
    func_ov002_02062dfc,
    UnloadPanelOverlay14_02062e18,
    UpdatePanelBanner_0206cfa0,
    LoadPanelOverlay13_02062e48,
    PollPanelOverlay13_02062e64,
    UnloadPanelOverlay13_02062e98,
    func_ov013_0206c9d4,
    func_ov002_02062f60,
    func_ov002_02062f80,
    func_ov002_02062f84,
    NULL,
    func_ov002_02062ec8,
    OSi_IrqDma0_02062ecc,
    func_ov002_02062edc,
    NULL,
    LoadPanelOverlay15_02062ee0,
    PollPanelOverlay15_02062efc,
    UnloadPanelOverlay15_02062f30,
    func_ov015_0206c5dc,
};

void (*data_ov002_0206c2f4[1])(void) = {
    PXI_Init_02062d94,
};
