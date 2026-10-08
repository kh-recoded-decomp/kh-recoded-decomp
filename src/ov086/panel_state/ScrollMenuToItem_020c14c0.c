#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x140];
    int itemId;
    int prevItemId;
    int selectedRow;
} Ov086Menu;

typedef struct {
    s32 x;
    s32 y;
} ElementOffset;

extern u8 *func_ov039_020bc1cc(void);
extern void *func_ov027_020b90a4(u8 *panel, int elementId);
extern void func_ov027_020b9580(u8 *panel, void *element, BOOL visible);
extern void func_ov027_020b91c8(u8 *panel, void *element, ElementOffset *offset, int flags);

void ScrollMenuToItem_020c14c0(Ov086Menu *menu, int itemId)
{
    u8 *panel = func_ov039_020bc1cc();
    ElementOffset offset = {0, 0};
    int clamped;

    menu->itemId = itemId;
    clamped = itemId;
    if (clamped > 0x38) {
        clamped = 0x38;
    }
    offset.y = clamped << 12;
    func_ov027_020b91c8(panel, func_ov027_020b90a4(panel, 0x14), &offset, 5);
    if (menu->prevItemId == 0) {
        if (itemId > 0) {
            func_ov027_020b9580(panel, func_ov027_020b90a4(panel, 0x2d), TRUE);
        } else {
            menu->selectedRow = -1;
        }
    } else if (itemId == 0) {
        menu->selectedRow = -1;
        func_ov027_020b9580(panel, func_ov027_020b90a4(panel, 0x2d), FALSE);
    }
    if (menu->prevItemId == 0x38) {
        if (itemId < 0x38) {
            func_ov027_020b9580(panel, func_ov027_020b90a4(panel, 0x2e), TRUE);
        } else {
            menu->selectedRow = -1;
        }
    } else if (itemId == 0x38) {
        menu->selectedRow = -1;
        func_ov027_020b9580(panel, func_ov027_020b90a4(panel, 0x2e), FALSE);
    }
    menu->prevItemId = itemId;
}
