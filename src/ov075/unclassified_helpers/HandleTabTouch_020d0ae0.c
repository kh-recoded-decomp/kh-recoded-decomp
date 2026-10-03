#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x94];
    u32 unused0 : 1;
    u32 tabsEnabled : 1;
} MenuState;

typedef struct {
    u8 pad_00000[0x11e40];
    MenuState *state;
} MatrixMenu;

typedef struct {
    u8 pad_00[4];
    s16 x;
    s16 y;
    u16 flags;
} TouchState;

extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);
extern u32 func_ov039_020bc0d4(void);
extern TouchState *func_ov039_020bca00(void);
extern BOOL func_ov039_020bca60(void);
extern BOOL func_ov039_020bca30(void);
extern void func_ov039_020bbf78(int tab, int arg, int mode);

int HandleTabTouch_020d0ae0(MatrixMenu *menu, int currentTab, BOOL allowChange)
{
    TouchState *touch;
    int tab;

    if (menu->state->tabsEnabled && func_ov039_020bc0d4() != 0) {
        touch = func_ov039_020bca00();
        if ((touch->flags & 3) == 1 && touch->x >= 0xc0 && touch->x < 0xf0 && touch->y >= 4 &&
            touch->y < 0x14) {
            tab = ((touch->x - 0xc0) >> 4) + 1;
            if (!func_ov039_020bca60() && !func_ov039_020bca30() && currentTab != tab) {
                if (!allowChange) {
                    PlaySoundEffect_0204d924(1, 4);
                } else {
                    PlaySoundEffect_0204d924(1, 2);
                    func_ov039_020bbf78(tab, -1, 0);
                }
            } else {
                PlaySoundEffect_0204d924(1, 4);
            }
            return tab - 1;
        }
    }
    return -1;
}
