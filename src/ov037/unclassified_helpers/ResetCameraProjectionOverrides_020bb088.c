#include "nitro/types.h"

extern u8 *g_screenState_020bb764;
extern void LoadDefaultProjectionValues_0202a7b4(u32 *values);

void ResetCameraProjectionOverrides_020bb088(void)
{
    LoadDefaultProjectionValues_0202a7b4((u32 *)(g_screenState_020bb764 + 0x198));
    *(u32 *)(g_screenState_020bb764 + 0x1b0) = 0x4cd;
    *(u32 *)(g_screenState_020bb764 + 0x1bc) = 0x4cd;
    *(u32 *)(g_screenState_020bb764 + 0x1c0) = 0x3000;
}
