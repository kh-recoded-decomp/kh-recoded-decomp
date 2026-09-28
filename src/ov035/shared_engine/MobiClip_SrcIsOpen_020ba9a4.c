#include "nitro/types.h"

extern u32 data_ov035_020bc460;
extern u32 func_0202a78c(u32 handle);

BOOL MobiClip_SrcIsOpen_020ba9a4(void) {
    if (func_0202a78c(data_ov035_020bc460) != 0) {
        return 1;
    }
    return 0;
}
