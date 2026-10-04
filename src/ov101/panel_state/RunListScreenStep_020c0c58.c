#include "nitro/types.h"

typedef struct {
    s32 listId;
    s32 itemCount;
    s32 visibleRows;
    s32 entryIndex;
    u8 pad_10[0x1C];
    s32 scroll;
    s32 cursor;
    u8 pad_34[0x18];
} ScrollPanel;

typedef struct {
    u8 pad_0000[0xCD64];
    ScrollPanel panels[2];
    u8 pad_CDFC[0xCFD0 - 0xCDFC];
    s32 step;
} Ov101State;

#define REG_DISPCNT (*(volatile u32 *)0x04000000)

extern void func_ov101_020c06c0(Ov101State *state);
extern void func_ov101_020c0578(Ov101State *state);
extern BOOL IsStateFlagSet_020c07a8(int setIndex, int bitIndex);
extern void func_ov101_020bfa6c(int listIndex, int entryIndex, int value, Ov101State *state);
extern void SetEntryAnimFrame_020bfcd0(int listIndex, int entryIndex, int frame, Ov101State *state);
extern void func_ov101_020bf634(int selection, Ov101State *state);
extern void SetStatePhase_020c0c18(s32 phase);

void RunListScreenStep_020c0c58(Ov101State *state)
{
    ScrollPanel *panel;
    int i;
    int scroll;
    int highlighted;
    int owned;
    u32 planes;

    switch (state->step) {
    case 0:
        planes = (REG_DISPCNT & 0x1F00) >> 8;
        REG_DISPCNT = (REG_DISPCNT & ~0x1F00) | ((planes & ~1) << 8);
        func_ov101_020c06c0(state);
        func_ov101_020c0578(state);
        state->step++;
        break;
    case 1:
        panel = &state->panels[0];
        for (i = 0; i < panel->itemCount; i++) {
            scroll = panel->scroll;
            highlighted = IsStateFlagSet_020c07a8(2, scroll + i) != 0;
            owned = IsStateFlagSet_020c07a8(1, scroll + i);
            func_ov101_020bfa6c(0, i + 3, owned, state);
            SetEntryAnimFrame_020bfcd0(0, i + 3, highlighted, state);
        }
        func_ov101_020bf634(-1, state);
        state->step++;
        break;
    case 2:
        planes = (REG_DISPCNT & 0x1F00) >> 8;
        REG_DISPCNT = (REG_DISPCNT & ~0x1F00) | ((planes | 1) << 8);
        SetStatePhase_020c0c18(0);
        break;
    }
}
