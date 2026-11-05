#include "nitro/types.h"

u32
FilterCapsuleFieldObjectContact(u32 unused, int record)
{
    if ((record != 0) && (*(int *)(record + 4) == 0x15)) {
        return 1;
    }
    return 0;
}
