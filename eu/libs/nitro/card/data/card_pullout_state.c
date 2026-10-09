#include "nitro/types.h"

typedef BOOL (*CARDPulledOutCallback)(void);

typedef struct CARDPulledOutState {
    u32 slotResetCount;
    BOOL isPulledOut;
    CARDPulledOutCallback userCallback;
} CARDPulledOutState;

CARDPulledOutState sCardPullOutState;
