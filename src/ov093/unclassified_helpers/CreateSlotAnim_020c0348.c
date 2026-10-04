#include "nitro/types.h"

typedef struct {
    u32 archive;
    u32 resource;
} AnimSource;

typedef struct {
    AnimSource source;
    int x;
    int y;
    int mode;
    int flag;
    int start;
} SlotAnimDesc;

typedef struct {
    s16 right;
    s16 bottom;
    s16 left;
    s16 top;
} AnimBounds;

typedef struct {
    int animIndex;
    int x;
    int y;
    int width;
    int height;
    AnimBounds bounds;
} SlotEntry;

typedef struct {
    u8 pad_0000[0x200];
    u8 animSets[2][0x6434];
    SlotEntry leftSlots[13];
    SlotEntry rightSlots[13];
} SceneWork;

extern int func_0204f0b4(void *animSet, AnimSource source);
extern void func_0204f204(void *animSet, int index, int frame);
extern void func_0204f2e4(void *animSet, int index);
extern void Slot_SetMode2Bit_0204f480(void *animSet, int index, int value);
extern void func_0204f378(void *animSet, int index, int value);
extern int func_0204f2c0(void *animSet, int index);
extern void func_ov093_020c0458(int side, int slotIndex, int x, int y, SceneWork *work);
extern AnimBounds *GetSlotAnimResource_020c0680(int side, int slotIndex, SceneWork *work);
extern void func_01ff89a8(const void *src, void *dest, int size);

void CreateSlotAnim_020c0348(int side, int slotIndex, SlotAnimDesc *desc, SceneWork *work)
{
    int offset = side * 0x6434;
    u8 *animSets = work->animSets[0];
    SlotEntry *entry = side == 0 ? &work->leftSlots[slotIndex] : &work->rightSlots[slotIndex];
    int animIndex;
    AnimBounds *bounds;

    animIndex = func_0204f0b4(animSets + offset, desc->source);
    func_0204f204(animSets + offset, animIndex, 0);
    func_0204f2e4(animSets + offset, animIndex);
    Slot_SetMode2Bit_0204f480(animSets + offset, animIndex, desc->mode);
    func_0204f378(animSets + offset, animIndex, desc->flag);
    if (desc->start != 0) {
        func_0204f2c0(animSets + offset, animIndex);
    }
    entry->animIndex = animIndex;
    entry->x = desc->x;
    entry->y = desc->y;
    func_ov093_020c0458(side, slotIndex, desc->x, desc->y, work);
    bounds = GetSlotAnimResource_020c0680(side, slotIndex, work);
    entry->width = bounds->right - bounds->left + 1;
    entry->height = bounds->bottom - bounds->top + 1;
    func_01ff89a8(bounds, &entry->bounds, sizeof(AnimBounds));
}
