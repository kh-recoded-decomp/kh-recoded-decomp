#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Ov039State {
    u8 pad_0000[0x647c];
    u8 subResources[0xc8f8 - 0x647c];
    u8 mainTracker[0x4c];
    u8 subTracker[0x4c];
    void *heapHandle;
    int mode;
    u8 pad_c998[8];
    u8 tileTable[0x28];
    fx32 brightness;
    fx32 subBrightness;
    u8 brightnessTween[0x1c];
    u8 subBrightnessTween[0x24];
    BOOL secondaryEnabled;
    BOOL inputEnabled;
    BOOL primaryActive;
    BOOL secondaryActive;
    u8 pad_ca20[2];
    u8 layerMask;
    u8 pad_ca23;
    BOOL vblankPending;
    BOOL busyFlag;
    u8 pad_ca2c[0x18];
    u8 startDelay;
    u8 pad_ca45[5];
    u16 inputSource[1];
    u8 pad_ca4c[0x28];
    u8 taskList[0xc];
    u32 entryArg;
    u8 scripts[4][0xc];
    u8 pad_cab4[0x10];
    u8 packedView[0xc];
    BOOL firstVisit;
    u8 pad_cad4[0x18];
} Ov039State;

typedef struct TileTableDesc {
    int *ids;
    int count;
    u16 width;
    u16 height;
    int rowLength;
} TileTableDesc;

typedef struct TrackerConfig {
    int values[5];
} TrackerConfig;

typedef struct InputLimits {
    u16 low;
    u16 high;
} InputLimits;

typedef struct TileIdList {
    int ids[7];
} TileIdList;

extern Ov039State *data_ov039_020bea20;
extern TrackerConfig data_ov039_020be770;
extern InputLimits data_ov039_020be750;
extern TileIdList data_ov039_020be7a0;
extern char sOv039_TextFontEu08Nftr_020be848[];
extern char sOv039_TextFontEu10Nftr_020be860[];
extern char sOv039_TextFontEu08sNftr_020be878[];
extern char sOv039_TextFontEu10sNftr_020be890[];
extern char sOv039_UiMenuStrLanguageShareSZ_020be8a8[];
extern void data_ov027_020ba3a0(void);
extern char OVERLAY_27_ID[];

extern void func_02029f8c(int processor, int overlayId);
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void MI_CpuFill8(void *dst, int value, u32 size);
extern BOOL PlaySoundEffect(int seqArcNo, int index);
extern void LoadSlotImagePair();
extern void *func_0202a45c(void *descriptor, void *userData);
extern void NNS_FndInitList(void *list, int offset);
extern int func_0200146c(void *script, char *path);
extern void func_ov039_020bab30(void);
extern void func_ov039_020bcdd8(void);
extern int *AcquireMapLayout(BOOL reload, BOOL discard);
extern void InitTileTableFrom(void *table, TileTableDesc *source);
extern void func_020524fc(void *tween);
extern void func_ov027_020b7d78(void *tracker, TrackerConfig *config);
extern int InitializeResourceContainer(void *container, void *config);
extern void SetBrightnessAndSyncMain(int value);
extern void SetSecondaryBrightness(int value);
extern void LoadPackedFileView(void *view, char *path, BOOL fromTail);
extern void AcquireRecordManager(void);
extern void AcquireRecordSlot(int slot, int arg);
extern void SetMenuButtonsEnabled(int event);
extern int func_0204f5a0(u16 *record, InputLimits *limits);
extern void SetupMainBgLayers_020be6c0(void);
extern void StartSubScene(int scene, int arg1, int arg2);

void InitOverlayState(u32 entryArg)
{
    TrackerConfig config = data_ov039_020be770;
    InputLimits limits = data_ov039_020be750;
    TileIdList ids = data_ov039_020be7a0;
    TileTableDesc desc;
    int scene;
    Ov039State *state;

    func_02029f8c(0, (int)OVERLAY_27_ID);
    state = NNSi_FndAllocFromDefaultHeap(sizeof(Ov039State));
    data_ov039_020bea20 = state;
    MI_CpuFill8(state, 0, sizeof(Ov039State));
    state->primaryActive = TRUE;
    state->secondaryActive = TRUE;
    state->inputEnabled = TRUE;
    switch ((u16)entryArg) {
    case 0:
        state->mode = 0;
        PlaySoundEffect(0, 2);
        break;
    case 1:
        state->mode = 1;
        PlaySoundEffect(0, 2);
        break;
    case 2:
        state->mode = 2;
        break;
    case 3:
        state->mode = 3;
        break;
    case 4:
        state->mode = 4;
        break;
    case 5:
        state->mode = 5;
        break;
    case 6:
        state->mode = 7;
        break;
    case 7:
        state->mode = 6;
        break;
    case 8:
        state->mode = 8;
        break;
    default:
        state->mode = 0;
        break;
    }
    state->entryArg = entryArg >> 16;
    LoadSlotImagePair(state, 0, -1);
    if (state->mode != 8) {
        LoadSlotImagePair(state, 2, state->mode);
    }
    state->heapHandle = func_0202a45c(data_ov027_020ba3a0, NULL);
    NNS_FndInitList(state->taskList, 4);
    state->brightness = -16 * 0x1000;
    state->subBrightness = -16 * 0x1000;
    state->busyFlag = TRUE;
    state->startDelay = 1;
    func_0200146c(data_ov039_020bea20->scripts[0], sOv039_TextFontEu08Nftr_020be848);
    func_0200146c(data_ov039_020bea20->scripts[1], sOv039_TextFontEu10Nftr_020be860);
    func_0200146c(data_ov039_020bea20->scripts[2], sOv039_TextFontEu08sNftr_020be878);
    func_0200146c(data_ov039_020bea20->scripts[3], sOv039_TextFontEu10sNftr_020be890);
    func_ov039_020bab30();
    func_ov039_020bcdd8();
    AcquireMapLayout(state->mode != 7, FALSE);
    desc.ids = ids.ids;
    desc.count = 7;
    desc.width = 0x20;
    desc.height = 0x20;
    desc.rowLength = 0;
    InitTileTableFrom(state->tileTable, &desc);
    func_020524fc(state->brightnessTween);
    func_020524fc(state->subBrightnessTween);
    func_ov027_020b7d78(state->mainTracker, &config);
    func_ov027_020b7d78(state->subTracker, &config);
    InitializeResourceContainer(state, NULL);
    InitializeResourceContainer(state->subResources, NULL);
    SetBrightnessAndSyncMain(-16);
    SetSecondaryBrightness(-16);
    LoadPackedFileView(state->packedView, sOv039_UiMenuStrLanguageShareSZ_020be8a8, FALSE);
    AcquireRecordManager();
    state->layerMask = 0xf;
    AcquireRecordSlot(1, 0);
    AcquireRecordSlot(0, 0);
    AcquireRecordSlot(2, 0);
    SetMenuButtonsEnabled(0);
    func_0204f5a0(state->inputSource, &limits);
    state->vblankPending = TRUE;
    state->firstVisit = FALSE;
    switch (state->mode) {
    case 0:
        scene = 0;
        break;
    case 1:
        scene = 0;
        break;
    case 2:
        scene = 6;
        break;
    case 3:
        scene = 6;
        break;
    case 5:
        scene = 7;
        break;
    case 6:
        scene = 9;
        break;
    case 8:
        scene = 0x11;
        break;
    case 7:
        scene = 10;
        break;
    }
    if (state->firstVisit == FALSE) {
        state->firstVisit = state->mode == 1;
    }
    SetupMainBgLayers_020be6c0();
    StartSubScene(scene, 100, 1);
}
