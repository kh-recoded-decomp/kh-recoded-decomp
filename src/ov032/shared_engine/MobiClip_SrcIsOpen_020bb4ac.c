#include "nitro/types.h"

extern u32 data_ov032_020bffc0;
extern s32 func_0202a78c(u32 handle);

/* Checks whether the MobiClip source handle is open */
BOOL MobiClip_SrcIsOpen_020bb4ac(void) {
    if (func_0202a78c(data_ov032_020bffc0) != 0) {
        return 1;
    }
    return 0;
}
