#include "nitro/types.h"

extern void Text_UploadTileBuffer(u32 widget);
extern void SelectListNodeOrFirst(u32 widget, u32 value);
extern u32 GetWord20(u32 widget);
extern void SetFieldAt2C(u32 widget, u32 value);
extern void GetSceneTagTracker(void);
extern u32 func_ov001_0207123c(void);
extern void WriteTileBlockToScreen(u32 widget, u32 layer, u32 param3, u32 param4, u32 param5);
extern u32 func_ov027_020b9e10(u32 layer, u32 id);

void func_ov001_02075d1c(u32 widget, u32 source, u32 param3)
{
    u32 layer;
    u32 saved;

    GetSceneTagTracker();
    layer = func_ov001_0207123c();
    layer = func_ov027_020b9e10(layer, 0xb);
    saved = GetWord20(widget);
    SelectListNodeOrFirst(widget, *(u32 *)(source + 0x1c));
    SetFieldAt2C(widget, 0x370);
    WriteTileBlockToScreen(widget, layer, param3, 6, 6);
    Text_UploadTileBuffer(widget);
    SelectListNodeOrFirst(widget, saved);
}
