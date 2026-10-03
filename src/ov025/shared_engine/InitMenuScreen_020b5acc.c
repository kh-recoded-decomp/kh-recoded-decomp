#include "nitro/types.h"

typedef char *(*PathResolver)(int resourceId);

typedef struct ListViewConfig {
    PathResolver resolvePath;
    void (*onChange)(void);
    u32 data;
    BOOL asyncLoad;
    u32 field;
    u8 mode;
    u32 cellSet;
    int *highlightCell;
    int *cursorCell;
    int maxSlots;
    int normalSequence;
    int highlightSequence;
} ListViewConfig;

typedef struct ObjManagerConfig {
    u32 vramKey;
    u32 params[3];
} ObjManagerConfig;

typedef struct LayerParams {
    u32 values[2];
} LayerParams;

typedef struct LayerConfig {
    LayerParams *params;
    u32 values[3];
} LayerConfig;

extern ListViewConfig data_ov025_020b76d4;
extern ObjManagerConfig data_ov025_020b76a0;
extern LayerParams data_ov025_020b7688;
extern LayerConfig data_ov025_020b7690;
extern u32 g_uiContext_020b7760;

extern void *NNSi_FndGetCurrentRootHeap_0202a764(void);
extern u32 func_ov001_0207b200(void (*callback)(void));
extern void SetupSubBgLayers_020b5a0c(void);
extern void func_ov027_020b9a0c(u32 layers, LayerConfig *config);
extern int InitializeResourceContainer_020b8bd4(u32 container, int *extra);
extern unsigned int MakePrimaryVramKey_020711ec(unsigned int slot);
extern unsigned int MakePrimaryVramKey_02071214(unsigned int slot);
extern void InitObjManagerAndMark_020b9060(u32 obj, ObjManagerConfig *config);
extern void PXI_Init_020b9078(u32 obj, unsigned int key);
extern void func_ov027_020b8f98(u32 obj, unsigned int key, int count);
extern u32 func_ov001_02073060(void);
extern u32 UpdateWidgetLayerDefault_020b9df0(u32 owner, int layerId);
extern u8 func_ov001_0207b62c(void);
extern int *func_ov027_020b90a4(u32 obj, int id);
extern s32 GetClampedPaletteSlot_02073598(void);
extern void SetEntrySlotsVisible_020b9580(u32 obj, int *entry, int visible);
extern void InitSlotListView_020b7068(u32 list, ListViewConfig *config);
extern void *func_0202c48c(unsigned int key, u32 heapId);
extern void LoadSubBgGraphics_020b5908(u32 screen, void *archive);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern void AdvanceMenuDelayCounter_020b582c(u32 menu);
extern void *QueueFileLoadRequest_020ba114(unsigned int key, int loadMode, void *callback, void *userData);
extern void LoadMenuWidgetResource_020b5954(unsigned int resource);
extern u32 func_ov025_020b5c78(void);

void *InitMenuScreen_020b5acc(BOOL loadImmediately)
{
    ListViewConfig config = data_ov025_020b76d4;
    ObjManagerConfig objConfig = data_ov025_020b76a0;
    LayerParams layerParams = data_ov025_020b7688;
    LayerConfig layerConfig = data_ov025_020b7690;
    u32 menu;
    void *archive;

    menu = (u32)NNSi_FndGetCurrentRootHeap_0202a764();
    g_uiContext_020b7760 = menu;
    *(int *)(menu + 0x66d0) = -1;
    if (loadImmediately) {
        *(u8 *)(menu + 0x64e9) = 1;
    }
    func_ov001_0207b200(SetupSubBgLayers_020b5a0c);
    SetupSubBgLayers_020b5a0c();
    layerConfig.params = &layerParams;
    func_ov027_020b9a0c(menu + 0x64c8, &layerConfig);
    *(int *)(menu + 0x64e4) = 1;
    InitializeResourceContainer_020b8bd4(menu + 0x4c, NULL);
    objConfig.vramKey = MakePrimaryVramKey_020711ec(0x69);
    InitObjManagerAndMark_020b9060(menu + 0x4c, &objConfig);
    PXI_Init_020b9078(menu + 0x4c, MakePrimaryVramKey_02071214(0xc));
    func_ov027_020b8f98(menu + 0x4c, MakePrimaryVramKey_020711ec(0x6b), 3);
    config.data = func_ov001_02073060();
    config.field = UpdateWidgetLayerDefault_020b9df0(menu + 0x64c8, 0x1a);
    config.cellSet = menu + 0x4c;
    config.mode = func_ov001_0207b62c();
    config.highlightCell = func_ov027_020b90a4(menu + 0x4c, 0x15);
    config.cursorCell = func_ov027_020b90a4(menu + 0x4c, 0x16);
    config.maxSlots = GetClampedPaletteSlot_02073598();
    config.normalSequence = 2;
    config.highlightSequence = 3;
    if (*(u8 *)(menu + 0x64e9) != 0) {
        config.asyncLoad = FALSE;
        SetEntrySlotsVisible_020b9580(menu + 0x4c, config.highlightCell, TRUE);
    } else {
        SetEntrySlotsVisible_020b9580(menu + 0x4c, config.highlightCell, FALSE);
    }
    SetEntrySlotsVisible_020b9580(menu + 0x4c, func_ov027_020b90a4(menu + 0x4c, 3), FALSE);
    InitSlotListView_020b7068(menu + 0x64f4, &config);
    if (*(u8 *)(menu + 0x64e9) != 0) {
        archive = func_0202c48c(MakePrimaryVramKey_02071214(0xb), 14);
        LoadSubBgGraphics_020b5908(menu, archive);
        NNSi_FndFreeFromDefaultHeap_0202a1c4(archive);
        AdvanceMenuDelayCounter_020b582c(menu);
    } else {
        QueueFileLoadRequest_020ba114(MakePrimaryVramKey_02071214(0xb), 1, LoadMenuWidgetResource_020b5954, NULL);
    }
    return func_ov025_020b5c78;
}
