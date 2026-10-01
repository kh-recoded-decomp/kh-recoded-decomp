#include "nitro/types.h"

typedef struct {
    s32 width;
    s32 height;
} TextSize;

extern TextSize G2D_MeasureTextRectangle_02016c18(const void *font, int hSpace, int vSpace, const void *text);

static inline TextSize MeasureText(const void *font, int hSpace, int vSpace, const void *text)
{
    return G2D_MeasureTextRectangle_02016c18(font, hSpace, vSpace, text);
}

int MeasureMessageTiles_02078dd8(TextSize *size, BOOL useFixedSize, const void *font, const void *text)
{
    int extraWidth;

    if (!useFixedSize) {
        int width;

        extraWidth = 0;
        *size = MeasureText(font, 0, 3, text);
        width = (size->width + 10) / 8;
        if (width >= 28) {
            width = 28;
        }
        size->width = width;
        size->height = (size->height + 7) / 8;
    } else {
        size->width = 24;
        extraWidth = 4;
        size->height = 5;
    }
    return extraWidth;
}
