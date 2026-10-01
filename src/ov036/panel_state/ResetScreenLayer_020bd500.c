#include "nitro/types.h"

typedef struct ScreenLayer {
    u8 pad_00[0x28];
    s32 activeImageId;
    u8 pad_2C[0x20];
    s32 useWhiteClearColor;
    s32 pendingImageId;
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
extern void ClearScreenLayerGraphics_020bbb64(ScreenLayer *layer, int screen);

void ResetScreenLayer_020bd500(int screen, s32 useWhiteClearColor)
{
    ScreenLayer *layer = &data_ov036_020c3920.work->layers[screen];

    layer->pendingImageId = -1;
    layer->activeImageId = -1;
    layer->useWhiteClearColor = useWhiteClearColor;
    ClearScreenLayerGraphics_020bbb64(layer, screen);
}
