#include "nitro/types.h"

extern void func_02001520(u32 widget);
extern void func_020019b8(u32 widget, u32 value);
extern u32 func_020019f0(u32 widget);
extern void SetFieldAt0x2c_02001b1c(u32 widget, u32 value);
extern void func_ov001_020711b0(void);
extern u32 func_ov001_0207123c(void);
extern void func_ov001_02075584(u32 widget, u32 layer, u32 param3, u32 param4, u32 param5);
extern u32 UpdateWidgetLayerDefault_020b9df0(u32 layer, u32 id);

void func_ov001_02075d1c(u32 widget, u32 source, u32 param3)
{
    u32 layer;
    u32 saved;

    func_ov001_020711b0();
    layer = func_ov001_0207123c();
    layer = UpdateWidgetLayerDefault_020b9df0(layer, 0xb);
    saved = func_020019f0(widget);
    func_020019b8(widget, *(u32 *)(source + 0x1c));
    SetFieldAt0x2c_02001b1c(widget, 0x370);
    func_ov001_02075584(widget, layer, param3, 6, 6);
    func_02001520(widget);
    func_020019b8(widget, saved);
}
