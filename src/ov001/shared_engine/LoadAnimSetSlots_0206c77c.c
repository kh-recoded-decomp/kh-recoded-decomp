#include "nitro/types.h"

typedef struct AnimSlot {
    u8 pad_00[0x24];
    u8 alpha;
    u8 pad_25[0xb];
} AnimSlot;

typedef struct AnimSet {
    AnimSlot *slots;
    s8 slotCount;
    u8 pad_05[0xb];
    s8 current;
    u8 state;
    u8 phase;
    u8 pad_13[5];
    int speed;
    int target;
    int elapsed;
    int reverse;
} AnimSet;

extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void func_0202c690(int arg0);
extern void *RetainOrInitializeSharedRecord_0202c80c(int a, int b);
extern int ReleaseSharedRecordSlot_0202c8a8(void *slot);
extern int *func_0202c940(void *info, void *textureHeader, int flag);
extern int func_0202d3c8(int *objectBase, int recordIndex);
extern int func_0202d3e0(int *objectBase, int recordIndex, int entryIndex);
extern s32 func_ov001_02063a38(void);
extern void SetSlotKeyAndRebind_0206a94c(AnimSlot *slot, int key, int flag);

void LoadAnimSetSlots_0206c77c(AnimSet *set, int recordId, int mode)
{
    int *objectBase;
    void *info;
    int i;

    info = RetainOrInitializeSharedRecord_0202c80c(recordId, 0x11);
    func_0202c690(0);
    objectBase = func_0202c940(info, NULL, 1);
    func_0202c690(1);
    set->slotCount = func_0202d3c8(objectBase, 7);
    if (mode == 0 && func_ov001_02063a38() != 6) {
        set->slotCount--;
    }
    set->slots = NNSi_FndAllocFromDefaultHeap_0202a178(set->slotCount * 0x30);
    for (i = 0; i < set->slotCount; i++) {
        AnimSlot *slots = set->slots;
        SetSlotKeyAndRebind_0206a94c(&slots[i], func_0202d3e0(objectBase, 7, i), 0);
        slots[i].alpha = 0x3f;
    }
    ReleaseSharedRecordSlot_0202c8a8(info);
    set->current = -1;
    set->state = 0;
    set->elapsed = 0;
    switch (mode) {
    case 0:
        set->speed = 0x1800;
        set->phase = 0;
        set->target = 0xc000;
        set->reverse = 0;
        break;
    case 1:
        set->phase = 0;
        set->speed = 0x8cd;
        set->target = 0;
        set->reverse = 1;
        break;
    }
}
