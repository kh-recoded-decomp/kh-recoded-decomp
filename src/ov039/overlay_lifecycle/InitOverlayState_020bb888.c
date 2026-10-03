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

extern Ov039State *data_ov039_020bea00;
extern TrackerConfig data_ov039_020be750;
extern InputLimits data_ov039_020be730;
extern TileIdList data_ov039_020be780;
extern char data_ov039_020be828[];
extern char data_ov039_020be840[];
extern char data_ov039_020be858[];
extern char data_ov039_020be870[];
extern char data_ov039_020be888[];
extern void func_ov027_020ba380(void);
extern char OverlayId27_0000001b[];

extern void func_02029f78(int processor, int overlayId);
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void func_01ff8830(void *dst, int value, u32 size);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);
extern void func_ov039_020bb754();
extern void *func_0202a448(void *descriptor, void *userData);
extern void func_0201288c(void *list, int offset);
extern int func_02001458(void *script, char *path);
extern void SetupOverlayDisplay_020bab10(void);
extern void func_ov039_020bcdb8(void);
extern int *AcquireMapLayout_020506dc(BOOL reload, BOOL discard);
extern void InitTileTableFrom_020b9a0c(void *table, TileTableDesc *source);
extern void func_020524e8(void *tween);
extern void func_ov027_020b7d58(void *tracker, TrackerConfig *config);
extern int InitializeResourceContainer_020b8bd4(void *container, void *config);
extern void SetBrightnessAndSyncMain_02029e7c(int value);
extern void SetSecondaryBrightness_02029ed0(int value);
extern void LoadPackedFileView_020ba25c(void *view, char *path, BOOL fromTail);
extern void AcquireRecordManager_02051c80(void);
extern void AcquireRecordSlot_02051d3c(int slot, int arg);
extern void func_ov039_020bae84(int event);
extern int func_0204f58c(u16 *record, InputLimits *limits);
extern void func_ov039_020be6a0(void);
extern void func_ov039_020bbf78(int scene, int arg1, int arg2);

void InitOverlayState_020bb888(u32 entryArg)
{
    TrackerConfig config = data_ov039_020be750;
    InputLimits limits = data_ov039_020be730;
    TileIdList ids = data_ov039_020be780;
    TileTableDesc desc;
    int scene;
    Ov039State *state;

    func_02029f78(0, (int)OverlayId27_0000001b);
    state = NNSi_FndAllocFromDefaultHeap_0202a178(sizeof(Ov039State));
    data_ov039_020bea00 = state;
    func_01ff8830(state, 0, sizeof(Ov039State));
    state->primaryActive = TRUE;
    state->secondaryActive = TRUE;
    state->inputEnabled = TRUE;
    switch ((u16)entryArg) {
    case 0:
        state->mode = 0;
        PlaySoundEffect_0204d924(0, 2);
        break;
    case 1:
        state->mode = 1;
        PlaySoundEffect_0204d924(0, 2);
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
    func_ov039_020bb754(state, 0, -1);
    if (state->mode != 8) {
        func_ov039_020bb754(state, 2, state->mode);
    }
    state->heapHandle = func_0202a448(func_ov027_020ba380, NULL);
    func_0201288c(state->taskList, 4);
    state->brightness = -16 * 0x1000;
    state->subBrightness = -16 * 0x1000;
    state->busyFlag = TRUE;
    state->startDelay = 1;
    func_02001458(data_ov039_020bea00->scripts[0], data_ov039_020be828);
    func_02001458(data_ov039_020bea00->scripts[1], data_ov039_020be840);
    func_02001458(data_ov039_020bea00->scripts[2], data_ov039_020be858);
    func_02001458(data_ov039_020bea00->scripts[3], data_ov039_020be870);
    SetupOverlayDisplay_020bab10();
    func_ov039_020bcdb8();
    AcquireMapLayout_020506dc(state->mode != 7, FALSE);
    desc.ids = ids.ids;
    desc.count = 7;
    desc.width = 0x20;
    desc.height = 0x20;
    desc.rowLength = 0;
    InitTileTableFrom_020b9a0c(state->tileTable, &desc);
    func_020524e8(state->brightnessTween);
    func_020524e8(state->subBrightnessTween);
    func_ov027_020b7d58(state->mainTracker, &config);
    func_ov027_020b7d58(state->subTracker, &config);
    InitializeResourceContainer_020b8bd4(state, NULL);
    InitializeResourceContainer_020b8bd4(state->subResources, NULL);
    SetBrightnessAndSyncMain_02029e7c(-16);
    SetSecondaryBrightness_02029ed0(-16);
    LoadPackedFileView_020ba25c(state->packedView, data_ov039_020be888, FALSE);
    AcquireRecordManager_02051c80();
    state->layerMask = 0xf;
    AcquireRecordSlot_02051d3c(1, 0);
    AcquireRecordSlot_02051d3c(0, 0);
    AcquireRecordSlot_02051d3c(2, 0);
    func_ov039_020bae84(0);
    func_0204f58c(state->inputSource, &limits);
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
    func_ov039_020be6a0();
    func_ov039_020bbf78(scene, 100, 1);
}




