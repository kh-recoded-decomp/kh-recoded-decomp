#include "nitro/types.h"

extern void G2D_ClearArea1D_020176fc(void);
extern void G2D_ClearCharacterCanvas_02017494(void);
extern void G2D_DrawGlyph1D_0201728c(void);

void (*const data_020530a8[3])(void) = {
    G2D_DrawGlyph1D_0201728c,
    G2D_ClearCharacterCanvas_02017494,
    G2D_ClearArea1D_020176fc,
};
