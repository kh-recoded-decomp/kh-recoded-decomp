#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s32 x;
    s32 y;
} PanelPos;

typedef struct {
    u8 pad_00[0x94];
    u32 unk94_0 : 1;
    u32 active : 1;
} Widget;

typedef struct {
    PanelPos pos;
    u8 pad_08[0x4ac - 8];
} SlotGroup;

typedef struct {
    u8 pad_0000[0xe0];
    u8 flags0 : 6;
    u8 noSlots : 1;
    u8 pad_00e1[0x6ac0 - 0xe1];
    u8 container[0xd0a8 - 0x6ac0];
    SlotGroup groups[3];
    s32 baseY[3];
    s32 angles[3];
} PanelState;

extern PanelState *data_ov015_0207e960;
extern const s16 data_0205356c[];
extern s64 LongDivide_02023ba4(s64 numerator, s64 denominator);
extern Widget *FindWidgetById_020b90a4(void *root, int id);
extern BOOL IsWidgetMoveFinished_020b9100(Widget *widget);
extern void SetEntrySlotsVisible_020b9580(void *root, Widget *widget, int visible);
extern void ResetGroupSlotsPosition_020680a4(void *manager, PanelPos *pos);
extern void func_ov027_020b9360(void *container, Widget *widget, PanelPos *pos, int flag);
extern void func_ov027_020b91c8(void *container, Widget *widget, PanelPos *pos, int flag);

void BobPanelWidgets_0206f7d8(void) {
    PanelPos pos;
    PanelState *state;
    Widget *widget;
    int i;
    int degrees;
    fx32 fixed;
    s64 radians;
    int index;
    s32 offset;
    void *container;

    for (i = 0; i < 3; i++) {
        widget = FindWidgetById_020b90a4(data_ov015_0207e960->container, i + 1);
        if (widget == NULL || !widget->active) {
            continue;
        }
        if (IsWidgetMoveFinished_020b9100(widget)) {
            data_ov015_0207e960->angles[i] += 4;
            data_ov015_0207e960->angles[i] %= 360;
            state = data_ov015_0207e960;
            degrees = state->angles[i];
            if (degrees > 0) {
                fixed = 0.5f + (float)(degrees << 12);
            } else {
                fixed = (float)(degrees << 12) - 0.5f;
            }
            radians = LongDivide_02023ba4((s64)fixed * 0x3244, 0xb4000);
            index = LongDivide_02023ba4(radians << 16, 0x6488) & 0xffff;
            func_ov027_020b9360(state->container, widget, &pos, 0);
            index >>= 4;
            offset = (s32)(((s64)data_0205356c[index] * 2 + 0x800) >> 12) << 12;
            pos.y = data_ov015_0207e960->baseY[i] + offset;
            func_ov027_020b91c8(data_ov015_0207e960->container, widget, &pos, 0);
            state = data_ov015_0207e960;
            if (!state->noSlots) {
                container = state->container;
                SetEntrySlotsVisible_020b9580(container, FindWidgetById_020b90a4(container, i + 10), 1);
            }
        }
        func_ov027_020b9360(data_ov015_0207e960->container, widget, &pos, 0);
        state = data_ov015_0207e960;
        pos.x -= 0x5000;
        pos.y -= 0x2d000;
        state->groups[i].pos = pos;
        ResetGroupSlotsPosition_020680a4(state->container, &state->groups[i].pos);
    }
}
