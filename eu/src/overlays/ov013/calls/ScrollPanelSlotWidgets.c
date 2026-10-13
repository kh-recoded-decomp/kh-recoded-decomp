#pragma opt_propagation off

#include "src/overlays/ov013/Ov013PanelState.h"
#include "nitro/fx.h"

extern void SetScrollListPixels(PanelScrollList *list, int pixels, BOOL keepCursor);
extern void func_ov013_0206fbbc(void);
extern void SetEntrySlotsVisible(int root, int *widget, int visible);
extern WidgetPositionRecord *FindWidgetById(void *root, int id);
extern void func_ov027_020b91e8(void *root, WidgetPositionRecord *widget,
                                const WidgetPoint *point, int mode);
extern void RefreshPanelSlotDigits(void);
extern void RefreshProgressCaption(void);

void ScrollPanelSlotWidgets(void)
{
    int slot;
    int span;
    int offset;
    int remainder;
    int digitBase;
    BOOL keepCursor;
    WidgetPoint position;
    Ov013PanelState *state;
    void *widgets;
    WidgetPositionRecord *widget;

    keepCursor = TRUE;
    state = data_ov013_02074ce0;
    offset = state->scrollOffset + state->animationOffset;
    remainder = offset % state->rowHeight;
    if (state->moveCursorWithScroll) {
        keepCursor = FALSE;
    }
    SetScrollListPixels(&state->list, -offset, keepCursor);
    func_ov013_0206fbbc();

    slot = 0;
    span = data_ov013_02074ce0->list.itemCount - data_ov013_02074ce0->list.scrollOffset;
    if (data_ov013_02074ce0->list.scrollOffset == 0) {
        slot = 1;
        SetEntrySlotsVisible((int)data_ov013_02074ce0->widgets, (int *)data_ov013_02074ce0->frames[0], 0);
        SetEntrySlotsVisible((int)data_ov013_02074ce0->widgets, (int *)data_ov013_02074ce0->icons[0], 0);
        SetEntrySlotsVisible((int)data_ov013_02074ce0->widgets, (int *)data_ov013_02074ce0->digits[0], 0);
        SetEntrySlotsVisible((int)data_ov013_02074ce0->widgets, (int *)data_ov013_02074ce0->digits[1], 0);
        SetEntrySlotsVisible((int)data_ov013_02074ce0->widgets, (int *)data_ov013_02074ce0->digits[2], 0);
        widgets = data_ov013_02074ce0->widgets;
        widget = FindWidgetById(widgets, 200);
        SetEntrySlotsVisible((int)widgets, (int *)widget, 0);
        widgets = data_ov013_02074ce0->widgets;
        widget = FindWidgetById(widgets, 100);
        SetEntrySlotsVisible((int)widgets, (int *)widget, 0);
    }
    for (; slot < 9; slot++) {
        if (slot < span + 1) {
            SetEntrySlotsVisible((int)data_ov013_02074ce0->widgets, (int *)data_ov013_02074ce0->frames[slot], 1);
            position = data_ov013_02074ce0->framePositions[slot];
            position.y += remainder * FX32_ONE;
            func_ov027_020b91e8(data_ov013_02074ce0->widgets, data_ov013_02074ce0->frames[slot], &position, 0);
            SetEntrySlotsVisible((int)data_ov013_02074ce0->widgets, (int *)data_ov013_02074ce0->icons[slot], 1);
            position = data_ov013_02074ce0->iconPositions[slot];
            position.y += remainder * FX32_ONE;
            func_ov027_020b91e8(data_ov013_02074ce0->widgets, data_ov013_02074ce0->icons[slot], &position, 0);
            digitBase = slot * 3;
            SetEntrySlotsVisible((int)data_ov013_02074ce0->widgets, (int *)data_ov013_02074ce0->digits[digitBase], 1);
            ResolveWidgetPositionComponents(data_ov013_02074ce0->widgets, data_ov013_02074ce0->digits[digitBase], &position, 0);
            position.y = data_ov013_02074ce0->digitPositions[slot].y + (remainder * FX32_ONE);
            func_ov027_020b91e8(data_ov013_02074ce0->widgets, data_ov013_02074ce0->digits[digitBase], &position, 0);
            SetEntrySlotsVisible((int)data_ov013_02074ce0->widgets, (int *)data_ov013_02074ce0->digits[digitBase + 1], 1);
            ResolveWidgetPositionComponents(data_ov013_02074ce0->widgets, data_ov013_02074ce0->digits[digitBase + 1], &position, 0);
            position.y = data_ov013_02074ce0->digitPositions[slot].y + (remainder * FX32_ONE);
            func_ov027_020b91e8(data_ov013_02074ce0->widgets, data_ov013_02074ce0->digits[digitBase + 1], &position, 0);
            SetEntrySlotsVisible((int)data_ov013_02074ce0->widgets, (int *)data_ov013_02074ce0->digits[digitBase + 2], 1);
            ResolveWidgetPositionComponents(data_ov013_02074ce0->widgets, data_ov013_02074ce0->digits[digitBase + 2], &position, 0);
            position.y = data_ov013_02074ce0->digitPositions[slot].y + (remainder * FX32_ONE);
            func_ov027_020b91e8(data_ov013_02074ce0->widgets, data_ov013_02074ce0->digits[digitBase + 2], &position, 0);
            widgets = data_ov013_02074ce0->widgets;
            widget = FindWidgetById(widgets, slot + 200);
            SetEntrySlotsVisible((int)widgets, (int *)widget, 1);
            state = data_ov013_02074ce0;
            position = state->labelPositions[slot];
            position.y += remainder * FX32_ONE;
            widgets = state->widgets;
            widget = FindWidgetById(widgets, slot + 200);
            func_ov027_020b91e8(widgets, widget, &position, 0);
            widgets = data_ov013_02074ce0->widgets;
            widget = FindWidgetById(widgets, slot + 100);
            SetEntrySlotsVisible((int)widgets, (int *)widget, 1);
            state = data_ov013_02074ce0;
            position = state->valuePositions[slot];
            position.y += remainder * FX32_ONE;
            widgets = state->widgets;
            widget = FindWidgetById(widgets, slot + 100);
            func_ov027_020b91e8(widgets, widget, &position, 0);
        } else {
            SetEntrySlotsVisible((int)data_ov013_02074ce0->widgets, (int *)data_ov013_02074ce0->frames[slot], 0);
            SetEntrySlotsVisible((int)data_ov013_02074ce0->widgets, (int *)data_ov013_02074ce0->icons[slot], 0);
            digitBase = slot * 3;
            SetEntrySlotsVisible((int)data_ov013_02074ce0->widgets, (int *)data_ov013_02074ce0->digits[digitBase], 0);
            SetEntrySlotsVisible((int)data_ov013_02074ce0->widgets, (int *)data_ov013_02074ce0->digits[digitBase + 1], 0);
            SetEntrySlotsVisible((int)data_ov013_02074ce0->widgets, (int *)data_ov013_02074ce0->digits[digitBase + 2], 0);
            widgets = data_ov013_02074ce0->widgets;
            widget = FindWidgetById(widgets, slot + 200);
            SetEntrySlotsVisible((int)widgets, (int *)widget, 0);
            widgets = data_ov013_02074ce0->widgets;
            widget = FindWidgetById(widgets, slot + 100);
            SetEntrySlotsVisible((int)widgets, (int *)widget, 0);
        }
    }
    RefreshPanelSlotDigits();
    RefreshProgressCaption();
}
