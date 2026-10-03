#include "nitro/types.h"

typedef struct ResourceContainer ResourceContainer;

typedef struct ScrollList {
    s16 itemCount;
    u8 pad_02[0x22];
    s16 trackHeight;
} ScrollList;

typedef struct StatusMenu {
    s8 mode;
    u8 pad_01;
    u8 refreshCount;
    u8 flags;
    u8 pad_04[0x10];
    BOOL busy;
    u8 pad_0018[0xe9c - 0x18];
    u16 headerCursor;
    u8 pad_0e9e[0xfbc - 0xe9e];
    char headerText[0x70];
    u8 pad_102c[0x10e0 - 0x102c];
    ResourceContainer *container;
    u8 pad_10e4[0x10];
    ScrollList scroll;
    u8 pad_111a[0x11cc - 0x111a];
    u8 strings[1];
} StatusMenu;

extern const char data_ov073_020c4180[];
extern void SetupScrollList_020bdf10(ScrollList *list, ResourceContainer *container, BOOL enabled);
extern void SetStatusElementVisible_020beb5c(int elementId, BOOL visible);
extern void *func_ov027_020ba2a8(void *table, int index);
extern int OS_SNPrintf_0202e080(void *dst, u32 len, const char *fmt, ...);
extern void ShowStatusPageContents_020c1b28(StatusMenu *menu);

void OpenStatusPageView_020bfefc(StatusMenu *menu)
{
    menu->scroll.trackHeight = 0xe8;
    SetupScrollList_020bdf10(&menu->scroll, menu->container, FALSE);
    SetStatusElementVisible_020beb5c(0xc, TRUE);
    if (menu->flags & 1) {
        menu->headerCursor = 0;
        OS_SNPrintf_0202e080(menu->headerText, 0x70, data_ov073_020c4180, func_ov027_020ba2a8(menu->strings, 0));
        menu->refreshCount = 1;
    }
    if (menu->busy == 0) {
        ShowStatusPageContents_020c1b28(menu);
    }
}
