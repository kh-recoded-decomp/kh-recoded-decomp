#include "nitro/types.h"

typedef struct {
    u8 pad_0000[0xc9a0];
    u8 screenLayers[0x1c];
} Ov039State;

extern Ov039State *data_ov039_020bea00;
extern void func_ov027_020b9e30(void *layers, int layerId);

void ClearScreenLayerDirty_020bc128(int layerId)
{
    func_ov027_020b9e30(data_ov039_020bea00->screenLayers, layerId);
}
