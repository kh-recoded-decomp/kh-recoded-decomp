#include "nitro/types.h"

extern u32 gMenuListWorkStorage;
extern u32 ScrollListDownOneRow;

void ScrollMenuListDownOneRow(void) {
    ((void (*)(u32))&ScrollListDownOneRow)(gMenuListWorkStorage + 25844);
}
