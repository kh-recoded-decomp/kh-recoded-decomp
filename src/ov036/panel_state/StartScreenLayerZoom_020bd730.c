#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScreenLayer {
    fx32 targetZoom;
    fx32 zoom;
    fx32 centerX;
    fx32 centerY;
    s32 zoomTimer;
    u8 pad_14[0x10];
    u16 flags;
    u8 pad_26[0xe];
    s32 scrollX;
    s32 scrollY;
    u8 pad_3C[0xc];
    s32 zoomDuration;
    u8 pad_4C[0x8];
} ScreenLayer;

typedef struct PanelWork {
    u8 pad_0000[0x1098];
    ScreenLayer *layers;
} PanelWork;

typedef struct PanelContext {
    u32 unk_00;
    PanelWork *work;
} PanelContext;

extern PanelContext data_ov036_020c3920;
extern void UpdateScreenLayer_020bbf90(int screen);

void StartScreenLayerZoom_020bd730(int screen, int zoom, s32 duration)
{
    ScreenLayer *layer = &data_ov036_020c3920.work->layers[screen];

    layer->zoomDuration = duration;
    if (layer->flags & 0x20) {
        layer->flags &= ~0x20;
        if (zoom != 0) {
            layer->zoom = zoom << 12;
            if (layer->zoom > 0xc000) {
                layer->zoom = 0xc000;
            }
        }
    } else {
        layer->zoomTimer = 0;
        layer->targetZoom = zoom << 12;
        if (layer->targetZoom > 0xc000) {
            layer->targetZoom = 0xc000;
        }
        layer->zoom = layer->targetZoom;
        layer->centerX = layer->scrollX << 12;
        layer->centerY = layer->scrollY << 12;
        layer->flags |= 0x10;
    }
    if (layer->zoomDuration != -1) {
        if (layer->zoomDuration == 0) {
            UpdateScreenLayer_020bbf90(screen);
        }
    } else {
        layer->flags |= 0x20;
    }
}
