#include "nitro/types.h"

extern u32 g_fieldContext_020bb380;

void SetFieldModeFlag_020bb03c(u8 mode)
{
    *(u8 *)(g_fieldContext_020bb380 + 8) = mode;
    *(u16 *)(g_fieldContext_020bb380 + 6) = *(u16 *)(g_fieldContext_020bb380 + 6) | 0x4000;
}
