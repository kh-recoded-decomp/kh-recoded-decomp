#include "nitro/types.h"

typedef struct {
    s32 offsets[11];
} RegionOffsetTable;

typedef struct {
    u8 pad_000[0x10];
    u8 region;
} SelectionRecord;

typedef struct {
    u8 pad_0000[0x488];
    u32 activeEntry;
    u8 pad_048c[0xb34 - 0x48c];
    u32 entries[0x200];
    u32 savedEntry;
} Scene;

typedef struct {
    u32 unk0;
    Scene *scene;
} SceneHolder;

extern SceneHolder data_ov001_020a04a4;
extern const RegionOffsetTable data_ov001_0209dd68;
extern SelectionRecord *func_0204f768(u32 index);
extern void ClearChoiceHighlight_020701a8(Scene *scene);
extern void PlaySoundEffect_0204d924(int channel, int soundId);
extern void func_ov001_0207b640(u32 value);

void ApplyRegionChoiceEntry_02072530(u32 choice)
{
    Scene *scene = data_ov001_020a04a4.scene;
    RegionOffsetTable table = data_ov001_0209dd68;
    int index = choice + table.offsets[func_0204f768(0)->region];

    ClearChoiceHighlight_020701a8(scene);
    scene->activeEntry = scene->entries[index];
    scene->savedEntry = scene->entries[index];
    PlaySoundEffect_0204d924(0, 0x13);
    func_ov001_0207b640((u8)choice);
}
