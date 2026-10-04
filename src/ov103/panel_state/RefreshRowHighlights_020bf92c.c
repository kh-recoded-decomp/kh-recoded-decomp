#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x2C];
    s32 scroll;
} ScrollPanel;

typedef struct {
    u8 pad_0000[0xCACC];
    ScrollPanel panel;
} Ov103State;

extern BOOL IsEntryFlagSet_020c0180(int flagSet, int entryIndex);
extern void SetSlotEntryVisible_020bf678(int listIndex, int entryIndex, int visible, Ov103State *state);

void RefreshRowHighlights_020bf92c(Ov103State *state)
{
    ScrollPanel *panel = &state->panel;
    int i;

    for (i = 0; i < 9; i++) {
        if (IsEntryFlagSet_020c0180(1, i + panel->scroll)) {
            SetSlotEntryVisible_020bf678(0, i + 3, 1, state);
        } else {
            SetSlotEntryVisible_020bf678(0, i + 3, 0, state);
        }
    }
}
