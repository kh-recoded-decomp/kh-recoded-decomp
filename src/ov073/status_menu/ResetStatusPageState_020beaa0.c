#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScrollList {
    s16 itemCount;
    s16 cursor;
    s16 topIndex;
    u8 scrollOffset;
    u8 pad_07[0xd4 - 0x07];
} ScrollList;

typedef struct StatusMenu {
    s8 page;
    u8 pad_01[2];
    u8 flags;
    u8 pad_04[0x10 - 0x04];
    s16 lastCursor;
    u8 pad_12[2];
    BOOL active;
    u8 pad_18[0xdc0 - 0x18];
    u8 textLayer[0x10f4 - 0xdc0];
    ScrollList list;
    s16 dragIndex;
    s16 dragTarget;
    u8 strings[1];
} StatusMenu;

extern void *func_ov039_020bc1cc(void);
extern void *FindWidgetById_020b90a4(void *container, int id);
extern void func_ov027_020b96a0(void *container, void *element, int frame);
extern void func_ov027_020b91c8(void *container, void *element, fx32 *position, int mode);
extern void CallVirtualHandlerSlot1_02001574(void *context, int arg);
extern u16 *func_ov027_020ba2a8(void *table, int index);
extern void *func_ov039_020bc9ac(void);
extern void func_0200160c(void *layer, int x, int y, int color, u32 flags, const u16 *text, void *fallbackFont, int maxWidth);
extern void FlushBufferAndRunCallback_0200153c(void *context);

void ResetStatusPageState_020beaa0(StatusMenu *menu)
{
    void *container = func_ov039_020bc1cc();
    fx32 position[2];
    BOOL active;
    u16 *title;

    position[0] = menu->page << 16;
    func_ov027_020b96a0(container, FindWidgetById_020b90a4(container, 0xb), menu->page);
    func_ov027_020b91c8(container, FindWidgetById_020b90a4(container, 2), position, 4);
    active = TRUE;
    if ((menu->flags & 1) == 0 && (menu->flags != 2 || menu->page == 0)) {
        active = FALSE;
    }
    menu->active = active;
    menu->lastCursor = -1;
    menu->list.cursor = 0;
    menu->list.topIndex = 0;
    menu->list.scrollOffset = 0;
    menu->dragIndex = -1;
    menu->dragTarget = -1;
    if (menu->page != 4) {
        CallVirtualHandlerSlot1_02001574(menu->textLayer, 0);
        title = func_ov027_020ba2a8(menu->strings, menu->page + 1);
        func_0200160c(menu->textLayer, 0, 5, 2, 8, title, func_ov039_020bc9ac(), 0x4c);
        FlushBufferAndRunCallback_0200153c(menu->textLayer);
    }
}
