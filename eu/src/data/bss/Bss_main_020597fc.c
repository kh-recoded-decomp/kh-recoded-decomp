#include "nitro/types.h"

static u32 gWmCommandFreeQueueSlots[10];
static u32 gWmCommandFreeQueue[8];
static u32 gWmPreSleepCallbackStorage[4];
static u32 gWmState[2];
