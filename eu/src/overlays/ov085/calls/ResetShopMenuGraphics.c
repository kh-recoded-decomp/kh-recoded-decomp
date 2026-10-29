#include "nitro/types.h"

typedef struct MenuObjectList {
    u32 reserved_00;
    void *headObject;
    void *tailObject;
    u16 numObjects;
    u16 offset;
    u8 pad_10[0x24];
} MenuObjectList;

typedef struct IconCell {
    u16 width;
    u16 height;
    u32 texImageParam;
    u32 plttBase;
} IconCell;

typedef struct PaletteResource {
    u8 pad_00[0x0c];
    const void *colors;
} PaletteResource;

typedef struct ShopMenu {
    u8 pad_00[2];
    u8 hasPaletteBackup;
    u8 pad_03[0x15];
    u32 savedVisiblePlanes;
    u8 pad_1c[0xf0 - 0x1c];
    MenuObjectList objectLists[4];
    u8 pad_1c0[0x278 - 0x1c0];
    void *ownedPointer;
    u8 pad_27c[0x4810 - 0x27c];
    IconCell icons[133];
    u8 pad_4e4c[0x5e54 - 0x4e4c];
    u32 savedResourceBits[16];
    u32 *sharedResourceBits;
    u8 pad_5e98[8];
    PaletteResource *paletteResource;
    void *paletteBackup;
} ShopMenu;

typedef char MenuObjectListSizeCheck[(sizeof(MenuObjectList) == 0x34) ? 1 : -1];
typedef char IconCellSizeCheck[(sizeof(IconCell) == 12) ? 1 : -1];

extern void *func_ov039_020bc1dc(void);
extern void *GetPrimaryMenuElement(void);
extern void SweepElements(void);
extern void FreePointerIfSet(void **ptr);
extern void DestroyAllContainerElements(void *container);
extern void ReleaseIfMarked(void *container);
extern void func_ov085_020c1fd4(IconCell *icons);
extern void ReleaseRecordSlot(int slot);
extern BOOL DestroyFndObjectList(MenuObjectList *list);
extern void GX_LoadBGPltt(const void *source, u32 offset, u32 size);
extern void NNSi_FndFreeFromDefaultHeap(void *pointer);
extern void NNS_GfdResetFrmTexVramState(void);
extern void NNS_GfdResetFrmPlttVramState(void);

void ResetShopMenuGraphics(ShopMenu *menu)
{
    const u32 *source;
    u32 *destination;
    u32 *end;
    void *container = func_ov039_020bc1dc();

    GetPrimaryMenuElement();
    SweepElements();
    FreePointerIfSet(&menu->ownedPointer);
    DestroyAllContainerElements(container);
    ReleaseIfMarked(container);
    func_ov085_020c1fd4(menu->icons);
    ReleaseRecordSlot(8);
    ReleaseRecordSlot(0);
    DestroyFndObjectList(&menu->objectLists[0]);
    DestroyFndObjectList(&menu->objectLists[1]);
    DestroyFndObjectList(&menu->objectLists[2]);
    DestroyFndObjectList(&menu->objectLists[3]);
    if (menu->hasPaletteBackup) {
        GX_LoadBGPltt(menu->paletteResource->colors, 0, 0x40);
        NNSi_FndFreeFromDefaultHeap(menu->paletteBackup);
    }
    NNS_GfdResetFrmTexVramState();
    NNS_GfdResetFrmPlttVramState();
    *(volatile u32 *)0x04000000 =
        (*(volatile u32 *)0x04000000 & 0xffffe0ff) | (menu->savedVisiblePlanes << 8);
    source = menu->savedResourceBits;
    destination = menu->sharedResourceBits;
    end = destination + 16;
    while (destination < end) {
        *destination |= *source;
        source++;
        destination++;
    }
}
