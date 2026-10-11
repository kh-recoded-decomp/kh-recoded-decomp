#include "src/overlays/ov001/SessionCounters.h"

/* AddSessionCounter clamps positive increments to the corresponding limit. */
const s32 gSessionCounterLimits[SESSION_COUNTER_COUNT] = {
    999999, 9999999, 9999999, 999, 999, 999, 999, 999,
    999, 999, 999, 999, 999, 999, 999999, 999999,
    999, 99999, 999, 99999, 99999, 99999, 99999, 99999,
    99999, 999, 999, 99999, 99999,
};
