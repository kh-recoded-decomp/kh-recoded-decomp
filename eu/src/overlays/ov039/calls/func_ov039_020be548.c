#include "nitro/types.h"

extern void SetTextColorIfFits(int *obj, u32 flags, u32 style);
extern void DrawTextAnchored(int *obj, int x, int y, int z, u32 color, u32 style);
extern void Obj_SetField14(int *obj, int value);

void func_ov039_020be548(int *obj, int x, int y, int z, u32 color, u32 style, u32 flags)
{
    int saved = *obj;

    SetTextColorIfFits(obj, flags, style);
    DrawTextAnchored(obj, x + 1, y + 1, z + 1, color, style);
    DrawTextAnchored(obj, x, y, z, color, style);
    Obj_SetField14(obj, saved);
}
