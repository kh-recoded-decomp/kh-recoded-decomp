#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x134];
    int pageIndex;
    u8 pad_138[0x4];
    int cursorIndex;
} Ov086Menu;

extern s64 func_02023dbc(int numerator, int denominator);
extern void func_ov086_020c080c(Ov086Menu *menu);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);

void StepCursorForward_020c0df0(Ov086Menu *menu)
{
    int columnCount;

    switch (menu->pageIndex) {
    case 3:
        columnCount = 4;
        break;
    case 6:
        columnCount = 3;
        break;
    default:
        columnCount = 2;
        break;
    }
    menu->cursorIndex = (int)(func_02023dbc(menu->cursorIndex + 1, columnCount) >> 32);
    func_ov086_020c080c(menu);
    PlaySoundEffect_0204d924(0, 2);
}
