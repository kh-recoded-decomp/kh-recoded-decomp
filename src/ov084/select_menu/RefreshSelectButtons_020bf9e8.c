#include "nitro/types.h"

typedef struct ButtonRecord {
    u16 id;
    s16 x;
    s16 y;
} ButtonRecord;

typedef struct SelectMenu {
    u8 selection;
    u8 pad1[0xaf];
    void *records;
    ButtonRecord *buttons[2];
    void *cursor;
} SelectMenu;

extern void apply_all_pending_entry_edits_020b84f4(void *records, void *cursor, int x, int y);
extern void func_ov027_020b845c(void *records, void *cursor);
extern void TagTracker_InvokeCallback_020b8210(void *pool, void *record);

void RefreshSelectButtons_020bf9e8(SelectMenu *menu)
{
    s16 i;

    for (i = 0; i < 2; i++) {
        if (i == menu->selection) {
            apply_all_pending_entry_edits_020b84f4(menu->records, menu->cursor, menu->buttons[i]->x, menu->buttons[i]->y);
            func_ov027_020b845c(menu->records, menu->cursor);
        } else {
            TagTracker_InvokeCallback_020b8210(menu->records, menu->buttons[i]);
        }
    }
}
