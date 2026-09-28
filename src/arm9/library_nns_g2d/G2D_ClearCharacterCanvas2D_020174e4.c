#include "nitro/types.h"

typedef struct NNSG2dCharCanvas {
    u8 *charBase;
    int areaWidth;
    int areaHeight;
    u8 dstBpp;
    u8 reserved[3];
    u32 param;
    const void *vtable;
} NNSG2dCharCanvas;

extern void MIi_CpuClearFast_01ff8740(u32 data, void *destp, u32 size);

static inline int GetCharacterSize(const NNSG2dCharCanvas *pCC) {
    return 8 * 8 * pCC->dstBpp / 8;
}

static inline u32 SpreadColor32(const NNSG2dCharCanvas *pCC, int cl) {
    u32 val = (u32)cl;
    if (pCC->dstBpp == 4) {
        val = (val << 4) | val;
        val |= val << 8;
        val |= val << 16;
    } else {
        val = (val << 8) | val;
        val |= val << 16;
    }
    return val;
}

void G2D_ClearCharacterCanvas2D_020174e4(const NNSG2dCharCanvas *pCC, int cl) {
    u32 data = SpreadColor32(pCC, cl);
    const int charSize = GetCharacterSize(pCC);
    const int lineStep = (int)(charSize * pCC->param);
    const int lineSize = charSize * pCC->areaWidth;
    int y;
    u8 *charBase = pCC->charBase;

    for (y = 0; y < pCC->areaHeight; y++) {
        MIi_CpuClearFast_01ff8740(data, charBase, (u32)lineSize);
        charBase += lineStep;
    }
}
