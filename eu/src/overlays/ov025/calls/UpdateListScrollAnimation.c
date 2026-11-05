#include "src/overlays/ov025/SlotListTouch.h"

#define ABS(x) ((x) < 0 ? -(x) : (x))

extern void HandleListInput(ListTouchView *list, u32 keys);
extern void SetListHighlightEntry(ListTouchView *list, int index);
extern void SetListCursorEntry(ListTouchView *list, int index);

void UpdateListScrollAnimation(ListTouchView *list, const ListTouchInput *touch,
                               u32 keys)
{
    int delta;

    if (touch) {
        HandleListTouch(list, touch);
    }
    HandleListInput(list, keys);
    if (list->scrolling) {
        delta = list->scrollTarget - list->scrollPos;
        if (ABS(delta) < 40) {
            list->scrollPos = list->scrollTarget;
            list->scrolling = FALSE;
        } else {
            list->scrollPos += (delta / ABS(delta)) * 40;
        }
        SetListHighlightEntry(list, list->selectedIndex);
        SetListCursorEntry(list, list->cursorIndex);
    }
}
