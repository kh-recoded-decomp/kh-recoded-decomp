#include "nitro/types.h"

extern u8 *data_ov015_020812e0;

BOOL func_ov015_020790e8(void) {
    return *(s16 *)(data_ov015_020812e0 + 0x38) > 0;
}
