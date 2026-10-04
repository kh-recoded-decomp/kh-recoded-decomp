#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_000[0x73c];
    fx32 scrollX;
    fx32 scrollSpeed;
    int entryCount;
    int cursor;
    u8 pad_74c[0x1b0];
    BOOL confirmMode;
    int lastRepeatTick;
    BOOL popupOpen;
} Ov089Menu;

extern u16 data_020604fc;
extern u16 data_02060500;

extern u64 OS_GetTick_02003fd4(void);
extern BOOL func_ov039_020bc0d4(void);
extern void RefreshEntryCaption_020beff4(Ov089Menu *menu, BOOL playSound);
extern void DrawEntryCarousel_020bfeec(Ov089Menu *menu);

void UpdateEntryCarousel_020c01f4(Ov089Menu *menu)
{
    BOOL scrollLeft = FALSE;
    BOOL scrollRight = FALSE;
    u64 tick = OS_GetTick_02003fd4();
    BOOL ready;
    fx32 scroll;

    if (tick == 0 || tick - menu->lastRepeatTick >= 0x3fec4) {
        ready = TRUE;
    } else {
        ready = FALSE;
    }
    if (!menu->popupOpen) {
        if (data_020604fc & 0x220) {
            if (ready) {
                scrollLeft = TRUE;
                if (data_02060500 & 0x220) {
                    menu->lastRepeatTick = tick;
                }
            }
        } else if (data_020604fc & 0x110) {
            if (ready) {
                scrollRight = TRUE;
                if (data_02060500 & 0x110) {
                    menu->lastRepeatTick = tick;
                }
            }
        } else {
            menu->lastRepeatTick = 0;
        }
    }
    if (!menu->popupOpen && !menu->confirmMode && menu->entryCount > 1) {
        if (func_ov039_020bc0d4() && scrollLeft) {
            scroll = menu->scrollX + 0x2800;
            menu->scrollX = scroll;
            menu->scrollSpeed = 0x2800;
            if (scroll >= 0xc800) {
                menu->scrollX = scroll - 0xc800;
                menu->cursor = (menu->entryCount + menu->cursor - 1) % menu->entryCount;
                RefreshEntryCaption_020beff4(menu, TRUE);
            }
        } else if (func_ov039_020bc0d4() && scrollRight) {
            scroll = menu->scrollX - 0x2800;
            menu->scrollX = scroll;
            menu->scrollSpeed = -0x2800;
            if (scroll <= -0xc800) {
                menu->scrollX = scroll + 0xc800;
                menu->cursor = (menu->cursor + 1) % menu->entryCount;
                RefreshEntryCaption_020beff4(menu, TRUE);
            }
        } else if (menu->scrollX != 0) {
            menu->scrollX += menu->scrollSpeed;
            if (menu->scrollX <= -0xc800) {
                menu->cursor = (menu->cursor + 1) % menu->entryCount;
                menu->scrollSpeed = 0;
                menu->scrollX = 0;
                RefreshEntryCaption_020beff4(menu, TRUE);
            }
            if (menu->scrollX >= 0xc800) {
                menu->cursor = (menu->entryCount + menu->cursor - 1) % menu->entryCount;
                menu->scrollSpeed = 0;
                menu->scrollX = 0;
                RefreshEntryCaption_020beff4(menu, TRUE);
            }
        }
    }
    DrawEntryCarousel_020bfeec(menu);
}
