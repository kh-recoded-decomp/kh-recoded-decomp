#include "nitro/types.h"
#include "src/overlays/ov001/SessionBuffers.h"

typedef struct Words4 {
    u32 words[4];
} Words4;

typedef struct Words5 {
    u32 words[5];
} Words5;

typedef struct BgLayerDesc {
    Words4 *layout;
    int count;
    u16 width;
    u16 height;
    int flags;
} BgLayerDesc;

typedef struct BoardState {
    int resourceA;
    int resourceB;
    void *widget;
    char widgetData[0x28 - 0xc];
    char animSet[0x74 - 0x28];
    char objectSet[0x64f8 - 0x74];
    int active;
    char pad64fc[0x655c - 0x64fc];
    int markerSlots[4];
    int cellIds[0x12];
    int itemSlots[30];
    int cursorSlot;
    int targetSlot;
    int nodeIds[0x28];
    int pad66d4;
    int hintSlot;
    int goalSlot;
    int useChannel;
    char pad66e4[0x66ec - 0x66e4];
    int showTutorial;
} BoardState;

typedef struct BoardGlobals {
    BoardState *state;
    int unk04;
    void *cursor;
} BoardGlobals;

#define BOARD_VRAM_KEY(base) ((((base) + 0x8000) & 0xfffffc) << 7)

extern Words4 gBoardBgLayerIds;
extern Words4 gBoardObjectManagerConfig;
extern Words5 gBoardBackgroundContainerConfig;
extern BoardGlobals gBoardScreenGlobals;
extern int gBoardNodeGraphicsBufferStorage[6];
extern char sOv024_UiBtlBtluiP2_020b74f4[];
extern char sOv024_UiBtlBtlLanguageP2_020b7508[];

extern BoardState *GetRunningTaskWork(void);
extern void MI_CpuFill8(void *dest, int value, int size);
extern void MIi_CpuClear32(int value, void *dest, int size);
extern BOOL IsSessionFlagSet(int flag);
extern BOOL IsFieldFlag13OrSessionFlagSet(void);
extern void SetSubsceneBgSetupCallback(void (*callback)(void));
extern void SetupSubScreenBgLayers(void);
extern void SetPanelSessionActive(void);
extern void *GetFieldSceneManager(void);
extern void InitTileTableFrom(void *widget, BgLayerDesc *desc);
extern int Msg_OpenContainerAndReadHeader(const char *path, int heap, int flags);
extern void InitBackgroundContainer(void *animSet, Words5 *desc);
extern void LoadTagTrackerResourceFile(void *animSet, u32 key);
extern void InitializeResourceContainer(void *objectSet, int value);
extern void InitObjManagerAndMark(void *objectSet, Words4 *desc);
extern void CreateWidgetImageEntry(void *objectSet, u32 key);
extern void LoadWidgetDescriptorsFromFile(void *objectSet, u32 key, int count);
extern void SetAllElementObjectModes(void *objectSet, int mode);
extern int CreateDefaultObjectSlot(void *objectSet, int resource, int kind, int arg3, int arg4);
extern void BuildBoardLayout(void *cursor, int value);
extern void *StartBoardScreen(void);

void *CreateBoardScreen(int mode)
{
    Words4 layout = gBoardBgLayerIds;
    BgLayerDesc bgDesc;
    Words5 animDesc;
    Words4 objDesc;
    BoardState *state;
    int i;

    state = GetRunningTaskWork();
    gBoardScreenGlobals.state = state;
    MI_CpuFill8(state, 0, 0x6700);
    MIi_CpuClear32(-1, gBoardScreenGlobals.state->cellIds, 0x48);
    MIi_CpuClear32(-1, gBoardScreenGlobals.state->nodeIds, 0xa0);
    for (i = 0; i < 6; i++) {
        gBoardNodeGraphicsBufferStorage[i] = 0;
    }
    gBoardScreenGlobals.state->useChannel = (mode == 0x7b);
    if (gBoardScreenGlobals.state->useChannel || IsSessionFlagSet(0x3520) || IsFieldFlag13OrSessionFlagSet()) {
        state->showTutorial = 0;
    } else {
        state->showTutorial = 1;
    }
    if (!gBoardScreenGlobals.state->useChannel) {
        SetSubsceneBgSetupCallback(SetupSubScreenBgLayers);
    }
    SetupSubScreenBgLayers();
    if (!gBoardScreenGlobals.state->useChannel) {
        SetPanelSessionActive();
    }
    if (gBoardScreenGlobals.state->useChannel) {
        bgDesc.layout = &layout;
        bgDesc.count = 4;
        bgDesc.width = 0x20;
        bgDesc.height = 0x20;
        bgDesc.flags = 0;
        gBoardScreenGlobals.state->widget = gBoardScreenGlobals.state->widgetData;
        InitTileTableFrom(gBoardScreenGlobals.state->widget, &bgDesc);
    } else {
        gBoardScreenGlobals.state->widget = GetFieldSceneManager();
    }
    gBoardScreenGlobals.state->resourceA = Msg_OpenContainerAndReadHeader(sOv024_UiBtlBtluiP2_020b74f4, 0xe, 0);
    gBoardScreenGlobals.state->resourceB = Msg_OpenContainerAndReadHeader(sOv024_UiBtlBtlLanguageP2_020b7508, 0xe, 0);
    animDesc = gBoardBackgroundContainerConfig;
    InitBackgroundContainer(state->animSet, &animDesc);
    LoadTagTrackerResourceFile(state->animSet, BOARD_VRAM_KEY(gBoardScreenGlobals.state->resourceA) | 0x8000000f);
    gBoardScreenGlobals.cursor = (void *)SessionBuffer_GetAddress(10);
    objDesc = gBoardObjectManagerConfig;
    objDesc.words[0] = BOARD_VRAM_KEY(gBoardScreenGlobals.state->resourceA) | 0x80000013;
    InitializeResourceContainer(gBoardScreenGlobals.state->objectSet, 0);
    InitObjManagerAndMark(gBoardScreenGlobals.state->objectSet, &objDesc);
    CreateWidgetImageEntry(gBoardScreenGlobals.state->objectSet, BOARD_VRAM_KEY(gBoardScreenGlobals.state->resourceB) | 0x80000019);
    LoadWidgetDescriptorsFromFile(gBoardScreenGlobals.state->objectSet, BOARD_VRAM_KEY(gBoardScreenGlobals.state->resourceA) | 0x80000014, 7);
    SetAllElementObjectModes(gBoardScreenGlobals.state->objectSet, 1);
    gBoardScreenGlobals.state->markerSlots[0] = CreateDefaultObjectSlot(gBoardScreenGlobals.state->objectSet, 0, 0, 0, 0);
    gBoardScreenGlobals.state->markerSlots[1] = CreateDefaultObjectSlot(gBoardScreenGlobals.state->objectSet, 0, 1, 0, 0);
    if (!gBoardScreenGlobals.state->useChannel && IsFieldFlag13OrSessionFlagSet()) {
        if (IsSessionFlagSet(0x3609)) {
            gBoardScreenGlobals.state->markerSlots[2] = CreateDefaultObjectSlot(gBoardScreenGlobals.state->objectSet, 0, 2, 0, 0);
        }
        if (IsSessionFlagSet(0x360a)) {
            gBoardScreenGlobals.state->markerSlots[3] = CreateDefaultObjectSlot(gBoardScreenGlobals.state->objectSet, 0, 2, 0, 0);
        }
    }
    for (i = 0; i < 30; i++) {
        gBoardScreenGlobals.state->itemSlots[i] = CreateDefaultObjectSlot(gBoardScreenGlobals.state->objectSet, 0, 3, 0, 0);
    }
    gBoardScreenGlobals.state->cursorSlot = CreateDefaultObjectSlot(gBoardScreenGlobals.state->objectSet, 0, 4, 0, 0);
    gBoardScreenGlobals.state->targetSlot = CreateDefaultObjectSlot(gBoardScreenGlobals.state->objectSet, 0, 5, 0, 0);
    gBoardScreenGlobals.state->hintSlot = CreateDefaultObjectSlot(gBoardScreenGlobals.state->objectSet, 0, 6, 0, 0);
    gBoardScreenGlobals.state->goalSlot = CreateDefaultObjectSlot(gBoardScreenGlobals.state->objectSet, 0, 7, 0, 0);
    BuildBoardLayout(gBoardScreenGlobals.cursor, 1);
    gBoardScreenGlobals.state->active = 1;
    return StartBoardScreen;
}
