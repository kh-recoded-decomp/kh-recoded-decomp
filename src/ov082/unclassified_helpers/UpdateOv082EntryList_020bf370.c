#include "nitro/types.h"

typedef struct ScrollList {
    s16 count;
    s16 slotIndex;
    u8 pad_04[0x24];
} ScrollList;

typedef struct EntryList {
    u8 kind;
} EntryList;

typedef struct InputRepeat {
    u8 pad_00[0xa];
    u16 flags;
} InputRepeat;

typedef struct Ov082State {
    ScrollList list;
    u8 pad_0028[0x3708 - 0x28];
    int needsRedraw;
} Ov082State;

extern u16 data_020604fc;
extern u16 data_02060500;

extern void *func_ov039_020bc1cc(void);
extern void DrawEntryRowFrames_020bf260(Ov082State *state);
extern EntryList *GetSlotEntry_020c5438(int slot);
extern InputRepeat *func_ov039_020bca00(void);
extern void ScriptCmd_ResetScreenLayer_020be0c4(ScrollList *list, void *layout);
extern void func_ov082_020bf448(Ov082State *state);
extern void func_ov081_020c5c0c(void);
extern void func_ov082_020bef08(Ov082State *state);

void UpdateOv082EntryList_020bf370(Ov082State *state)
{
    void *layout = func_ov039_020bc1cc();
    s16 previous = state->list.slotIndex;

    if (state->needsRedraw) {
        state->needsRedraw = 0;
        DrawEntryRowFrames_020bf260(state);
    }
    if (state->list.slotIndex == 1 && GetSlotEntry_020c5438(0)->kind == 2
        && ((data_020604fc & 0x40) || (data_020604fc & 0x20)) && !(data_02060500 & 0x40)) {
        func_ov039_020bca00()->flags &= ~0x60;
    }
    ScriptCmd_ResetScreenLayer_020be0c4(&state->list, layout);
    func_ov082_020bf448(state);
    if (state->list.slotIndex == previous) {
        return;
    }
    state->needsRedraw = 1;
    func_ov081_020c5c0c();
    func_ov082_020bef08(state);
}
