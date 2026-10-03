#include "nitro/types.h"

extern void CloseMenuElement5_020651c0(void);
extern void CloseMenuPopup_02065668(void);
extern void OSi_IrqDma3_02065c1c(void);
extern void OSi_IrqDma3_02065c34(void);
extern void OpenMenuPopup_0206574c(void);
extern void OpenMenuSelector_02065244(void);
extern void ReleaseMenuPanelCallback_02065bf4(void);
extern void ResetMenuElement5_02065074(void);
extern void RunMenuIntroStep_02064ff8(void);
extern void UpdateMenuTouchSelect_020650e0(void);
extern void UpdateQuitMenuState_020658c0(void);
extern void UpdateSaveMenuState_02065374(void);
extern void func_ov002_02065070(void);
extern void func_ov002_02065c2c(void);
extern void func_ov002_02065c30(void);
extern void func_ov002_02065c44(void);
extern void func_ov002_02065c48(void);

void (*data_ov002_0206c3d0[16])(void) = {
    func_ov002_02065070,
    ResetMenuElement5_02065074,
    UpdateMenuTouchSelect_020650e0,
    CloseMenuElement5_020651c0,
    OpenMenuSelector_02065244,
    UpdateSaveMenuState_02065374,
    CloseMenuPopup_02065668,
    OpenMenuPopup_0206574c,
    UpdateQuitMenuState_020658c0,
    ReleaseMenuPanelCallback_02065bf4,
    OSi_IrqDma3_02065c1c,
    func_ov002_02065c2c,
    func_ov002_02065c30,
    OSi_IrqDma3_02065c34,
    func_ov002_02065c44,
    func_ov002_02065c48,
};

void (*data_ov002_0206c3cc[1])(void) = {
    RunMenuIntroStep_02064ff8,
};
