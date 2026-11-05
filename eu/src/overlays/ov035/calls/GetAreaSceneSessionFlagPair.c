#include "nitro/types.h"

extern int IsSessionFlag3701Set(void);
extern int IsSessionFlag3700Set(void);

u8 GetAreaSceneSessionFlagPair(void) {
    int lockResult;
    u8 status;

    lockResult = IsSessionFlag3701Set();
    status = 2;
    if (lockResult == 0) {
        status = 0;
    }
    lockResult = IsSessionFlag3700Set();
    return lockResult != 0 | status;
}
