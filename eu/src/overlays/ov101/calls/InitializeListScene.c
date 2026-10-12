#include "src/overlays/ov101/ListMenuData.h"

extern ListSceneState *data_ov101_020c5920;
extern void SetStateFlagBits(u8 clearMask, u8 setBits);
extern void MIi_CpuClearFast(u32 value, void *destination, u32 size);
extern u32 GetCurrentMenuStackEntry(void);
extern void RefreshEntryUnlocks(ListSceneState *scene);
extern void SetupListDisplay(ListSceneState *scene);
extern void LoadStateMessages(ListSceneState *scene);
extern void LoadStateBackgrounds(ListSceneState *scene);
extern void InitListTextLayers(ListSceneState *scene);
extern void InitListSlots(ListSceneState *scene);
extern void LoadPortraitSprites(ListSceneState *scene);
extern void CommitPageInteractionBounds(ListSceneState *scene);
extern u16 *func_ov027_020ba2c8(ListTextArchiveView *view, s32 index);
extern void InitScrollPanel(ListScrollPanelConfig *config, ListSceneState *scene);
extern void DrawListPanelText(s32 which, ListSceneState *scene);
extern const u8 sOv101_VblankFunc_020c1f78[];
extern void func_ov101_020c1980(void);
extern void InvokeForChannelOrBoth(u32 mask, u32 callback, u32 parameter, s32 channel);
extern BOOL IsStateFlagSet(s32 set, s32 bit);
extern void *SetStateFlag(s32 set, s32 bit);
extern void SetGlobalPackedBit(s32 bit);
extern void SetEntryAnimFrame(s32 list, s32 entry, s32 frame, ListSceneState *scene);
extern void SetStatePhase(s32 phase);

BOOL InitializeListScene(ListSceneState *scene)
{
    s32 i = 0;
    s32 selected;
    ListTextPage *page;
    ListTextArchiveView *description;
    u16 *text;

    data_ov101_020c5920 = scene;
    SetStateFlagBits(5, 0);
    MIi_CpuClearFast(0, scene, sizeof(ListSceneState));
    /* Reuse the list selection saved by the parent menu. */
    scene->activeList = GetCurrentMenuStackEntry();
    scene->captionRefreshFrames = 0;
    scene->captionRefreshPhase = 0;
    scene->activePage = 0;
    scene->unknownCe64 = 0;
    scene->handlerPhase = 0;
    scene->handlerPhaseTimer = 0;
    scene->handlerStep = 0;
    RefreshEntryUnlocks(scene);
    MIi_CpuClearFast(0, scene->listPages, sizeof(scene->listPages));
    SetupListDisplay(scene);
    LoadStateMessages(scene);
    LoadStateBackgrounds(scene);
    InitListTextLayers(scene);
    InitListSlots(scene);
    LoadPortraitSprites(scene);
    CommitPageInteractionBounds(scene);
    description = &scene->textArchives[1];

    /* Split the writable UTF-16 description in place and retain each line. */
    for (; i < 40; i++) {
        page = &scene->textPages[i];
        text = func_ov027_020ba2c8(description,
                                  gListEntryTextIndices[i].descriptionIndex);
        page->lineCount = 0;
        page->lines[page->lineCount] = text;
        while (*text != 0) {
            if (*text == '\n') {
                *text++ = 0;
                page->lineCount++;
                page->lines[page->lineCount] = text;
            } else {
                text++;
            }
        }
        page->lineCount++;
    }
    InitScrollPanel(&gPrimaryListScrollConfig, scene);
    gSecondaryListScrollConfig.totalRows = scene->textPages[scene->activeList].lineCount;
    InitScrollPanel(&gSecondaryListScrollConfig, scene);
    DrawListPanelText(-1, scene);
    InvokeForChannelOrBoth(1, (u32)sOv101_VblankFunc_020c1f78,
                          (u32)func_ov101_020c1980, 0);
    selected = scene->activeList;
    if (IsStateFlagSet(1, selected)) {
        SetStateFlag(2, selected);
        SetGlobalPackedBit(selected + 0x1272);
    }
    for (i = 0; i < 9; i++) {
        s32 highlighted = IsStateFlagSet(2, i) != 0;
        SetEntryAnimFrame(0, i + 3, highlighted, scene);
    }
    SetStatePhase(0);
    return TRUE;
}
