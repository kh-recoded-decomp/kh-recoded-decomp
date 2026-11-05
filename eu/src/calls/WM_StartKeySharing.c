#include "nitro/types.h"

extern int WM_StartDataSharing(void *sharingBuffer, u32 port, u32 aidMask,
                               u32 dataSize, BOOL doubleMode);

int WM_StartKeySharing(void *sharingBuffer, u32 port)
{
    return WM_StartDataSharing(sharingBuffer, port, 0xffff, 2, TRUE);
}
