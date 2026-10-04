#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x748];
    int cursor;
} Ov089Menu;

extern int AcquireRecordSlot_02051d3c(int slot, int param);
extern void func_ov089_020bf0a4(void);
extern void func_ov089_020bf210(Ov089Menu *menu);
extern void func_ov089_020bf398(Ov089Menu *menu);
extern void func_ov089_020bf49c(Ov089Menu *menu);
extern void func_ov089_020bf9c0(Ov089Menu *menu);
extern void func_ov089_020bfc4c(Ov089Menu *menu);
extern u32 ReadSessionPackedBits_02064574(int bitOffset, u32 bitCount);
extern void RefreshEntryCaption_020beff4(Ov089Menu *menu, BOOL playSound);
extern BOOL ShouldOpenPopupWindow_020bef00(Ov089Menu *menu);
extern void OpenPopupWindow_020bfae8(Ov089Menu *menu);

int InitEntryMenu_020c00e4(Ov089Menu *menu)
{
    int row = 0;
    u32 bits;
    int col;
    BOOL found;

    AcquireRecordSlot_02051d3c(2, 0);
    func_ov089_020bf0a4();
    func_ov089_020bf210(menu);
    func_ov089_020bf398(menu);
    func_ov089_020bf49c(menu);
    func_ov089_020bf9c0(menu);
    func_ov089_020bfc4c(menu);
    bits = ReadSessionPackedBits_02064574(0x1e05, 0x12);
    for (; row < 6; row++) {
        found = FALSE;
        for (col = 0; col < 3; col++) {
            if (bits & (1 << (0x11 - (col + row * 3)))) {
                found = TRUE;
                break;
            }
        }
        if (!found) {
            menu->cursor = row;
            RefreshEntryCaption_020beff4(menu, FALSE);
            break;
        }
    }
    if (ShouldOpenPopupWindow_020bef00(menu)) {
        OpenPopupWindow_020bfae8(menu);
    }
    return 1;
}
