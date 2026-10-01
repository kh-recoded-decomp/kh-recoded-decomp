#include "nitro/types.h"

typedef struct MenuEntry {
    u16 itemId;
    u16 unk_02;
    u16 unk_04;
} MenuEntry;

typedef struct MenuState {
    u8 pad_00[0xb4];
    MenuEntry entries[1];
} MenuState;

extern MenuState *data_ov001_020a04ac;
extern void func_ov001_020747fc(int index, int x, int y, int redraw, int arg4, int arg5);

void RefreshActiveMenuEntry_02074f7c(int index, int x, int y)
{
    if (data_ov001_020a04ac->entries[index].itemId != 0) {
        func_ov001_020747fc(index, x, y, 1, 0, 0);
    }
}
