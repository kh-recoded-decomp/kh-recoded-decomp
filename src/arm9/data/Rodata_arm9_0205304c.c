#include "nitro/types.h"

extern void G2D_ClearCharacterCanvas2D_020174e4(void);
extern void G2D_DrawGlyphOnCanvas_020170f8(void);
extern void G2D_FillCanvasRectangle_02017564(void);

void *const data_02053064[14] = {
    (void *)0x03020100,
    (void *)0x08060504,
    (void *)0x03020100,
    (void *)0x08060504,
    (void *)0x03010100,
    (void *)0x08000303,
    (void *)0x00080000,
    (void *)0x08080808,
    (void *)0xFFFFFFFF,
    (void *)0xFFFFFFFF,
    (void *)0xFFFFFFFF,
    (void *)G2D_DrawGlyphOnCanvas_020170f8,
    (void *)G2D_ClearCharacterCanvas2D_020174e4,
    (void *)G2D_FillCanvasRectangle_02017564,
};

const u32 data_0205304c[6] = {
    0x01000100, 0x01000000, 0x00020200, 0x01000200,
    0x02000001, 0x00030200,
};
