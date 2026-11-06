#pragma opt_propagation off

#include "src/overlays/ov013/Ov013PanelState.h"
#include "nitro/fx.h"

extern void SetScrollListPixels(PanelScrollList *list, int pixels, BOOL keepCursor);
extern void PositionOv013CursorWidget(void);
extern void SetEntrySlotsVisible(int root, int *widget, int visible);
extern WidgetPositionRecord *FindWidgetById(void *root, int id);
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
    state = gOv013PanelGlobals;
    offset = state->scrollOffset + state->animationOffset;
    remainder = offset % state->rowHeight;
    if (state->moveCursorWithScroll) {
        keepCursor = FALSE;
    }
    SetScrollListPixels(&state->list, -offset, keepCursor);
    PositionOv013CursorWidget();

    slot = 0;
    span = gOv013PanelGlobals->list.itemCount - gOv013PanelGlobals->list.scrollOffset;
    if (gOv013PanelGlobals->list.scrollOffset == 0) {
        slot = 1;
        SetEntrySlotsVisible((int)gOv013PanelGlobals->widgets, (int *)gOv013PanelGlobals->frames[0], 0);
        SetEntrySlotsVisible((int)gOv013PanelGlobals->widgets, (int *)gOv013PanelGlobals->icons[0], 0);
        SetEntrySlotsVisible((int)gOv013PanelGlobals->widgets, (int *)gOv013PanelGlobals->digits[0], 0);
        SetEntrySlotsVisible((int)gOv013PanelGlobals->widgets, (int *)gOv013PanelGlobals->digits[1], 0);
        SetEntrySlotsVisible((int)gOv013PanelGlobals->widgets, (int *)gOv013PanelGlobals->digits[2], 0);
        widgets = gOv013PanelGlobals->widgets;
        widget = FindWidgetById(widgets, 200);
        SetEntrySlotsVisible((int)widgets, (int *)widget, 0);
        widgets = gOv013PanelGlobals->widgets;
        widget = FindWidgetById(widgets, 100);
        SetEntrySlotsVisible((int)widgets, (int *)widget, 0);
    }
    for (; slot < 9; slot++) {
        if (slot < span + 1) {
            SetEntrySlotsVisible((int)gOv013PanelGlobals->widgets, (int *)gOv013PanelGlobals->frames[slot], 1);
            position = gOv013PanelGlobals->framePositions[slot];
            position.y += remainder * FX32_ONE;
            SetWidgetPosition(gOv013PanelGlobals->widgets, gOv013PanelGlobals->frames[slot], &position, 0);
            SetEntrySlotsVisible((int)gOv013PanelGlobals->widgets, (int *)gOv013PanelGlobals->icons[slot], 1);
            position = gOv013PanelGlobals->iconPositions[slot];
            position.y += remainder * FX32_ONE;
            SetWidgetPosition(gOv013PanelGlobals->widgets, gOv013PanelGlobals->icons[slot], &position, 0);
            digitBase = slot * 3;
            SetEntrySlotsVisible((int)gOv013PanelGlobals->widgets, (int *)gOv013PanelGlobals->digits[digitBase], 1);
            ResolveWidgetPositionComponents(gOv013PanelGlobals->widgets, gOv013PanelGlobals->digits[digitBase], &position, 0);
            position.y = gOv013PanelGlobals->digitPositions[slot].y + (remainder * FX32_ONE);
            SetWidgetPosition(gOv013PanelGlobals->widgets, gOv013PanelGlobals->digits[digitBase], &position, 0);
            SetEntrySlotsVisible((int)gOv013PanelGlobals->widgets, (int *)gOv013PanelGlobals->digits[digitBase + 1], 1);
            ResolveWidgetPositionComponents(gOv013PanelGlobals->widgets, gOv013PanelGlobals->digits[digitBase + 1], &position, 0);
            position.y = gOv013PanelGlobals->digitPositions[slot].y + (remainder * FX32_ONE);
            SetWidgetPosition(gOv013PanelGlobals->widgets, gOv013PanelGlobals->digits[digitBase + 1], &position, 0);
            SetEntrySlotsVisible((int)gOv013PanelGlobals->widgets, (int *)gOv013PanelGlobals->digits[digitBase + 2], 1);
            ResolveWidgetPositionComponents(gOv013PanelGlobals->widgets, gOv013PanelGlobals->digits[digitBase + 2], &position, 0);
            position.y = gOv013PanelGlobals->digitPositions[slot].y + (remainder * FX32_ONE);
            SetWidgetPosition(gOv013PanelGlobals->widgets, gOv013PanelGlobals->digits[digitBase + 2], &position, 0);
            widgets = gOv013PanelGlobals->widgets;
            widget = FindWidgetById(widgets, slot + 200);
            SetEntrySlotsVisible((int)widgets, (int *)widget, 1);
            state = gOv013PanelGlobals;
            position = state->labelPositions[slot];
            position.y += remainder * FX32_ONE;
            widgets = state->widgets;
            widget = FindWidgetById(widgets, slot + 200);
            SetWidgetPosition(widgets, widget, &position, 0);
            widgets = gOv013PanelGlobals->widgets;
            widget = FindWidgetById(widgets, slot + 100);
            SetEntrySlotsVisible((int)widgets, (int *)widget, 1);
            state = gOv013PanelGlobals;
            position = state->valuePositions[slot];
            position.y += remainder * FX32_ONE;
            widgets = state->widgets;
            widget = FindWidgetById(widgets, slot + 100);
            SetWidgetPosition(widgets, widget, &position, 0);
        } else {
            SetEntrySlotsVisible((int)gOv013PanelGlobals->widgets, (int *)gOv013PanelGlobals->frames[slot], 0);
            SetEntrySlotsVisible((int)gOv013PanelGlobals->widgets, (int *)gOv013PanelGlobals->icons[slot], 0);
            digitBase = slot * 3;
            SetEntrySlotsVisible((int)gOv013PanelGlobals->widgets, (int *)gOv013PanelGlobals->digits[digitBase], 0);
            SetEntrySlotsVisible((int)gOv013PanelGlobals->widgets, (int *)gOv013PanelGlobals->digits[digitBase + 1], 0);
            SetEntrySlotsVisible((int)gOv013PanelGlobals->widgets, (int *)gOv013PanelGlobals->digits[digitBase + 2], 0);
            widgets = gOv013PanelGlobals->widgets;
            widget = FindWidgetById(widgets, slot + 200);
            SetEntrySlotsVisible((int)widgets, (int *)widget, 0);
            widgets = gOv013PanelGlobals->widgets;
            widget = FindWidgetById(widgets, slot + 100);
            SetEntrySlotsVisible((int)widgets, (int *)widget, 0);
        }
    }
    RefreshPanelSlotDigits();
    RefreshProgressCaption();
}
