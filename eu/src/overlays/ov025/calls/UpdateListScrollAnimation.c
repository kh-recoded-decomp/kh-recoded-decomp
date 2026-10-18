#include "src/overlays/ov025/SlotListTouch.h"

#define ABS(x) ((x) < 0 ? -(x) : (x))

extern void HandleListInput(ListTouchView *list, u32 keys);
extern void func_ov025_020b6cc0(ListTouchView *list, int index);
extern void func_ov025_020b6d20(ListTouchView *list, int index);

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
        func_ov025_020b6cc0(list, list->selectedIndex);
        func_ov025_020b6d20(list, list->cursorIndex);
    }
}
