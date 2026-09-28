#include "nitro/types.h"

typedef struct TitlePackagePaths {
    char title[0xc];
    char titleLocalized[0x10];
    char movie[0xc];
} TitlePackagePaths;

typedef struct Panel {
    u32 titlePackage;
    u32 titleLocalizedPackage;
    u8 statusRecord[0x1c];
    u8 pad_24[0x668c - 0x24];
    u32 moviePackage;
    u8 pad_6690[0x66e8 - 0x6690];
    s32 loadError;
} Panel;

typedef void (*PanelUpdateFunc)(void);

extern TitlePackagePaths data_ov000_0206397c;

extern Panel *NNSi_FndGetCurrentRootHeap_0202a764(void);
extern u32 func_0202cc6c(const char *path, u32 heapId, u32 flags);
extern void func_0202a794(int value);
extern void func_0204f718(void);
extern int func_0204f58c(void *record, void *limits);
extern void SetupDisplayBanksAndLayers_0206141c(Panel *panel);
extern void func_ov000_020616dc(Panel *panel);
extern void SetParamHalf18_02050630(u16 value);
extern void SetParamWord20_02050640(u32 value);
extern void SelectLocalizedTextIds_02028e04(void);
extern int func_02026dc0(void);
extern void SetPanelState_02061db0(Panel *panel, s32 state, u32 param1, u32 param2);
extern void EnterPanelPhase_02062270(Panel *panel, s32 phase, u32 phaseArg, int brightness);
extern void func_ov000_02063424(void);

PanelUpdateFunc InitTitleScreen_02063240(s32 startMode)
{
    Panel *panel = NNSi_FndGetCurrentRootHeap_0202a764();

    panel->titlePackage = func_0202cc6c(data_ov000_0206397c.title, 0xe, 0);
    panel->titleLocalizedPackage = func_0202cc6c(data_ov000_0206397c.titleLocalized, 0xe, 0);
    panel->moviePackage = func_0202cc6c(data_ov000_0206397c.movie, 0xd, 0);
    func_0202a794(0);
    func_0204f718();
    func_0204f58c(panel->statusRecord, NULL);
    SetupDisplayBanksAndLayers_0206141c(panel);
    func_ov000_020616dc(panel);
    SetParamHalf18_02050630(0);
    SetParamWord20_02050640(0);
    SelectLocalizedTextIds_02028e04();
    if (startMode == -2) {
        switch (func_02026dc0()) {
        case 3:
            panel->loadError = 1;
            EnterPanelPhase_02062270(panel, 0xe, 3, 0);
            break;
        case 5:
            EnterPanelPhase_02062270(panel, 0xd, 3, 0);
            break;
        default:
            SetPanelState_02061db0(panel, 0, 0, 0);
            EnterPanelPhase_02062270(panel, 5, 3, 0x10);
            break;
        }
    } else if (startMode != 0) {
        panel->loadError = startMode;
        EnterPanelPhase_02062270(panel, 0xe, 3, 0);
    } else {
        switch (func_02026dc0()) {
        case 3:
            panel->loadError = 1;
            EnterPanelPhase_02062270(panel, 0xe, 3, 0);
            break;
        case 5:
            EnterPanelPhase_02062270(panel, 0xd, 3, 0);
            break;
        default:
            SetPanelState_02061db0(panel, 0, 0, 0x1e);
            EnterPanelPhase_02062270(panel, 0, 2, 0x10);
            break;
        }
    }
    return func_ov000_02063424;
}
