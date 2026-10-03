#include "nitro/types.h"

typedef struct ListView {
    u8 pad_00[0x94];
    int scrollX;
    int targetX;
    BOOL scrolling;
    u8 pad_a0[4];
    int cursorIndex;
    int selectedIndex;
} ListView;

extern void func_ov073_020c38e8(ListView *list);
extern void func_ov073_020c39f0(ListView *list, int input);
extern void SelectListEntry_020c3718(ListView *list, int entryIndex);
extern void PlaceCursorAtListEntry_020c3778(ListView *list, int entryIndex);

void UpdateListScroll_020c3ce0(ListView *list, BOOL refresh, int input)
{
    int delta;
    int distance;

    if (refresh) {
        func_ov073_020c38e8(list);
    }
    func_ov073_020c39f0(list, input);
    if (list->scrolling) {
        delta = list->targetX - list->scrollX;
        distance = delta < 0 ? -delta : delta;
        if (distance < 40) {
            list->scrollX = list->targetX;
            list->scrolling = FALSE;
        } else {
            list->scrollX += delta / (delta < 0 ? -delta : delta) * 40;
        }
        SelectListEntry_020c3718(list, list->selectedIndex);
        PlaceCursorAtListEntry_020c3778(list, list->cursorIndex);
    }
}
