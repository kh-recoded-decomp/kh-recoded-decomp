#include "nitro/types.h"

typedef struct MatAnmResult {
    u32 flag;
    u32 prmMatColor0;
    u32 prmMatColor1;
    u32 prmPolygonAttr;
} MatAnmResult;

typedef struct GeometryStateCache {
    u8 pad_00[8];
    u32 polygonAttr;
} GeometryStateCache;

extern GeometryStateCache data_0205a9a4;
extern void CalcNsBmaAnimation_0201c508(MatAnmResult *result, const void *anmObj, u32 dataIdx);
extern s64 SignedDivMod_02023dbc(int numerator, int denominator);

void CalcMaterialAnimWithGlobalAlpha_0208f4ac(MatAnmResult *result, const void *anmObj, u32 dataIdx)
{
    u16 globalAlpha = (data_0205a9a4.polygonAttr & 0x1f0000) >> 16;
    u32 attr;
    u16 alpha;

    CalcNsBmaAnimation_0201c508(result, anmObj, dataIdx);
    attr = result->prmPolygonAttr;
    alpha = SignedDivMod_02023dbc(globalAlpha * (u16)((attr & 0x1f0000) >> 16), 0x1f);
    result->prmPolygonAttr = (attr & ~0x1f0000) | (alpha << 16);
}
