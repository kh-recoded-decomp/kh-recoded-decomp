#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x2C];
    s32 scroll;
    s32 cursor;
} ScrollPanel;

typedef struct {
    s32 selection;
    u8 pad_0004[0xCACC - 4];
    ScrollPanel panel;
} Ov103State;

extern int func_ov103_020c030c(Ov103State *state);
extern BOOL func_ov103_020bfc00(int panelIndex, Ov103State *state);
extern void func_ov103_020bf0a4(Ov103State *state);
extern void func_ov103_020bf39c(int which, Ov103State *state);
extern void RefreshRowHighlights_020bf92c(Ov103State *state);
extern void PlaySoundEffect_0204d924(int soundId, int arg);

void HandleListScrollDown_020bebc4(Ov103State *state)
{
    ScrollPanel *panel;

    if (func_ov103_020c030c(state) != 3) {
        return;
    }
    if (!func_ov103_020bfc00(0, state)) {
        return;
    }
    panel = &state->panel;
    state->selection = panel->scroll + panel->cursor;
    func_ov103_020bf0a4(state);
    func_ov103_020bf39c(0, state);
    RefreshRowHighlights_020bf92c(state);
    PlaySoundEffect_0204d924(0, 0);
}
