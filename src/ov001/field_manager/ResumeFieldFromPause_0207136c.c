#include "nitro/types.h"

typedef struct TickTween {
    u8 data[0x1c];
} TickTween;

typedef struct BgResource {
    u8 pad_00[0x24];
    void *charData;
} BgResource;

typedef struct FieldManager {
    u8 pad_000[0x1c];
    u8 records[0x410];
    void *overlayScreen;
    s32 panelReady;
    u8 pad_434[0x8];
    void *savedBgScreen;
    void *savedBg2Char;
    void *savedBgPalette;
    u8 pad_448[0x34];
    s32 panelState;
    u32 isSliding : 1;
    u32 unk_480_1 : 5;
    u32 use256ColorBg : 1;
    u32 unk_480_7 : 13;
    u32 slotLabelsDirty : 1;
    u32 unk_480_21 : 11;
    u8 pad_484[0xd0];
    TickTween tickerTween;
    u8 pad_570[0x34];
    BgResource *bgResource;
    u8 pad_5a8[0x34];
    TickTween slideTween;
} FieldManager;

typedef struct FieldManagerHandle {
    u32 unk_00;
    FieldManager *manager;
} FieldManagerHandle;

typedef void (*ScreenLoader)(const void *src, u32 offset, u32 size);

typedef struct WidgetLayerIds {
    int ids[7];
} WidgetLayerIds;

typedef struct ScreenLoaders {
    ScreenLoader loaders[7];
} ScreenLoaders;

extern FieldManagerHandle data_ov001_020a04a4;
extern const WidgetLayerIds data_ov001_0209dd00;
extern const ScreenLoaders data_ov001_0209ecf0;

extern BOOL func_ov001_02072040(void);
extern void func_020033e0(void);
extern void func_ov001_0206ec80(void);
extern void SetFieldMenuSuspended_02077b90(int enable, int arg1);
extern void func_ov001_0207b4c0(void);
extern void ConfigureFieldBgLayers_0206e818(void);
extern void *G2_GetBG3ScrPtr_02006f80(void);
extern void *G2_GetBG1ScrPtr_02006e34(void);
extern void MIi_CpuClearFast_01ff8740(u32 value, void *dest, u32 size);
extern void GX_LoadBG3Char_02007b70(const void *src, u32 offset, u32 size);
extern void GX_LoadBG2Char_02007a90(const void *src, u32 offset, u32 size);
extern void GX_LoadBGPltt_02007250(const void *src, u32 offset, u32 size);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *memory);
extern u32 func_ov001_0207b3cc(void);
extern void GXS_LoadBG1Char_02007a20(const void *src, u32 offset, u32 size);
extern void GX_LoadBG1Char_020079b0(const void *src, u32 offset, u32 size);
extern void RegisterEmbeddedObjectIfPending_020c0720(void);
extern void func_ov001_0207b5cc(void);
extern void *UpdateWidgetLayerDefault_020b9df0(FieldManager *manager, int layer);
extern void func_0202d60c(u32 value);
extern void ApplyModeFadeBlend_0207a8c8(void);
extern BOOL func_ov001_0207e108(void);
extern void SetPanelReadyState_02028968(int readyA, int readyB);
extern void setStopwatchHeld_02052648(TickTween *tween, int hold);
extern void RefreshModeWindow_0207a89c(int screen);
extern BOOL func_ov001_020728a4(void);
extern BOOL IsHudFlag9Set_02072884(void);
extern void *FindActiveRecordById_020b8184(void *pool, u32 recordId);
extern void TagTracker_InvokeCallback_020b8210(void *pool, void *record);

void ResumeFieldFromPause_0207136c(void)
{
    int i;
    int layerCount;
    BOOL overridden;
    FieldManager *manager = data_ov001_020a04a4.manager;
    WidgetLayerIds layers = data_ov001_0209dd00;
    ScreenLoaders screens = data_ov001_0209ecf0;
    void *charData = manager->bgResource->charData;

    overridden = func_ov001_02072040();
    func_020033e0();
    if ((manager->panelState == 0 || manager->panelState == 3) && !overridden) {
        func_ov001_0206ec80();
        SetFieldMenuSuspended_02077b90(0, 1);
        func_ov001_0207b4c0();
    } else {
        ConfigureFieldBgLayers_0206e818();
    }
    MIi_CpuClearFast_01ff8740(0, G2_GetBG3ScrPtr_02006f80(), 0x800);
    GX_LoadBG3Char_02007b70(manager->savedBgScreen, 0, 0x5c00);
    GX_LoadBG2Char_02007a90(manager->savedBg2Char, 0, 0x1000);
    GX_LoadBGPltt_02007250(manager->savedBgPalette, 0, 0x200);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(manager->savedBgPalette);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(manager->savedBg2Char);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(manager->savedBgScreen);
    manager->savedBgPalette = NULL;
    manager->savedBg2Char = NULL;
    manager->savedBgScreen = NULL;
    if ((manager->panelState == 0 || manager->panelState == 3) && func_ov001_0207b3cc() == 0) {
        GXS_LoadBG1Char_02007a20(charData, 0x1000, 0x780);
    }
    GX_LoadBG1Char_020079b0(charData, 0x5c00, 0x780);
    if (manager->overlayScreen != NULL && manager->use256ColorBg == 1) {
        RegisterEmbeddedObjectIfPending_020c0720();
        MIi_CpuClearFast_01ff8740(0, G2_GetBG1ScrPtr_02006e34(), 0x800);
    } else {
        if (func_ov001_0207b3cc() == 2) {
            layerCount = 4;
            func_ov001_0207b5cc();
        } else {
            layerCount = 7;
        }
        for (i = 0; i < layerCount; i++) {
            screens.loaders[i](UpdateWidgetLayerDefault_020b9df0(manager, layers.ids[i]), 0, 0x800);
        }
    }
    func_0202d60c(1);
    if (manager->panelState >= 1 && manager->panelState <= 2) {
        ApplyModeFadeBlend_0207a8c8();
    }
    if (manager->panelReady != 0 && func_ov001_0207e108()) {
        SetPanelReadyState_02028968(1, func_ov001_0207b3cc() == 0);
    }
    setStopwatchHeld_02052648(&manager->tickerTween, 0);
    setStopwatchHeld_02052648(&manager->slideTween, 0);
    RefreshModeWindow_0207a89c(0);
    if (func_ov001_020728a4()) {
        if (IsHudFlag9Set_02072884()) {
            manager->slotLabelsDirty = 1;
            return;
        }
        TagTracker_InvokeCallback_020b8210(manager->records, FindActiveRecordById_020b8184(manager->records, 5));
    }
}
