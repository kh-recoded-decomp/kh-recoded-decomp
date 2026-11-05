#include "nitro/types.h"

extern u32 data_ov025_020b7780;
extern u32 GetListPathEntryCount;

void GetMenuListPathEntryCount(void) {
    ((void (*)(u32))&GetListPathEntryCount)(data_ov025_020b7780 + 25844);
}
