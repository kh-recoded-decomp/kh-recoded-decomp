#include "nitro/types.h"

typedef struct ScreenWork {
    u8 pad_00000[0x10];
    void *buffer0;
    void *buffer1;
    void *container;
    u8 pad_0001C[0x18];
    u8 unk_00034[0x6c0];
    u8 sceneObject[0x4768];
    void *messageData;
    u8 pad_04E60[0xcda0];
    void *heapBlock;
} ScreenWork;

extern BOOL ReleaseRecordSlot_02051dfc(s32 slot);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern int ZeroHalfThenFree_0202cd78(void *buffer);
extern void ReleaseResourceAndDetach_0202eee8(void *object);
extern void _fp_init_020c9f5c(void *object);
extern void DestroyAllContainerElements_020b900c(void *container);
extern void func_ov027_020b903c(void *container);
extern void FreePointerIfSet_020ba294(void **ptr);
extern void SetSecondaryElementEnabled_020bc084(BOOL enabled);

void ReleaseScreenResources_020c90bc(ScreenWork *work)
{
    void *container = work->container;

    ReleaseRecordSlot_02051dfc(1);
    ReleaseRecordSlot_02051dfc(0);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(work->heapBlock);
    ZeroHalfThenFree_0202cd78(work->buffer1);
    ZeroHalfThenFree_0202cd78(work->buffer0);
    ReleaseResourceAndDetach_0202eee8(work->sceneObject);
    _fp_init_020c9f5c(work->unk_00034);
    DestroyAllContainerElements_020b900c(container);
    func_ov027_020b903c(container);
    FreePointerIfSet_020ba294(&work->messageData);
    SetSecondaryElementEnabled_020bc084(TRUE);
}
