#include "nitro/types.h"

typedef struct MenuInputState {
    u8 pad_00[8];
    u16 state;
    u16 buttons;
} MenuInputState;

typedef struct StatusPanelState {
    u8 unk_00;
    u8 dirty;
    u8 pad_02[0x10 - 0x02];
    s16 lastCursor;
    u8 pad_12[0x10e0 - 0x12];
    void *container;
    u8 pad_10e4[0x10f4 - 0x10e4];
    s16 itemCount;
    s16 cursor;
} StatusPanelState;

extern MenuInputState *GetMenuInputState(void);
extern int UpdateScrollListInput(s16 *list, void *owner);
extern BOOL PlaySoundEffect(int seqArcNo, int index);

int UpdateStatusPanelInput(StatusPanelState *panel)
{
    int input;
    int result;

    if (panel->itemCount <= 1) {
        result = -1;
    } else {
        result = UpdateScrollListInput(&panel->itemCount, panel->container);
        if (panel->lastCursor != panel->cursor &&
            (input = (int)GetMenuInputState(), (*(u16 *)(input + 8) & 3) == 1)) {
            result = 2;
        }
        panel->lastCursor = panel->cursor;
    }
    if (result != 1) {
        if (result != 2) {
            goto check_buttons;
        }
        PlaySoundEffect(0, 0);
    }
    panel->dirty = TRUE;

check_buttons:
    input = (int)GetMenuInputState();
    if ((*(u16 *)(input + 10) & 0xf0) != 0) {
        panel->dirty = TRUE;
    }
    return 0;
}
