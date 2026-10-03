#include "nitro/types.h"

typedef struct MenuState {
    char pad0000[0x64fc];
    int isOpen;
    char pad6500[0x66fe - 0x6500];
    s8 cursor;
} MenuState;

extern MenuState *data_ov024_020b7520;
extern void func_ov024_020b60e0(void);
extern void func_ov024_020b5828(void *menu, int value);
extern void func_ov024_020b6bb0(void);

void ResetBoardCursor_020b72e4(void *menu, BOOL refresh)
{
    if (refresh) {
        func_ov024_020b60e0();
    }
    func_ov024_020b5828(menu, 0);
    if (data_ov024_020b7520->isOpen) {
        data_ov024_020b7520->cursor = -1;
        func_ov024_020b6bb0();
    }
}
