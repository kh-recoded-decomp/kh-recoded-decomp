#include "src/overlays/ov073/ListView.h"

extern void HandleListCursorInput(ListView *list, int input);
extern void SelectListEntry(ListView *list, int index);
extern void PlaceCursorAtListEntry(ListView *list, int index);

void UpdateListScroll(ListView *list, const ListTouchSample *touch, u16 input)
{
    int delta;
    int distance;

    if (touch != NULL) {
        HandleListTouchInput(list, touch);
    }
    HandleListCursorInput(list, input);
    if (list->scrolling) {
        delta = list->targetX - list->scrollX;
        distance = delta < 0 ? -delta : delta;
        if (distance < 40) {
            list->scrollX = list->targetX;
            list->scrolling = FALSE;
        } else {
            list->scrollX += delta / (delta < 0 ? -delta : delta) * 40;
        }
        SelectListEntry(list, list->selectedIndex);
        PlaceCursorAtListEntry(list, list->cursorIndex);
    }
}
