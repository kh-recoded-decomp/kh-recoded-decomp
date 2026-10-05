#include "nitro/types.h"

typedef struct PanelWidget {
    u8 pad_00[0x94];
    u32 flag0 : 1;
    u32 hidden : 1;
    u32 flagRest : 30;
} PanelWidget;

typedef struct PanelCursorState {
    u8 pad_000[9];
    s8 blinkTimer;
    u8 pad_00a[0x90];
    u8 layout : 2;
    u8 layoutRest : 6;
    u8 pad_09b[0x255];
    s8 selection;
    u8 pad_2f1[0xab];
    u8 widgets[4];
} PanelCursorState;

extern PanelCursorState *data_ov013_02074ce0;
extern PanelWidget *FindWidgetById_020b90a4(void *container, int id);
extern void func_ov027_020b9360(void *container, PanelWidget *widget, s32 *position, int flag);
extern void func_ov027_020b91c8(void *container, PanelWidget *widget, s32 *position, int flag);
extern void SetEntrySlotsVisible_020b9580(void *container, PanelWidget *widget, int visible);

void BlinkPanelCursor_02071454(void)
{
    s32 position[2];
    PanelCursorState *state = data_ov013_02074ce0;
    int id = 8;
    PanelWidget *widget;
    u8 *widgets;

    if (state->layout == 2) {
        id = 4;
    }
    func_ov027_020b9360(state->widgets, FindWidgetById_020b90a4(state->widgets, id), position, 0);
    position[0] += 0x1000;
    widgets = data_ov013_02074ce0->widgets;
    func_ov027_020b91c8(widgets, FindWidgetById_020b90a4(widgets, id), position, 0);
    if ((data_ov013_02074ce0->selection + 1) % 10 != 0) {
        data_ov013_02074ce0->blinkTimer++;
        if (data_ov013_02074ce0->blinkTimer > 15) {
            widget = FindWidgetById_020b90a4(data_ov013_02074ce0->widgets, id);
            if (widget != NULL) {
                if (widget->hidden) {
                    SetEntrySlotsVisible_020b9580(data_ov013_02074ce0->widgets, widget, FALSE);
                } else {
                    SetEntrySlotsVisible_020b9580(data_ov013_02074ce0->widgets, widget, TRUE);
                }
            }
            data_ov013_02074ce0->blinkTimer = 0;
        }
    } else {
        data_ov013_02074ce0->blinkTimer = 0;
    }
}
