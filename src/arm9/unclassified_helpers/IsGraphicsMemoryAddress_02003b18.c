#include "nitro/types.h"

BOOL IsGraphicsMemoryAddress_02003b18(u32 address) {
    if (address >= 0x05000000) {
        if (address < 0x07000800) {
            return TRUE;
        }
    }
    return FALSE;
}
