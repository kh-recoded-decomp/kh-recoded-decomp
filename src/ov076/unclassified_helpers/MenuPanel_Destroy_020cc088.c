#include "nitro/types.h"

typedef struct MenuPanel {
    u8 pad_00000[0x10];
    void *buffer10;
    void *buffer14;
    void *container;
    u8 pad_0001C[0x18];
    u8 unk_34[0x6c0];
    u8 model[0x4768];
    void *unk_4E5C;
    u8 pad_04E60[0xcda0];
    void *heapBlock;
} MenuPanel;

extern BOOL ReleaseRecordSlot_02051dfc(s32 slot);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern int ZeroHalfThenFree_0202cd78(void *block);
extern void ReleaseResourceAndDetach_0202eee8(u8 *object);
extern void func_ov076_020ccf10(void *object);
extern void DestroyAllContainerElements_020b900c(void *container);
extern void func_ov027_020b903c(void *container);
extern void FreePointerIfSet_020ba294(void **ptr);
extern void SetSecondaryElementEnabled_020bc084(BOOL enabled);

void MenuPanel_Destroy_020cc088(MenuPanel *panel)
{
    void *container = panel->container;

    ReleaseRecordSlot_02051dfc(1);
    ReleaseRecordSlot_02051dfc(0);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(panel->heapBlock);
    ZeroHalfThenFree_0202cd78(panel->buffer14);
    ZeroHalfThenFree_0202cd78(panel->buffer10);
    ReleaseResourceAndDetach_0202eee8(panel->model);
    func_ov076_020ccf10(panel->unk_34);
    DestroyAllContainerElements_020b900c(container);
    func_ov027_020b903c(container);
    FreePointerIfSet_020ba294(&panel->unk_4E5C);
    SetSecondaryElementEnabled_020bc084(TRUE);
}
