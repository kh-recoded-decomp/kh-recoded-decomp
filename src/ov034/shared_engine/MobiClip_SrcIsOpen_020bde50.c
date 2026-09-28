#include "nitro/types.h"

extern int data_020be920;
extern u32 func_0202a78c(u32 handle);

/* Checks whether the MobiClip source handle is open */
BOOL MobiClip_SrcIsOpen_020bde50(void) {
    u32 status = func_0202a78c(data_020be920);
    if (status != 0) {
        return 1;
    }
    return 0;
}
