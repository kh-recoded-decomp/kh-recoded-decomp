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

extern void *GetMenuWidgetContainer(void);
extern void DrawEntryRowFrames(Ov082State *state);
extern EntryList *GetSlotEntry(int slot);
extern InputRepeat *GetMenuInputState(void);
extern void ScriptCmd_ResetScreenLayer(ScrollList *list, void *layout);
extern void StepEntryListCursor(Ov082State *state);
extern void func_ov076_020c5c2c(void);
extern void RefreshEntryRows(Ov082State *state);

void UpdateOv082EntryList(Ov082State *state)
{
    void *layout = GetMenuWidgetContainer();
    s16 previous = state->list.slotIndex;

    if (state->needsRedraw) {
        state->needsRedraw = 0;
        DrawEntryRowFrames(state);
    }
    if (state->list.slotIndex == 1
        && GetSlotEntry(0)->kind == 2
        && ((data_020604fc & 0x40) || (data_020604fc & 0x20))
        && !(data_02060500 & 0x40)) {
        GetMenuInputState()->flags &= ~0x60;
    }
    ScriptCmd_ResetScreenLayer(&state->list, layout);
    StepEntryListCursor(state);
    if (state->list.slotIndex == previous) {
        return;
    }
    state->needsRedraw = 1;
    func_ov076_020c5c2c();
    RefreshEntryRows(state);
}
