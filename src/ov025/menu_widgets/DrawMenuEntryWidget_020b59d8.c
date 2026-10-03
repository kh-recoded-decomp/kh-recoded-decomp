#include "nitro/types.h"

typedef struct MenuEntry {
    u8 pad_00[0x10];
    int widgetId;
} MenuEntry;

extern u8 *data_ov025_020b7760;
extern void *func_ov001_0207123c(void);
extern void func_ov027_020b9a74(void *widget, MenuEntry *entry);

void DrawMenuEntryWidget_020b59d8(MenuEntry *entry) {
    switch (entry->widgetId) {
    case 0x1a:
    case 0x1b:
        func_ov027_020b9a74(data_ov025_020b7760 + 0x64c8, entry);
        break;
    default:
        func_ov027_020b9a74(func_ov001_0207123c(), entry);
        break;
    }
}
