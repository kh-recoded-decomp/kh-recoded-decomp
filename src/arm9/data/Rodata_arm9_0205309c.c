#include "nitro/types.h"

extern void G2D_ClearCharacterCanvas_02017494(void);
extern void G2D_DrawGlyphOnCanvas_020170f8(void);
extern void G2D_FillCanvasRectangle_02017564(void);

void (*const data_0205309c[3])(void) = {
    G2D_DrawGlyphOnCanvas_020170f8,
    G2D_ClearCharacterCanvas_02017494,
    G2D_FillCanvasRectangle_02017564,
};
