#include "src/overlays/ov073/ListView.h"

#pragma opt_common_subs off

extern int func_ov001_02064784(void);
extern BOOL IsSessionFlagSet(u32 flag);
extern BOOL TrySelectListEntry_020c37a8(ListView *list, int index);
extern BOOL PlaySoundEffect(int group, int index);
extern void SelectListEntry(ListView *list, int index);
extern void PlaceCursorAtListEntry(ListView *list, int index);
extern void MI_CpuCopy8(const void *source, void *destination, u32 size);

void HandleListTouchInput(ListView *list, const ListTouchSample *touch)
{
    ListTable *table = list->data->table;

    if (func_ov001_02064784() == 0 && IsSessionFlagSet(0x370b)) {
        return;
    }
    if (!list->scrolling && touch->touched == 1 && touch->validity == 0) {
        if (list->previousTouch.touched == 0) {
            int i;
            int x = touch->x - list->scrollX;
            int y = touch->y;

            for (i = 0; i < table->count; ++i) {
                ListEntry *entry = &table->entries[i];
                int column = entry->column;

                /* Each selectable label occupies twelve by three tiles. */
                if (x >= column * 8 && (column + 12) * 8 >= x) {
                    int row = entry->row;
                    if (y >= row * 8 && (row + 3) * 8 >= y) {
                        if (!TrySelectListEntry_020c37a8(list, i)) {
                            PlaySoundEffect(0, 4);
                        } else {
                            PlaySoundEffect(0, 0x4d);
                        }
                        break;
                    }
                }
            }
        } else {
            int x = list->scrollX + (touch->x - list->previousTouch.x);
            if (x > 0) {
                x = 0;
            } else if (x < -256) {
                x = -256;
            }
            list->scrollX = x;
            SelectListEntry(list, list->selectedIndex);
            PlaceCursorAtListEntry(list, list->cursorIndex);
        }
    }
    MI_CpuCopy8(touch, &list->previousTouch, sizeof(*touch));
}
