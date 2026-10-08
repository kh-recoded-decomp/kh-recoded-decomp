#include "nitro/types.h"

typedef struct ScreenLayer {
    u8 pad_00[0x24];
    u16 flags;
    u8 pad_26[0x2];
    s32 activeImageId;
    s32 startX;
    s32 startY;
    s32 scrollX;
    s32 scrollY;
    u8 pad_3C[0x4];
    s32 scrollYOffset;
    s32 scrollFrame;
    u32 scrollDuration;
    u8 pad_4C[0x8];
} ScreenLayer;

typedef struct PanelWork {
    u8 pad_0000[0xc80];
    s32 isBusy;
    u8 pad_0C84[0x414];
    ScreenLayer *layers;
} PanelWork;

typedef struct PanelContext {
    u32 unk_00;
    PanelWork *work;
} PanelContext;

extern PanelContext data_ov036_020c3940;
extern void LoadScreenLayerImage(ScreenLayer *layer, int screen);
extern void ClearScreenLayerGraphics(ScreenLayer *layer, int screen);
extern void func_ov036_020bbc84(int screen);
extern void UpdateLayerShake(ScreenLayer *layer, int screen);
extern void StepBgMosaicTransition(ScreenLayer *layer);
extern int EvaluateInterpolationCurve(int curve, unsigned int duration, int frame);
extern int ScaleAroundPivot(int t, int from, int to);

void UpdateScreenLayer(int screen)
{
    ScreenLayer *layer = &data_ov036_020c3940.work->layers[screen];
    s32 x;
    s32 y;

    if (layer->flags & 1) {
        if (layer->activeImageId != -1) {
            LoadScreenLayerImage(layer, screen);
        } else {
            ClearScreenLayerGraphics(layer, screen);
        }
        layer->flags &= ~1;
    }
    if (layer->flags & 4) {
        if (layer->scrollFrame > 0) {
            layer->scrollFrame--;
        }
        if (data_ov036_020c3940.work->isBusy != 0 || layer->scrollFrame == 0) {
            layer->flags &= ~4;
            x = layer->scrollX;
            y = layer->scrollY;
        } else {
            int t = EvaluateInterpolationCurve(3, layer->scrollDuration, layer->scrollFrame);
            x = ScaleAroundPivot(t, layer->scrollX << 12, layer->startX << 12) >> 12;
            y = ScaleAroundPivot(t, layer->scrollY << 12, layer->startY << 12) >> 12;
        }
        if (screen == 0) {
            *(vu32 *)0x4000014 = (-x & 0x1ff) | ((-(y - layer->scrollYOffset) << 16) & 0x1ff0000);
        } else {
            *(vu32 *)0x4001010 = (-x & 0x1ff) | ((-y << 16) & 0x1ff0000);
        }
    }
    if (layer->flags & 8) {
        func_ov036_020bbc84(screen);
    }
    if (layer->flags & 0x10) {
        UpdateLayerShake(layer, screen);
    }
    if (layer->flags & 0x40) {
        StepBgMosaicTransition(layer);
    }
}
