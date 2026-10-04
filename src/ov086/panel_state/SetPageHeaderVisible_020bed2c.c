#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x134];
    int pageIndex;
    u8 pad_138[4];
    int stepCount;
    int itemId;
} Ov086Menu;

extern u8 *func_ov039_020bc1cc(void);
extern void *func_ov027_020b90a4(u8 *panel, int elementId);
extern void func_ov027_020b9580(u8 *panel, void *element, BOOL visible);
extern void func_ov086_020bebe8(Ov086Menu *menu);

void SetPageHeaderVisible_020bed2c(Ov086Menu *menu, BOOL visible)
{
    u8 *panel = func_ov039_020bc1cc();
    void *element;

    if (menu->pageIndex == 3) {
        element = func_ov027_020b90a4(panel, 0xd);
    } else if (menu->pageIndex == 6) {
        element = func_ov027_020b90a4(panel, 0x10);
    } else {
        element = func_ov027_020b90a4(panel, 0xb);
    }
    func_ov027_020b9580(panel, element, visible);
    if (menu->pageIndex != 7 && ((menu->pageIndex == 6 && menu->stepCount == 1) || (menu->pageIndex != 6 && menu->stepCount >= 1))) {
        if (menu->itemId != 0) {
            func_ov027_020b9580(panel, func_ov027_020b90a4(panel, 0x2d), visible);
        }
        if (menu->itemId != 0x38) {
            func_ov027_020b9580(panel, func_ov027_020b90a4(panel, 0x2e), visible);
        }
    }
    func_ov086_020bebe8(menu);
}
