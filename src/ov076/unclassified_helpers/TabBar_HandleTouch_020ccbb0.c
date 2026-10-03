#include "nitro/types.h"

typedef struct TouchState {
    s16 pad_00[2];
    s16 x;
    s16 y;
    u16 state;
    s16 consumed;
} TouchState;

typedef struct TabWidget {
    u8 pad_00[0x94];
    u32 unk_94_0 : 1;
    u32 touchEnabled : 1;
} TabWidget;

typedef struct TabOwner {
    u8 pad_00000[0x11e40];
    TabWidget *tabs;
} TabOwner;

extern BOOL func_ov039_020bc0d4(void);
extern TouchState *func_ov039_020bca00(void);
extern BOOL func_ov039_020bca60(void);
extern BOOL func_ov039_020bca30(void);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);
extern void func_ov039_020bbf78(int tab, int arg1, int arg2);

int TabBar_HandleTouch_020ccbb0(TabOwner *owner, int currentTab, BOOL enabled)
{
    TouchState *touch;

    if (owner->tabs->touchEnabled && func_ov039_020bc0d4()) {
        touch = func_ov039_020bca00();
        if ((touch->state & 3) == 1 && touch->x >= 0xc0 && touch->x < 0xf0 && touch->y >= 4 && touch->y < 0x14) {
            int tab = ((touch->x - 0xc0) >> 4) + 1;

            if (!func_ov039_020bca60() && !func_ov039_020bca30() && currentTab != tab) {
                if (!enabled) {
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
