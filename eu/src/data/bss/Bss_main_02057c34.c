#include "nitro/types.h"

static u32 gSoundCommandPoolPrefix[1024];
static u32 gSoundSharedWorkStorage[160];
static u32 gSoundSubmittedCommandListsStorage[11];
static u32 gSoundCommandQueueState[9];
static u32 gSoundCommandMutex[6];
static u32 gSoundInitialized;
