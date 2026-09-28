#include "nitro/types.h"

extern s32 func_ov001_02091aa8(void);
extern s32 func_ov001_02097974(void);

s32 func_ov001_02088064(void)
{
    s32 result;

    result = func_ov001_02091aa8();
    if (result == 0) {
        return 0;
    }
    result = func_ov001_02097974();
    if (result == 0) {
        result = 0;
    }
    return result;
}
