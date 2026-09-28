#include "nitro/types.h"

extern u32 g_ov038ObjHandle_020bbd80;
extern void PXI_Init_0202a638(u32 handle);

void ReleaseOv038Object_020ba6b8(void)
{
    PXI_Init_0202a638(g_ov038ObjHandle_020bbd80);
    g_ov038ObjHandle_020bbd80 = 0xffffffff;
}
