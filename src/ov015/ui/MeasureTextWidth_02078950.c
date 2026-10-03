#include "nitro/types.h"

extern int func_02001908(void *font, const u16 *text, const u16 **next);

int MeasureTextWidth_02078950(void *font, const u16 *text, int maxLines)
{
    int maxWidth = 0;
    int lines = 0;
    const u16 *next = NULL;
    int width;

    while (text != NULL) {
        width = func_02001908(font, text, &next);
        if (maxWidth < width) {
            maxWidth = width;
        }
        lines++;
        text = next;
        if (maxLines > 0 && lines >= maxLines) {
            break;
        }
    }
    return maxWidth;
}
