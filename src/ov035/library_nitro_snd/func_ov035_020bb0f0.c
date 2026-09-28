#include "nitro/types.h"

extern int SNDi_LockMutex_020baf94(void);
extern int func_ov035_020baf88(void);

u8 func_ov035_020bb0f0(void) {
    int lockResult;
    u8 status;

    lockResult = SNDi_LockMutex_020baf94();
    status = 2;
    if (lockResult == 0) {
        status = 0;
    }
    lockResult = func_ov035_020baf88();
    return lockResult != 0 | status;
}
