#include "nitro/types.h"

typedef struct {
    u32 words[0x3760 / 4];
} SaveData;

typedef struct {
    u8 bytes[0x34];
} TextLayer;

typedef struct {
    u8 pad_00[4];
    s32 step : 8;
    u32 stepHigh : 24;
    u8 pad_08[0x48];
    void *tagTracker;
    void *panel;
    u8 pad_58[0x7080];
    SaveData savedGame;
    u8 pad_A838[0xc];
    TextLayer layers[4];
    void *buffer;
} SaveSelectScreen;

extern SaveData *data_0205fe0c;
extern SaveSelectScreen *data_ov080_020c5e00;
extern void SweepElements_020b831c(void *tracker);
extern void DestroyAllContainerElements_020b900c(void *container);
extern void ReleaseIfMarked_020b903c(void *owner);
extern void FreePointerIfSet_020ba294(void **ptr);
extern BOOL DestroyFndObjectList_020014f0(TextLayer *layer);
extern void func_ov039_020be6a0(void);
extern void RebuildRecordCounters_02028e6c(void);
extern void *GetOverlaySelectionRecord(u32 selectionIndex);
extern void ComputePlayerStats_02050b30(SaveData *state, void *out, BOOL recompute, int scaleParam);
extern void FillSelectionRecordFromGroup_0204f8dc(void);
extern void BuildSelectionEntryList_0204f98c(void);
extern void SyncSelectionRecordFromSlotEntry_0204fabc(void);
extern void func_0204fba0(void);
extern void LoadSelectionPackedValues_0205053c(void);

void DestroySaveSelectScreen_020c4ad0(SaveSelectScreen *screen)
{
    SweepElements_020b831c(screen->tagTracker);
    DestroyAllContainerElements_020b900c(screen->panel);
    ReleaseIfMarked_020b903c(screen->panel);
    FreePointerIfSet_020ba294(&screen->buffer);
    DestroyFndObjectList_020014f0(&screen->layers[0]);
    DestroyFndObjectList_020014f0(&screen->layers[1]);
    DestroyFndObjectList_020014f0(&screen->layers[3]);
    DestroyFndObjectList_020014f0(&screen->layers[2]);
    *(vu16 *)0x04000050 = 0;
    func_ov039_020be6a0();
    data_ov080_020c5e00 = NULL;
    if (screen->step != 9) {
        *data_0205fe0c = screen->savedGame;
        RebuildRecordCounters_02028e6c();
        ComputePlayerStats_02050b30(data_0205fe0c, GetOverlaySelectionRecord(0), TRUE, 0);
        FillSelectionRecordFromGroup_0204f8dc();
        BuildSelectionEntryList_0204f98c();
        SyncSelectionRecordFromSlotEntry_0204fabc();
        func_0204fba0();
        LoadSelectionPackedValues_0205053c();
    }
}
