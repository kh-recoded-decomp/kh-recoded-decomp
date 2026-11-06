#include "nitro/types.h"

extern u32 gFieldSessionWork;

u32 GetSessionResourceArchive(void) {
    return *(u32 *)(gFieldSessionWork + 0x272c);
}
