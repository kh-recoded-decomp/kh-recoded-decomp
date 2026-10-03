#include "nitro/types.h"

typedef struct TouchState {
    u8 pad_00[8];
    u16 state;
    u16 buttons;
} TouchState;

typedef struct StatusMenu {
    u8 unk_00;
    u8 dirty;
    u8 pad_02[0x10 - 0x02];
    s16 lastCursor;
    u8 pad_12[0x10e0 - 0x12];
    void *container;
    u8 pad_10e4[0x10f4 - 0x10e4];
    s16 itemCount;
    s16 cursor;
} StatusMenu;

extern TouchState *func_ov039_020bca00(void);
extern int func_ov039_020be0c4(s16 *list, void *owner);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);

int UpdateStatusListInput_020c0e38(StatusMenu *menu)
{
    int result;

    if (menu->itemCount <= 1) {
        result = -1;
    } else {
        result = func_ov039_020be0c4(&menu->itemCount, menu->container);
        if (menu->lastCursor != menu->cursor && (func_ov039_020bca00()->state & 3) == 1) {
            result = 2;
        }
        menu->lastCursor = menu->cursor;
    }
    switch (result) {
    case -1:
        return 0;
    case 2:
        PlaySoundEffect_0204d924(0, 0);
    case 1:
        menu->dirty = TRUE;
        break;
    }
    if ((func_ov039_020bca00()->buttons & 0xf0) != 0) {
        menu->dirty = TRUE;
    }
    return 0;
}
