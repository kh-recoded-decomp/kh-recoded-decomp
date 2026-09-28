#include "nitro/types.h"

extern void func_02001668(void *context, int x, int y, int color, int flags, const u16 *text);

void DrawTextPackedColor_0200174c(void *context, int x, int y, int color, int flags, int highColor, const u16 *text)
{
    func_02001668(context, x, y, color | (highColor << 8), flags, text);
}
