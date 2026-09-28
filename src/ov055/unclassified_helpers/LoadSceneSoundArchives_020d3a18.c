#include "nitro/types.h"

typedef struct OverlaySelectionRecord {
    u8 overlaySet;
    u8 pad_01[0x1B];
    s16 soundArcIndex;
} OverlaySelectionRecord;

typedef struct SoundArcLoader {
    u8 pad_00[0x28];
    s32 primaryArc;
    s32 secondaryArc;
} SoundArcLoader;

typedef struct SoundArcList {
    void **entries;
    s32 entryCount;
} SoundArcList;

typedef struct SceneState {
    u8 pad_000[0x9B4];
    u8 selectionIndex;
    u8 pad_9B5[0xB2C - 0x9B5];
    SoundArcLoader soundArcLoader;
    u8 pad_B5C[0x1070 - 0xB5C];
    SoundArcList soundArcList;
} SceneState;

extern OverlaySelectionRecord *GetOverlaySelectionRecord_0204f768(u32 selectionIndex);
extern void SoundArcLoader_Load_ov021_020a7f74(SoundArcLoader *loader, s32 primaryArc, s32 secondaryArc);
extern void SoundArcList_LoadAll_ov021_020ad84c(SoundArcList *list);

void LoadSceneSoundArchives_020d3a18(SceneState *scene)
{
    OverlaySelectionRecord *record;

    record = GetOverlaySelectionRecord_0204f768(scene->selectionIndex);
    SoundArcLoader_Load_ov021_020a7f74(&scene->soundArcLoader, 0x31, record->soundArcIndex + 0x53);
    SoundArcList_LoadAll_ov021_020ad84c(&scene->soundArcList);
}
