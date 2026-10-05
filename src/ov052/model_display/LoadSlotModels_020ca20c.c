#include "nitro/types.h"

typedef struct {
    u32 ids[4];
} ModelIdList;

typedef struct {
    u8 bytes[0x104];
} SlotModel;

typedef struct {
    u8 pad_000[0x9b4];
    u8 pool;
    u8 pad_9b5[0x106c - 0x9b5];
    SlotModel *models;
} ModelActor;

extern const ModelIdList data_ov052_020d20dc;
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern u32 func_ov001_0206dba0(int index);
extern void *RetainOrInitializeSharedRecord_0202c80c(u32 fileId, int heap);
extern void *func_0202c48c(u32 fileId, u32 flags);
extern void func_0202ed9c(SlotModel *object, void *record, void *source, int heap);
extern void func_ov052_020ca310(void *block);

void LoadSlotModels_020ca20c(ModelActor *actor, void *block)
{
    int i;
    u32 id;
    void *source;
    u16 *record;
    int heap;
    ModelIdList list;

    heap = actor->pool + 8;
    actor->models = NNSi_FndAllocFromDefaultHeap_0202a178(0x410);
    i = 0;
    list = data_ov052_020d20dc;
    for (; i < 4; i++) {
        id = list.ids[i];
        source = NULL;
        record = RetainOrInitializeSharedRecord_0202c80c(((func_ov001_0206dba0(2) + 0x8000) & 0xfffffc) << 7 | 0x80000000 | (id & 0x1ff), heap);
        if (record[1] == 0) {
            source = func_0202c48c(((func_ov001_0206dba0(2) + 0x8000) & 0xfffffc) << 7 | 0x80000000 | ((id + 1) & 0x1ff), 0x11);
        }
        func_0202ed9c(&actor->models[i], record, source, heap);
        if (source != NULL) {
            NNSi_FndFreeFromDefaultHeap_0202a1c4(source);
        }
    }
    func_ov052_020ca310(block);
}
