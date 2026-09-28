#include "nitro/types.h"

extern void PXI_Init_0202a638();
extern u32 g_ov029ObjHandle_020bab60;

void ReleaseOv029Object_020baa64(void)
{
    PXI_Init_0202a638(g_ov029ObjHandle_020bab60);
    g_ov029ObjHandle_020bab60 = 0xffffffff;
}
