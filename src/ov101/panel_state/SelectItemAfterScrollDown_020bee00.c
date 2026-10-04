#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x2C];
    s32 cursorIndex;
    s32 scrollOffset;
} ListCursor;

typedef struct {
    s32 selectedItem;
    u8 pad_0004[0xCD64 - 0x4];
    ListCursor cursor;
} Ov101State;

extern BOOL ScrollPanelCursorDown_020c0134(int panelIndex, Ov101State *state);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);
extern BOOL IsStateFlagSet_020c07a8(int setIndex, int bitIndex);
extern void *func_ov101_020c07d4(int index, int arg2);
extern void SetGlobalPackedBit_02027320(int bitIndex);
extern void SetStatePhase_020c0c18(s32 phase);

void SelectItemAfterScrollDown_020bee00(Ov101State *state)
{
    ListCursor *cursor;
    int item;

    if (!ScrollPanelCursorDown_020c0134(0, state)) {
        return;
    }
    cursor = &state->cursor;
    state->selectedItem = cursor->cursorIndex + cursor->scrollOffset;
    PlaySoundEffect_0204d924(0, 0);
    item = state->selectedItem;
    if (IsStateFlagSet_020c07a8(1, item)) {
        func_ov101_020c07d4(2, item);
        SetGlobalPackedBit_02027320(item + 0x1272);
    }
    SetStatePhase_020c0c18(1);
}
