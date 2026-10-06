#include "nitro/types.h"

extern int func_ov035_020bafb4(void);
extern int ShowMovieMessage3700(void);

u8 func_ov035_020bb110(void) {
    int lockResult;
    u8 status;

    lockResult = func_ov035_020bafb4();
    status = 2;
    if (lockResult == 0) {
        status = 0;
    }
    lockResult = ShowMovieMessage3700();
    return lockResult != 0 | status;
}
