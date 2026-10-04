#include "nitro/types.h"

typedef struct {
    int animIndex;
    u8 pad_04[0x18];
} SlotEntry;

typedef struct {
    u8 data[0x1c];
} SlotTemplate;

typedef struct {
    u32 vramAttr;
    int mode;
    int unk_08;
    int unk_0C;
} ObjManagerParams;

typedef struct {
    u32 vramBase;
    u32 unk_04;
    u32 paletteBase;
    u8 pad_000c[0x200 - 0xc];
    u8 animSets[2][0x6434];
    SlotEntry leftSlots[13];
    SlotEntry rightSlots[30];
} SceneWork;

extern SlotTemplate data_ov093_020c4108[13];
extern SlotTemplate data_ov093_020c4274[30];

extern void InitObjManager_0204efa8(void *manager, ObjManagerParams *params);
extern void PXI_Init_0204f00c(void *manager, u32 attr);
extern void func_ov093_020c0348(int side, int slotIndex, SlotTemplate *tmpl, SceneWork *work);
extern BOOL IsEntryFlagSet_020c22a4(int flagSet, int entryIndex);
extern void SetSlotAnimFlag_020c0310(int side, int slotIndex, int value, SceneWork *work);
extern void func_ov093_020c0564(int side, int slotIndex, BOOL enabled, SceneWork *work);
extern void SetGlobalPackedBit_02027320(int bitIndex);
extern void func_0204f2e4(void *manager, int animIndex);

void InitEntrySlotSprites_020c0100(SceneWork *work)
{
    ObjManagerParams params;
    int entry;
    int i;
    int unlocked;
    void *rightSet;
    BOOL seen;

    i = 0;
    params.vramAttr = ((work->vramBase + 0x8000) & 0xfffffc) << 7 | 0x80000006;
    params.mode = 1;
    params.unk_08 = 0;
    params.unk_0C = 0;
    InitObjManager_0204efa8(work->animSets[0], &params);
    PXI_Init_0204f00c(work->animSets[0], ((work->paletteBase + 0x8000) & 0xfffffc) << 7 | 0x80000000);
    for (; i < 13; i++) {
        func_ov093_020c0348(0, i, &data_ov093_020c4108[i], work);
    }
    for (entry = 0; entry < 10; entry++) {
        unlocked = IsEntryFlagSet_020c22a4(4, entry);
        seen = IsEntryFlagSet_020c22a4(5, entry) != 0;
        SetSlotAnimFlag_020c0310(0, entry + 3, unlocked, work);
        func_ov093_020c0564(0, entry + 3, seen, work);
        if (entry == 0 && unlocked) {
            SetGlobalPackedBit_02027320(0x1202);
        }
    }
    params.vramAttr = ((work->vramBase + 0x8000) & 0xfffffc) << 7 | 0x80000002;
    params.mode = 2;
    params.unk_08 = 0;
    params.unk_0C = 0;
    rightSet = work->animSets[1];
    InitObjManager_0204efa8(rightSet, &params);
    for (i = 0; i < 30; i++) {
        func_ov093_020c0348(1, i, &data_ov093_020c4274[i], work);
    }
    for (i = 20; i < 30; i++) {
        func_0204f2e4(rightSet, work->rightSlots[i].animIndex);
    }
}









