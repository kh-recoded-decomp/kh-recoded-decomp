#include "nitro/types.h"

typedef struct ItemStatus {
    u8 pad_00[8];
    int value;
} ItemStatus;

typedef struct ItemSlot {
    u8 pad_00[8];
    ItemStatus *status;
} ItemSlot;

typedef struct ItemMenu {
    u8 pad_00[2];
    u8 useCatalog;
    u8 pad_03[0x5a49];
    ItemSlot *slots[1];
} ItemMenu;

extern void *GetItemMenuEntry_020bf72c(ItemMenu *menu, int index);
extern int func_ov085_020c1304(void *entry);
extern int OS_SNPrintf_0202e080(char *dst, u32 len, const char *fmt, ...);
extern const char data_ov085_020c239c[];

char *FormatItemValue_020c1354(ItemMenu *menu, int index, char *buffer)
{
    int value;

    if (menu->useCatalog) {
        value = func_ov085_020c1304(GetItemMenuEntry_020bf72c(menu, index));
    } else {
        value = menu->slots[index]->status->value;
    }
    OS_SNPrintf_0202e080(buffer, 0x2e, data_ov085_020c239c, value);
    return buffer;
}
