#include "nitro/types.h"

typedef struct FieldMenu FieldMenu;

typedef struct MenuHandler {
    void (*func)(FieldMenu *menu);
    int arg;
} MenuHandler;
struct FieldMenu {
    u8 pad_000[0x1f8];
    void (*onRefresh)(FieldMenu *menu, int a, int b);
    void (*onScroll)(FieldMenu *menu, int speed);
    u8 pad_200[0x34];
    u32 stateFlags;
    u8 pad_238[0x524];
    int closeMode;
    u8 pad_760[8];
    int closeRequested;
    u8 pad_76c[0x250];
    MenuHandler pending;
    int closeTimer;
    u8 pad_9c8[0x724];
    void (*onClose)(FieldMenu *menu, int arg);
};

extern int func_ov052_020d10f0(FieldMenu *menu);
extern void ApplyPendingFlagReward_020bdc94(FieldMenu *menu);

void UpdateRewardMenuClose_020bddd8(FieldMenu *menu)
{
    MenuHandler *pending = &menu->pending;

    if (menu->stateFlags & 4) {
        if (func_ov052_020d10f0(menu) == 0) {
            if (menu->onRefresh != NULL) {
                menu->onRefresh(menu, 0x1e, -1);
            }
            pending->func = ApplyPendingFlagReward_020bdc94;
            pending->arg = 0x17;
            return;
        }
        menu->onClose(menu, 3);
        return;
    }
    if (menu->closeRequested != 0 && menu->closeMode == 0xc && menu->onScroll != NULL) {
        menu->onScroll(menu, 0xf000);
    }
    if (menu->closeTimer >= 0x1e000) {
        menu->onClose(menu, 4);
    }
}

