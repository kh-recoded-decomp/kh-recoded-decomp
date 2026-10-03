#include "nitro/types.h"

typedef struct ListView {
    u8 pad_00[0x94];
    int scrollPos;
    int scrollTarget;
    BOOL scrolling;
    u8 pad_a0[4];
    int cursorIndex;
    int selectedIndex;
} ListView;

#define ABS(x) ((x) < 0 ? -(x) : (x))

extern void func_ov025_020b6e70(ListView *list);
extern void func_ov025_020b6f78(ListView *list, int input);
extern void func_ov025_020b6ca0(ListView *list, int entryIndex);
extern void func_ov025_020b6d00(ListView *list, int entryIndex);

void UpdateListScrollAnimation_020b7268(ListView *list, BOOL refresh, int input)
{
    int delta;

    if (refresh) {
        func_ov025_020b6e70(list);
    }
    func_ov025_020b6f78(list, input);
    if (list->scrolling) {
        delta = list->scrollTarget - list->scrollPos;
        if (ABS(delta) < 40) {
            list->scrollPos = list->scrollTarget;
            list->scrolling = FALSE;
        } else {
            list->scrollPos += (delta / ABS(delta)) * 40;
        }
        func_ov025_020b6ca0(list, list->selectedIndex);
        func_ov025_020b6d00(list, list->cursorIndex);
    }
}
