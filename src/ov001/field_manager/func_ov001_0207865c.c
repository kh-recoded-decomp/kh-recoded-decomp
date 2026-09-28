#include "nitro/types.h"

typedef struct {
    void *headObject;
    void *tailObject;
    u16 numObjects;
    u16 offset;
} NNSFndList;

typedef struct {
    u8 pad_00[8];
    u32 id;
} FieldListEntry;

typedef struct {
    u8 pad_000[0xB8];
    NNSFndList list;
    u8 pad_0C4[0x28];
    s32 selectedIndex;
} FieldMenu;

typedef struct {
    u32 unk_00;
    FieldMenu *menu;
} FieldMenuHandle;

extern FieldMenuHandle data_ov001_020a04b0;

extern void *FND_GetListObjectByIndex_02012a64(NNSFndList *list, u16 index);

u16 func_ov001_0207865c(void)
{
    FieldMenu *menu = data_ov001_020a04b0.menu;
    FieldListEntry *entry = FND_GetListObjectByIndex_02012a64(&menu->list, menu->selectedIndex);

    return entry->id;
}
