#include "nitro/types.h"

typedef struct {
    void **objects;
    s8 count;
    u8 pad_05[7];
    void *resource;
    void *buffer;
} FieldObjectManager;

extern FieldObjectManager *data_ov001_020a04d8;
extern void func_ov001_02087414(void);
extern void func_ov001_02086db8(void);
extern void func_ov001_0207f3d0(void *object);
extern void ZeroHalfThenFree_0202cd78(void *resource);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *ptr);
extern void StoreGlobalArrayEntry_02025668(int index, int value);

void DestroyFieldObjectManager_0207ed6c(void)
{
    FieldObjectManager *manager = data_ov001_020a04d8;
    int i;

    func_ov001_02087414();
    func_ov001_02086db8();
    for (i = 0; i < manager->count; i++) {
        if (manager->objects[i] != NULL) {
            func_ov001_0207f3d0(manager->objects[i]);
            manager->objects[i] = NULL;
        }
    }
    if (manager->resource != NULL) {
        ZeroHalfThenFree_0202cd78(manager->resource);
    }
    if (manager->buffer != NULL) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4(manager->buffer);
    }
    if (manager->objects != NULL) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4(manager->objects);
    }
    NNSi_FndFreeFromDefaultHeap_0202a1c4(data_ov001_020a04d8);
    data_ov001_020a04d8 = NULL;
    StoreGlobalArrayEntry_02025668(4, 0);
}
