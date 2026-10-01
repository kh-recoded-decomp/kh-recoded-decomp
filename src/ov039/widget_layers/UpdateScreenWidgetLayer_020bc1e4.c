#include "nitro/types.h"

typedef struct {
    u8 pad_0000[0xc9a0];
    u8 screenLayers[0x1c];
} Ov039State;

extern Ov039State *data_ov039_020bea00;
extern int UpdateWidgetLayerDefault_020b9df0(int layers, int widget);

void UpdateScreenWidgetLayer_020bc1e4(int widget)
{
    UpdateWidgetLayerDefault_020b9df0((int)data_ov039_020bea00->screenLayers, widget);
}
