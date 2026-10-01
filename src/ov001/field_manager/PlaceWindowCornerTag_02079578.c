#include "nitro/types.h"

typedef struct MessageWindow {
    u8 pad_00[0xc];
    BOOL hasBorder;
    u16 x;
    u16 y;
    u16 width;
    u16 height;
} MessageWindow;

extern void *GetSceneTagTracker_020711b0(void);
extern int func_ov027_020b8390(void *tracker, int tag);
extern void apply_all_pending_entry_edits_020b84f4(void *tracker, int entry, s16 x, s16 y);
extern void func_ov027_020b83e8(void *tracker, int entry, int visible);

void PlaceWindowCornerTag_02079578(MessageWindow *window)
{
    void *tracker = GetSceneTagTracker_020711b0();
    int margin = 0;
    int x;
    int y;
    int entry;

    if (window->hasBorder) {
        margin = 7;
    }
    x = window->x + window->width - margin - 3;
    y = window->y + window->height - 1;
    entry = func_ov027_020b8390(tracker, 5);
    apply_all_pending_entry_edits_020b84f4(tracker, entry, x, y);
    func_ov027_020b83e8(tracker, entry, 1);
}
