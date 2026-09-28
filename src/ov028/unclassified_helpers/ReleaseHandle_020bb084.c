#include "nitro/types.h"

extern u32 g_handle_020bb300;
extern void PXI_Init_0202a638(u32 handle);

void ReleaseHandle_020bb084(void)
{
    PXI_Init_0202a638(g_handle_020bb300);
    g_handle_020bb300 = 0xffffffff;
}
