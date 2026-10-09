#include "nitro/types.h"

typedef struct {
    s32 x;
    s32 y;
} SlotPosition;

typedef struct {
    u8 data[0x6434];
} SpriteManager;

typedef struct {
    u8 pad_00[0x10904];
    int slots[4];
    u8 pad_10914[2];
    u16 pendingDrop;
    u8 pad_10918[0x10940 - 0x10918];
} ScrollScreen;

typedef struct {
    u8 pad_00[0x14];
    ScrollScreen screens[2];
    u8 pad_21294[0x23aac - 0x21294];
    s32 rollPosition;
    s32 lastRollPosition;
    u8 pad_23ab4[0x23ad4 - 0x23ab4];
    SpriteManager managers[2];
} ScrollTextWork;

typedef struct {
    u32 frameCount;
    ScrollTextWork *work;
    u32 pad_08[6]; /* full size keeps work loads unaliased */
} ScrollTextGlobals;

extern ScrollTextGlobals g_scrollText_020645a0;

extern void UpdateScrollTextScreens_02062990(void);
extern void func_ov004_02061e7c(int screenIndex, int step);
extern void FeedScrollTextLine_02062dc0(int screenIndex);
extern SlotPosition *func_0204f160(SpriteManager *manager, int slot);
extern void func_0204f13c(SpriteManager *manager, int slot, SlotPosition *position);
extern void func_0204f378(SpriteManager *manager, int slot, int visible);
extern int func_0204f3b0(SpriteManager *manager, int slot);
extern void AlarmCallback_0204f12c(SpriteManager *manager);

void UpdateScrollTextFrame_020622f0(void)
{
    int i;
    int k;
    SlotPosition position;

    UpdateScrollTextScreens_02062990();
    func_ov004_02061e7c(0, 1);
    func_ov004_02061e7c(1, 1);
    FeedScrollTextLine_02062dc0(0);
    FeedScrollTextLine_02062dc0(1);
    g_scrollText_020645a0.work->lastRollPosition = g_scrollText_020645a0.work->rollPosition;
    g_scrollText_020645a0.work->rollPosition += 0x1a10;

    for (i = 0; i < 2; i++) {
        if (g_scrollText_020645a0.work->screens[i].pendingDrop != 0) {
            position = *func_0204f160(&g_scrollText_020645a0.work->managers[i], g_scrollText_020645a0.work->screens[i].slots[1]);
            if ((position.y >> 12) <= 0x80) {
                position.y += 0x40000;
                func_0204f13c(&g_scrollText_020645a0.work->managers[i], g_scrollText_020645a0.work->screens[i].slots[2], &position);
                func_0204f378(&g_scrollText_020645a0.work->managers[i], g_scrollText_020645a0.work->screens[i].slots[2], 1);
                g_scrollText_020645a0.work->screens[i].pendingDrop = 0;
            }
        }
    }

    for (k = 0; k < 2; k++) {
        for (i = 0; i < 4; i++) {
            int slot = g_scrollText_020645a0.work->screens[k].slots[i];
            SpriteManager *manager = &g_scrollText_020645a0.work->managers[k];

            if (func_0204f3b0(manager, slot)) {
                position = *func_0204f160(manager, slot);
                position.y -= 0x1a10;
                func_0204f13c(manager, slot, &position);
                func_0204f378(manager, slot, position.y > -0x40000);
            }
        }
    }
    AlarmCallback_0204f12c(&g_scrollText_020645a0.work->managers[0]);
    AlarmCallback_0204f12c(&g_scrollText_020645a0.work->managers[1]);
}

