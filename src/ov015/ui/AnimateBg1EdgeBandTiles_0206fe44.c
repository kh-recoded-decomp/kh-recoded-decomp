#include "nitro/types.h"

typedef struct {
    int values[8];
} FrameTable;

typedef struct {
    u8 pad_00[0xc];
    u16 tiles[1];
} ScreenData;

typedef struct {
    u8 pad_0[8];
    ScreenData *screen;
} ScreenEntry;

typedef struct {
    u8 pad_000[0xbd];
    s8 animFrame;
    s8 animTimer;
    u8 pad_0bf[0x5ac - 0xbf];
    u8 screenBank[1];
} SceneContext;

extern ScreenEntry *func_ov027_020b8558(void *owner, u16 entryId);
extern void GX_LoadBG1Scr_02007630(const void *src, u32 offset, u32 size);
extern const FrameTable data_ov015_0207a07c[];
extern SceneContext *data_ov015_0207e960;

void AnimateBg1EdgeBandTiles_0206fe44(void) {
    FrameTable mainScreenIds = data_ov015_0207a07c[0];
    FrameTable subScreenIds = data_ov015_0207a07c[3];
    FrameTable nextFrames = data_ov015_0207a07c[6];
    int row;
    ScreenEntry *entry;

    if (data_ov015_0207e960->animTimer == 0) {
        data_ov015_0207e960->animFrame = nextFrames.values[data_ov015_0207e960->animFrame];
        entry = func_ov027_020b8558(data_ov015_0207e960->screenBank, mainScreenIds.values[data_ov015_0207e960->animFrame]);
        for (row = 0; row < 4; row++) {
            GX_LoadBG1Scr_02007630(&entry->screen->tiles[row * 32], (row + 20) * 0x40, 0x40);
        }
        entry = func_ov027_020b8558(data_ov015_0207e960->screenBank, subScreenIds.values[data_ov015_0207e960->animFrame]);
        for (row = 0; row < 4; row++) {
            GX_LoadBG1Scr_02007630(&entry->screen->tiles[row * 32], row * 0x40, 0x40);
        }
        data_ov015_0207e960->animTimer = 2;
    } else {
        data_ov015_0207e960->animTimer--;
    }
}
