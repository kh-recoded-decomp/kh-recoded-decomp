#include "nitro/types.h"

extern u8 *data_ov031_020bc820;

u32 GetOv031FieldTransitionFlag(void)
{
    return *(const u16 *)(data_ov031_020bc820 + 0x6) & 0x20;
}
