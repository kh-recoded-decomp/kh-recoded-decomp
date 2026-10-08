#include "nitro/types.h"

typedef struct MosaicLayer {
    u8 pad_00[0x24];
    u16 flags;
    u8 pad_26[0x16];
    s32 mosaicLevel;
    u8 pad_40[0x4];
    s32 duration;
    s32 timer;
} MosaicLayer;

typedef struct SceneWork {
    u8 pad_0000[0x1098];
    MosaicLayer *layer;
} SceneWork;

typedef struct SceneContext {
    u32 unk_00;
    SceneWork *work;
} SceneContext;

#define REG_MOSAIC_BG (*(vu8 *)0x0400004c)
#define REG_BG1CNT (*(vu16 *)0x0400000a)

extern SceneContext data_ov036_020c3940;

void StartBgMosaicTransition(int reveal, int duration)
{
    MosaicLayer *layer = data_ov036_020c3940.work->layer;

    if (reveal == 0) {
        if (duration == 0) {
            REG_MOSAIC_BG = 0xff;
            return;
        }
        REG_MOSAIC_BG = 0;
        layer->mosaicLevel = 0xf;
    } else {
        if (duration == 0) {
            REG_BG1CNT &= ~0x40;
            return;
        }
        REG_MOSAIC_BG = 0xff;
        layer->mosaicLevel = 0;
    }
    REG_BG1CNT |= 0x40;
    layer->duration = duration;
    layer->timer = duration;
    layer->flags |= 0x40;
}
