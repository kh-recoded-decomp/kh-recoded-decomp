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
    u8 pad_494_pad[0x494 - 0x494];
    u32 startFrame;
} CursorModelSet;

extern ModelIdTable data_ov001_0209e34c;

extern u32 ObjectManager_GetFirstEntryParam_0207ee14(u32 id);
extern u32 ObjectManager_GetSecondEntryParam_0207ee48(u32 id);
extern void *RetainOrInitializeSharedRecord_0202c80c(int a, int b);
extern void *func_0202c48c(u32 fileId, u32 mode);
extern void func_0202ed9c(void *object, void *resource, void *block, int flag);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);

void LoadCursorModels_02082208(CursorModelSet *set) {
    int i = 0;
    ModelIdTable table = data_ov001_0209e34c;
    u32 *ids = table.ids;

    for (; i < 4; i++) {
        u32 id = ids[i];
        void *resource = RetainOrInitializeSharedRecord_0202c80c(ObjectManager_GetFirstEntryParam_0207ee14(id), 3);
        void *block = func_0202c48c(ObjectManager_GetSecondEntryParam_0207ee48(id), 3);
        func_0202ed9c(set->models[i].model, resource, block, 3);
        NNSi_FndFreeFromDefaultHeap_0202a1c4(block);
        set->models[i].frameC = set->startFrame;
        set->models[i].frameB = set->models[i].frameC;
        set->models[i].frameA = set->models[i].frameB;
    }
}
