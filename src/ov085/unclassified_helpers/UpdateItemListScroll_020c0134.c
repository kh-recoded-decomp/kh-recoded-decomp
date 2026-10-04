#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct WidgetPos {
    fx32 x;
    fx32 y;
} WidgetPos;

typedef struct ScrollList {
    s16 count;
    s16 offset;
    s16 base;
} ScrollList;

typedef struct ItemListMenu {
    u8 mode;
    u8 dirty;
    u8 pad_02[0x1a];
    ScrollList list;
    u8 pad_22[0x1ae];
    void *cells;
    u8 pad_1d4[0x30];
    int *scrollBar;
} ItemListMenu;

extern int GetFieldCa4a_020bc9e0(void);
extern BOOL func_ov039_020be0c4(ScrollList *list, void *cells);
extern WidgetPos *func_ov027_020b91a8(void *cells, int *widget);
extern void func_ov027_020b91c8(void *cells, int *widget, WidgetPos *pos, int mode);
extern void func_ov085_020c0280(ItemListMenu *menu);

void UpdateItemListScroll_020c0134(ItemListMenu *menu)
{
    GetFieldCa4a_020bc9e0();
    if ((menu->mode == 0 && menu->list.count != 0 && func_ov039_020be0c4(&menu->list, menu->cells))
        || menu->dirty != 0) {
        WidgetPos pos = *func_ov027_020b91a8(menu->cells, menu->scrollBar);

        if (menu->list.count != 0) {
            pos.y += (menu->list.offset - menu->list.base) << 16;
        }
        func_ov027_020b91c8(menu->cells, menu->scrollBar, &pos, 2);
        if (menu->dirty == 0) {
            menu->dirty = 1;
        }
    }
    func_ov085_020c0280(menu);
}
