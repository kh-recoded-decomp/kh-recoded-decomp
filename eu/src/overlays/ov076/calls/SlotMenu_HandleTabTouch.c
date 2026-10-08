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

extern BOOL GetPrimaryElementEnabled(void);
extern TouchState *GetMenuInputState(void);
extern BOOL IsStatePhaseActive(void);
extern BOOL IsStatePhase4(void);
extern BOOL PlaySoundEffect(int seqArcNo, int index);
extern void StartSubScene(int tab, int arg1, int arg2);

int SlotMenu_HandleTabTouch(TabOwner *owner, int currentTab, BOOL enabled)
{
    TouchState *touch;

    if (owner->tabs->touchEnabled && GetPrimaryElementEnabled()) {
        touch = GetMenuInputState();
        if ((touch->state & 3) == 1 && touch->x >= 0xc0 && touch->x < 0xf0 && touch->y >= 4 && touch->y < 0x14) {
            int tab = ((touch->x - 0xc0) >> 4) + 1;

            if (!IsStatePhaseActive() && !IsStatePhase4() && currentTab != tab) {
                if (!enabled) {
                    PlaySoundEffect(1, 4);
                } else {
                    PlaySoundEffect(1, 2);
                    StartSubScene(tab, -1, 0);
                }
            } else {
                PlaySoundEffect(1, 4);
            }
            return tab - 1;
        }
    }
    return -1;
}
