#include "nitro/types.h"

typedef struct ResourceContainer ResourceContainer;

typedef struct {
    u8 pad_00000[0x10];
    void *primaryArchive;
    void *secondaryArchive;
    ResourceContainer *layout;
    u8 pad_0001c[0x34 - 0x1c];
    u8 listState[0x6f4 - 0x34];
    u8 model[0x4e5c - 0x6f4];
    void *messageTable;
    u8 pad_04e60[0x11c00 - 0x4e60];
    void *listData;
} ItemPicker;

extern BOOL ReleaseRecordSlot_02051dfc(s32 slot);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern int ZeroHalfThenFree_0202cd78(void *arg0);
extern void ReleaseResourceAndDetach_0202eee8(u8 *object);
extern void _fp_init_020d10dc(void *state);
extern void DestroyAllContainerElements_020b900c(ResourceContainer *container);
extern void func_ov027_020b903c(ResourceContainer *container);
extern void FreePointerIfSet_020ba294(void **ptr);
extern void SetSecondaryElementEnabled_020bc084(BOOL enabled);

void DestroyItemPicker_020cffb8(ItemPicker *picker)
{
    ResourceContainer *layout = picker->layout;

    ReleaseRecordSlot_02051dfc(1);
    ReleaseRecordSlot_02051dfc(0);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(picker->listData);
    ZeroHalfThenFree_0202cd78(picker->secondaryArchive);
    ZeroHalfThenFree_0202cd78(picker->primaryArchive);
    ReleaseResourceAndDetach_0202eee8(picker->model);
    _fp_init_020d10dc(picker->listState);
    DestroyAllContainerElements_020b900c(layout);
    func_ov027_020b903c(layout);
    FreePointerIfSet_020ba294(&picker->messageTable);
    SetSecondaryElementEnabled_020bc084(TRUE);
}
