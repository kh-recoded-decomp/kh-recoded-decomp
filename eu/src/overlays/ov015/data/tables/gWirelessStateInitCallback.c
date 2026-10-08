#include "nitro/types.h"

extern void InitPeerWirelessSession(void);

void (*gWirelessStateInitCallback[1])(void) = {
    InitPeerWirelessSession,
};
