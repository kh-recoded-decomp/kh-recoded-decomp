#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x32];
    u8 value;
} OverlayObject;

extern u32 func_02036164(u8 value);
extern void func_ov001_02087258(OverlayObject *obj, u32 value);

void func_ov017_020a5a78(OverlayObject *obj)
{
    u32 result = func_02036164(obj->value);
    func_ov001_02087258(obj, result);
}
