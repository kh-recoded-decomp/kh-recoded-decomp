#include "nitro/types.h"

typedef struct ItemListView {
    u8 pad_0000[0x4580];
    u16 visibleCount;
} ItemListView;

extern void func_ov077_020c631c(ItemListView *view, u32 category);

u16 BuildItemListForCategory_020c65d8(ItemListView *view, u32 category)
{
    func_ov077_020c631c(view, category);
    return view->visibleCount;
}
