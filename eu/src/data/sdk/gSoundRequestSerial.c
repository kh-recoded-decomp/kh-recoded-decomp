#include "nitro/types.h"

/* AllocSoundRequest consumes the low 24 bits, then advances the counter. */
u32 gSoundRequestSerial = 1;
