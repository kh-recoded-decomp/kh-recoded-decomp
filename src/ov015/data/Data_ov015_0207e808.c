#include "nitro/types.h"

extern void DispatchPanelTransition_02072fb4(void);
extern void HandleConnectTransition_02073150(void);
extern void HandleMatchTransition_02073034(void);
extern void PXI_Init_02072fa8(void);
extern void UpdateWirelessParentState_020730ac(void);
extern void func_ov015_02072f7c(void);
extern void func_ov015_02072f98(void);
extern void func_ov015_02072f9c(void);
extern void func_ov015_02072fa0(void);
extern void func_ov015_02072fa4(void);
extern void func_ov015_02073018(void);
extern void func_ov015_02073030(void);
extern void func_ov015_020730a4(void);
extern void func_ov015_020730a8(void);
extern void func_ov015_02073148(void);
extern void func_ov015_0207314c(void);
extern void func_ov015_020731b8(void);
extern void func_ov015_020731bc(void);
extern void func_ov015_020731d4(void);
extern void func_ov015_0207321c(void);
extern void func_ov015_02073220(void);
extern void func_ov015_02073238(void);
extern void func_ov015_02073280(void);

void (*data_ov015_0207e80c[22])(void) = {
    func_ov015_02072f98,
    func_ov015_02072f9c,
    func_ov015_02072fa0,
    func_ov015_02072fa4,
    PXI_Init_02072fa8,
    DispatchPanelTransition_02072fb4,
    func_ov015_02073018,
    func_ov015_02073030,
    HandleMatchTransition_02073034,
    func_ov015_020730a4,
    func_ov015_020730a8,
    UpdateWirelessParentState_020730ac,
    func_ov015_02073148,
    func_ov015_0207314c,
    HandleConnectTransition_02073150,
    func_ov015_020731b8,
    func_ov015_020731bc,
    func_ov015_020731d4,
    func_ov015_0207321c,
    func_ov015_02073220,
    func_ov015_02073238,
    func_ov015_02073280,
};

void (*data_ov015_0207e808[1])(void) = {
    func_ov015_02072f7c,
};
