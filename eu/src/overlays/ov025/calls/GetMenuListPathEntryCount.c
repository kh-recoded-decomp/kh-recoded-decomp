#include "nitro/types.h"

extern u32 gMenuListWorkStorage;
extern u32 GetListPathEntryCount;

void GetMenuListPathEntryCount(void) {
    ((void (*)(u32))&GetListPathEntryCount)(gMenuListWorkStorage + 25844);
}
