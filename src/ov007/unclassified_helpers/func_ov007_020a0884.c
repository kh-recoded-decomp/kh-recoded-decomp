#include "nitro/types.h"

extern int func_ov001_02067ed4(void);
extern int func_ov001_020681d4(void);
extern int func_ov001_02072178(void);

typedef struct {
    u8 pad_00[0x0F];
    u8 flags;
} UnkObj_020a0884;

s32 func_ov007_020a0884(u32 unused, UnkObj_020a0884 *obj)
{
    obj->flags |= 2;
    func_ov001_02067ed4();
    func_ov001_020681d4();
    func_ov001_02072178();
    return 0;
}
