#include "nitro/types.h"

typedef struct AnimBlendSet {
    u8 data[0x104];
} AnimBlendSet;

typedef struct AnimFileIds {
    u32 ids[4];
} AnimFileIds;

typedef struct Actor {
    u8 pad_0000[0x1700];
    AnimBlendSet *animBank;
} Actor;

extern const AnimFileIds data_ov059_020cfe6c;
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern u32 func_ov001_0206dba0(int kind);
extern u8 *RetainOrInitializeSharedRecord_0202c80c(u32 fileId, int kind);
extern void *func_0202c48c(u32 fileId, int kind);
extern void func_0202ed9c(AnimBlendSet *set, u8 *record, void *block, int flag);
extern void func_ov059_020c8b7c(void *state);

void Actor_LoadJointBlendSets_020c8a84(Actor *actor, void *animReset) {
    AnimFileIds files;
    void *block;
    u8 *record;
    u32 fileId;
    int i;

    actor->animBank = NNSi_FndAllocFromDefaultHeap_0202a178(sizeof(AnimBlendSet) * 4);
    i = 0;
    files = data_ov059_020cfe6c;
    for (; i < 4; i++) {
        fileId = files.ids[i];
        block = NULL;
        record = RetainOrInitializeSharedRecord_0202c80c(
            0x80000000 | (((func_ov001_0206dba0(2) + 0x8000) & 0xfffffc) << 7) | (fileId & 0x1ff), 8);
        if (*(u16 *)(record + 2) == 0) {
            block = func_0202c48c(
                0x80000000 | (((func_ov001_0206dba0(2) + 0x8000) & 0xfffffc) << 7) | ((fileId + 1) & 0x1ff), 0x11);
        }
        func_0202ed9c(&actor->animBank[i], record, block, 8);
        if (block != NULL) {
            NNSi_FndFreeFromDefaultHeap_0202a1c4(block);
        }
    }
    func_ov059_020c8b7c(animReset);
}
