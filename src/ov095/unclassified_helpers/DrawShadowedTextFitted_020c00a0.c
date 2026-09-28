#include "nitro/types.h"

extern u32 func_ov039_020bc9ac(void);
extern void func_0200160c(void *layer, u32 x, u32 y, u32 color, u32 flags, int text,
                          u32 narrowFont, int maxWidth);

void DrawShadowedTextFitted_020c00a0(void *layer, u32 x, u32 y, u32 color, u32 flags, int text,
                                     int maxWidth)
{
    func_0200160c(layer, x + 1, y + 1, color + 1, flags, text, func_ov039_020bc9ac(), maxWidth);
    func_0200160c(layer, x, y, color, flags, text, func_ov039_020bc9ac(), maxWidth);
}
