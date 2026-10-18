#pragma optimization_level 3
#pragma opt_common_subs off

#include "src/overlays/ov025/SlotListTouch.h"

extern int func_ov001_02064784(void);
extern BOOL IsSessionFlagSet(u32 flag);
extern BOOL TrySelectListEntry(ListTouchView *list, int index);
extern BOOL PlaySoundEffect(int archive, int sound);
extern void func_ov025_020b6cc0(ListTouchView *list, int index);
extern void func_ov025_020b6d20(ListTouchView *list, int index);
extern void MI_CpuCopy8(const void *source, void *destination, u32 size);

void HandleListTouch(ListTouchView *list, const ListTouchInput *touch)
{
    ListTouchRowTable *table = list->data->table;

    if (func_ov001_02064784() == 0 && IsSessionFlagSet(0x370b)) {
        return;
    }
    if (!list->scrolling && touch->down == 1 && touch->status == 0) {
        if (list->previousTouch.down == 0) {
            s32 index = 0;
            s32 x = touch->x - list->scrollPos;
            s32 y = touch->y;

            for (; index < table->count; ++index) {
                ListTouchRow *row;
                row = &table->rows[index];
                s32 tileX;
                tileX = row->tileX;
                if (x < tileX * 8) {
                    continue;
                }
                if ((tileX + 12) * 8 < x) {
                    continue;
                }
                s32 tileY;
                tileY = row->tileY;
                if (y < tileY * 8) {
                    continue;
                }
                if ((tileY + 3) * 8 < y) {
                    continue;
                }

                if (!TrySelectListEntry(list, index)) {
                    PlaySoundEffect(0, 4);
                } else {
                    PlaySoundEffect(0, 0x4d);
                }
                break;
            }
        } else {
            s32 scroll = list->scrollPos + (touch->x - list->previousTouch.x);
            if (scroll > 0) {
                scroll = 0;
            } else if (scroll < -256) {
                scroll = -256;
            }
            list->scrollPos = scroll;
            func_ov025_020b6cc0(list, list->selectedIndex);
            func_ov025_020b6d20(list, list->cursorIndex);
        }
    }
    MI_CpuCopy8(touch, &list->previousTouch, sizeof(*touch));
}
