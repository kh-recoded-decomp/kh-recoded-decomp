#include "nitro/types.h"

typedef struct ScrollList {
    s16 count;
    s16 slotIndex;
    s16 topSlot;
    u8 pad_06;
    u8 visibleCount;
    u8 rowHeight;
    u8 pad_09[3];
    s32 wrapUp;
    s32 wrapDown;
    u8 pad_14[4];
    s32 repeatEnabled;
    u8 pad_1C[2];
    s16 offsetY;
    u8 pad_20[4];
    s16 cursorX;
    s16 cursorWidth;
} ScrollList;

typedef struct Ov081State {
    u8 pad_00[0x63c3];
    u8 visibleCount;
    u8 shownCount;
} Ov081State;

typedef struct Ov082State {
    ScrollList list;
    u8 pad_0028[0x3708 - 0x28];
    int pendingAction;
} Ov082State;

extern Ov082State *gOv082State;

extern void *GetMenuWidgetContainer(void);
extern Ov081State *func_ov081_020c5bf8(void);
extern void func_ov034_020bdea4(ScrollList *list, void *layout, int elementId, int arg3, int arg4, int arg5, int arg6,
                                int arg7, int arg8);
extern void ScriptCmd_ResetScreenLayer(ScrollList *list, void *layout);
extern void SetupOv082Screen(Ov082State *state);
extern void AdvanceListAndRedraw(void);

BOOL InitOv082EntryList(Ov082State *state)
{
    void *layout = GetMenuWidgetContainer();
    Ov081State *source = func_ov081_020c5bf8();

    gOv082State = state;
    state->list.count = source->visibleCount;
    state->list.visibleCount = source->shownCount;
    state->list.offsetY = -0x10;
    state->list.cursorX = 0;
    state->list.cursorWidth = 0;
    state->list.wrapDown = 0;
    func_ov034_020bdea4(&state->list, layout, 1, 10, 0x10, 1, 0x10, 0, 0);
    ScriptCmd_ResetScreenLayer(&state->list, layout);
    state->pendingAction = 0;
    SetupOv082Screen(state);
    AdvanceListAndRedraw();
    return TRUE;
}
