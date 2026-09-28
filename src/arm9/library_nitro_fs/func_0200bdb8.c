#include "nitro/types.h"

extern int func_0200b850(void *info, u32 param1, u32 param2);
extern int FS_UnloadOverlayImage_0200bd54(void *info);

int func_0200bdb8(u32 param1, u32 param2, u32 param3, u32 param4)
{
    u8 info[44];

    if (func_0200b850(info, param1, param2) != 0 && FS_UnloadOverlayImage_0200bd54(info) != 0) {
        return 1;
    }
    return 0;
}
