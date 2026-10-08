#include "nitro/types.h"

#pragma opt_propagation off

typedef struct {
    u32 ids[4];
} ModelIdTable;

typedef struct {
    u8 model[0xb0];
    u32 frameA;
    u32 frameB;
    u32 frameC;
    u8 pad_bc[0x104 - 0xbc];
} CursorModel;

typedef struct {
    u8 pad_00[0x84];
    CursorModel models[4];
    u32 startFrame;
} CursorModelSet;

extern ModelIdTable data_ov001_0209e374;

extern u32 ObjectManager_GetFirstEntryParam(u32 id);
extern u32 ObjectManager_GetSecondEntryParam(u32 id);
extern void *SND_RegisterSeq(int a, int b);
extern void *func_0202c4a0(u32 fileId, u32 mode);
extern void func_0202edb0(void *object, void *resource, void *block, int flag);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

void LoadCursorModels(CursorModelSet *set) {
    int i = 0;
    ModelIdTable table = data_ov001_0209e374;
    u32 *ids = table.ids;

    for (; i < 4; i++) {
        u32 id = ids[i];
        void *resource = SND_RegisterSeq(ObjectManager_GetFirstEntryParam(id), 3);
        void *block = func_0202c4a0(ObjectManager_GetSecondEntryParam(id), 3);
        func_0202edb0(set->models[i].model, resource, block, 3);
        NNSi_FndFreeFromDefaultHeap(block);
        set->models[i].frameC = set->startFrame;
        set->models[i].frameB = set->models[i].frameC;
        set->models[i].frameA = set->models[i].frameB;
    }
}
