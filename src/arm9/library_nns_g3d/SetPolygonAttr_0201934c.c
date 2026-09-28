#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x88];
    u32 prmPolygonAttr;
} NNSG3dGlbMaterial;

extern NNSG3dGlbMaterial data_0205a924;

void SetPolygonAttr_0201934c(u32 lightMask, int polygonMode, int cullMode, int polygonId, int alpha, u32 extraFlags)
{
    u32 low = lightMask | polygonMode << 4 | cullMode << 6;
    u32 high = extraFlags | low;
    data_0205a924.prmPolygonAttr = high | polygonId << 0x18 | alpha << 0x10;
}
