#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u32 modelFile;
    u32 animFile;
    u32 extra;
} EntryModelDef;

typedef struct {
    int index;
    u8 model[0xb0];
    fx32 scale[3];
    u8 pad_c0[0x1c];
    u8 blendTable[0x2c];
} EntryModel;

typedef struct {
    EntryModel entries[7];
    EntryModelDef *defs;
    u8 pad_73c[8];
    int entryCount;
    int cursor;
    u32 projection[10];
    fx32 rotateSpeed;
} Ov089Menu;

extern EntryModelDef data_ov089_020c0540[];
extern EntryModelDef data_ov089_020c05d8[];
extern EntryModelDef data_ov089_020c0590[];

extern u32 ReadSessionPackedBits_02064574(int bitOffset, u32 bitCount);
extern void LoadDefaultProjectionValues_0202a7b4(u32 *projection);
extern u32 BuildSlotImageParams_020bc220(int slot, u32 low);
extern void *func_0202c48c(u32 fileId, int mode);
extern void func_0202ed3c(void *dst, u32 fileId, void *info, int mode);
extern void func_0202f4d8(void *model);
extern void selectJointAnimationBlend_0202f2cc(void *model, u16 trackIndex, void *blendTable, s16 blendIndex);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *ptr);

void LoadEntryModels_020bf210(Ov089Menu *menu)
{
    int i;
    int track;
    void *anim;

    switch (ReadSessionPackedBits_02064574(0x3700, 3)) {
    case 0:
        menu->entryCount = 1;
        menu->defs = data_ov089_020c0540;
        break;
    case 6:
        menu->entryCount = 7;
        menu->defs = data_ov089_020c05d8;
        break;
    default:
        menu->entryCount = 6;
        menu->defs = data_ov089_020c0590;
        break;
    }
    LoadDefaultProjectionValues_0202a7b4(menu->projection);
    menu->rotateSpeed = 0x1e000;
    for (i = 0; i < menu->entryCount; i++) {
        menu->entries[i].index = i;
        anim = func_0202c48c(BuildSlotImageParams_020bc220(2, menu->defs[i].animFile), 0xe);
        func_0202ed3c(menu->entries[i].model, BuildSlotImageParams_020bc220(2, menu->defs[i].modelFile), anim, 0xe);
        for (track = 0; track < 5; track++) {
            func_0202f4d8(menu->entries[i].model);
            selectJointAnimationBlend_0202f2cc(menu->entries[i].model, track, menu->entries[i].blendTable, 0);
        }
        menu->entries[i].scale[0] = menu->entries[i].scale[1] = menu->entries[i].scale[2] = 0x800;
        NNSi_FndFreeFromDefaultHeap_0202a1c4(anim);
    }
}
