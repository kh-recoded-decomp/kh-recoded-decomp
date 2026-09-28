#include "nitro/types.h"

typedef struct ModelResList {
    u8 pad_00[0xc];
    void *texFile;
    void *tex;
} ModelResList;

typedef struct ModelInstance {
    u8 pad_00[0x74];
    ModelResList *resList;
    void *resMdl;
} ModelInstance;

typedef struct ModelAnimSet {
    u16 count[5];
    u16 texSource;
    int pad_0c;
    void **objects[5];
} ModelAnimSet;

extern void *func_0202d3e0(void *archive, int memberIndex, int subIndex);
extern int ReadValidatedRecordByte_0202e804(void *file);
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void func_01ff8830(void *dst, int value, int size);
extern void *GetAnimationSetResourceByIndex_0201acb0(void *anmSet, u32 idx);
extern void *NNSi_FndGetAllocatorForDefaultHeap_0202a268(void *heap);
extern void *AllocateAnimationObjectStorage_0201a394(void *allocator, void *anm, void *resMdl);
extern void *FindTextureResourceBlock_0201ac70(void *file);
extern void InitializeAnimationObject_02018554(void *anmObj, void *anm, void *resMdl, void *tex);

void BindModelAnimations_0202e854(ModelAnimSet *set, ModelInstance *inst, void *archive, int texSource)
{
    int i;
    int total = 0;
    int j;

    for (i = 0; i < 5; i++) {
        total += ReadValidatedRecordByte_0202e804(func_0202d3e0(archive, i, 0));
    }
    if (total > 0) {
        void **slot = NNSi_FndAllocFromDefaultHeap_0202a178(total * 4);

        for (i = 0; i < 5; i++) {
            int n = ReadValidatedRecordByte_0202e804(func_0202d3e0(archive, i, 0));
            if (n > 0) {
                set->objects[i] = slot;
                slot += n;
            } else {
                set->objects[i] = NULL;
            }
        }
    } else {
        func_01ff8830(set, 0, sizeof(ModelAnimSet));
    }
    for (i = 0; i < 5; i++) {
        void *anmSet = func_0202d3e0(archive, i, 0);
        int n = ReadValidatedRecordByte_0202e804(anmSet);

        for (j = 0; j < n; j++) {
            void *anm = GetAnimationSetResourceByIndex_0201acb0(anmSet, j);
            void *tex;

            set->objects[i][j] = AllocateAnimationObjectStorage_0201a394(NNSi_FndGetAllocatorForDefaultHeap_0202a268(0), anm, inst->resMdl);
            if (i == 3) {
                tex = inst->resList->tex;
                if (tex == NULL) {
                    tex = FindTextureResourceBlock_0201ac70(func_0202d3e0(inst->resList->texFile, 7, 0));
                }
            } else {
                tex = NULL;
            }
            InitializeAnimationObject_02018554(set->objects[i][j], anm, inst->resMdl, tex);
        }
        set->count[i] = n;
    }
    set->texSource = texSource;
}
