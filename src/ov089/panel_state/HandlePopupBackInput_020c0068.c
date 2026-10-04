#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x8fc];
    BOOL subMenuOpen;
    u8 pad_900[4];
    BOOL popupOpen;
} Ov089Menu;

extern void ClosePopupWindow_020bfb8c(Ov089Menu *menu, int soundIndex);
extern void func_ov089_020bfdac(Ov089Menu *menu, int arg);
extern void WriteSessionPackedBits_0206459c(int key, int bits, int value);
extern void SetPendingScene_02025644(int scene, int arg);
extern void func_ov039_020bbf78(int a, int b, int c);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);

void HandlePopupBackInput_020c0068(Ov089Menu *menu)
{
    if (menu->popupOpen) {
        ClosePopupWindow_020bfb8c(menu, 3);
        return;
    }
    if (menu->subMenuOpen) {
        func_ov089_020bfdac(menu, 0);
    } else {
        WriteSessionPackedBits_0206459c(0x3703, 3, 0);
        SetPendingScene_02025644(2, 0);
        func_ov039_020bbf78(-1, -1, 1);
    }
    PlaySoundEffect_0204d924(0, 3);
}
