#include "nitro/types.h"

typedef struct MosaicLayer {
    u8 pad_00[0x24];
    u16 flags;
    u8 pad_26[0xe];
    s32 scrollX;
    s32 scrollY;
    s32 mosaicLevel;
    s32 scrollYOffset;
    s32 timer;
    s32 duration;
} MosaicLayer;

typedef struct SceneWork {
    u8 pad_0000[0xc80];
    s32 skipAnimations;
} SceneWork;

typedef struct SceneContext {
    u32 unk_00;
    SceneWork *work;
} SceneContext;

#define REG_MOSAIC_BG (*(vu8 *)0x0400004c)
#define REG_BG1CNT (*(vu16 *)0x0400000a)
#define REG_BG1OFS (*(vu32 *)0x04000014)
#define SET_BG1_OFFSET(x, y) (REG_BG1OFS = ((x) & 0x1ff) | (((y) << 16) & 0x1ff0000))

extern SceneContext data_ov036_020c3920;
extern int EvaluateInterpolationCurve_02025718(int mode, unsigned int duration, int remaining);
extern int ScaleAroundPivot_020257b0(int ratio, int target, int origin);

void StepBgMosaicTransition_020bbe78(MosaicLayer *layer)
{
    int remaining = --layer->timer;
    int level;
    int ratio;

    if (data_ov036_020c3920.work->skipAnimations != 0 || remaining == 0) {
        layer->flags &= ~0x40;
        REG_MOSAIC_BG = layer->mosaicLevel | (layer->mosaicLevel << 4);
        if (layer->mosaicLevel == 0) {
            REG_BG1CNT &= ~0x40;
        }
        level = layer->mosaicLevel;
        SET_BG1_OFFSET((level >> 1) - layer->scrollX, (level >> 1) - (layer->scrollY - layer->scrollYOffset));
        return;
    }
    ratio = EvaluateInterpolationCurve_02025718(2, layer->duration, remaining);
    level = ScaleAroundPivot_020257b0(ratio, layer->mosaicLevel << 12, (0xf - layer->mosaicLevel) << 12) >> 12;
    REG_MOSAIC_BG = level | (level << 4);
    SET_BG1_OFFSET((level >> 1) - layer->scrollX, (level >> 1) - (layer->scrollY - layer->scrollYOffset));
}
