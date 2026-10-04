#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x1dc];
    void *listEntry;
} Ov086Menu;

extern Ov086Menu *data_ov086_020c3000;
extern void *func_ov039_020bc1cc(void);
extern void RemoveListEntry_020bc70c(void *entry);
extern void func_ov027_020b7dfc(void *tracker);
extern void DestroyAllContainerElements_020b900c(void *container);
extern void ReleaseIfMarked_020b903c(void *owner);
extern BOOL DestroyFndObjectList_020014f0(void *list);
extern void FreePointerIfSet_020ba294(void *ptr);
extern void FreeAllocatedBuffers_020b9a60(void *owner);
extern BOOL ReleaseRecordSlot_02051dfc(s32 slot);
extern void ReleaseRecordManager_02051cdc(void);

void DestroyRecordMenu_020c1e50(void)
{
    void *container = func_ov039_020bc1cc();
    Ov086Menu *menu = data_ov086_020c3000;
    u8 *base = (u8 *)menu;

    RemoveListEntry_020bc70c(menu->listEntry);
    func_ov027_020b7dfc(base + 0x190);
    DestroyAllContainerElements_020b900c(container);
    ReleaseIfMarked_020b903c(container);
    DestroyFndObjectList_020014f0(base + 0xc);
    DestroyFndObjectList_020014f0(base + 0x40);
    DestroyFndObjectList_020014f0(base + 0x74);
    FreePointerIfSet_020ba294(menu);
    FreeAllocatedBuffers_020b9a60(base + 0x174);
    ReleaseRecordSlot_02051dfc(0);
    ReleaseRecordManager_02051cdc();
    *(vu32 *)0x04001000 &= ~0xe000;
}
