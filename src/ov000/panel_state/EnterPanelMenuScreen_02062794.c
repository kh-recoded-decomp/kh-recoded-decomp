#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x58];
    u32 unk_58;
    u8 pad_5c[0x224 - 0x5c];
    u8 layerManager[0x6434];
    BOOL layersReady;
    int layerIds[4];
    int overlayLayerId;
    u8 pad_6670[0x66d0 - 0x6670];
    u64 startTick;
} Panel;

extern void InitPanelLayers_0206183c(Panel *panel);
extern void InitPanelScene_02061614(Panel *panel);
extern BOOL IsPanelFlagSet_02061bb0(Panel *panel, int bit);
extern void func_0204f378(void *manager, int layerId, int flag);
extern void ShowPanelBgScreen_02061a80(Panel *panel, int screenIndex);
extern BOOL IsSoundStreamActive_0204ded4(int handleIndex);
extern BOOL func_0204dd4c(int handleIndex, u16 streamId);
extern u64 OS_GetTick_02003fd4(void);

void EnterPanelMenuScreen_02062794(Panel *panel)
{
    int i;

    InitPanelLayers_0206183c(panel);
    InitPanelScene_02061614(panel);
    for (i = 0; i < 4; i++) {
        func_0204f378(panel->layerManager, panel->layerIds[i], IsPanelFlagSet_02061bb0(panel, i));
    }
    func_0204f378(panel->layerManager, panel->overlayLayerId, 1);
    ShowPanelBgScreen_02061a80(panel, 4);
    if (!IsSoundStreamActive_0204ded4(0)) {
        func_0204dd4c(0, 0);
    }
    panel->unk_58 = 0;
    panel->startTick = OS_GetTick_02003fd4();
}
