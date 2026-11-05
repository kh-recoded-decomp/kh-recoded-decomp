#include "nitro/types.h"

extern int MeasureMovieSubtitleWidth_020a8d00(void);

int MeasureSubtitleLinesMaxAndResetCursor(int context, int minWidth)
{
    int width = MeasureMovieSubtitleWidth_020a8d00();

    *(s32 *)(context + 0x58) = 0;
    if (width <= minWidth) {
        width = minWidth;
    }
    return width;
}
