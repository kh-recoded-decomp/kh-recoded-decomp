#include "nitro/types.h"

typedef struct {
    u8 pad_0000[0xc9a0];
    u8 screenLayers[0x1c];
} Ov039State;

extern Ov039State *data_ov039_020bea00;
extern void func_ov027_020b9b94(void *layers, void *widget);

void ClearWidgetOnScreenLayer_020bb730(void *widget)
{
    func_ov027_020b9b94(data_ov039_020bea00->screenLayers, widget);
}
