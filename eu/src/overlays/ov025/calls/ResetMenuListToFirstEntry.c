#include "nitro/types.h"

extern u32 gMenuListWorkStorage;
extern u32 ResetListToFirstEntry;

void ResetMenuListToFirstEntry(void) {
    ((void (*)(u32))&ResetListToFirstEntry)(gMenuListWorkStorage + 25844);
}
