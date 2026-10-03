#include "nitro/types.h"

extern u16 RemapCharHighByte_02065fc8(u16 code);

int UnpackWideChars12_0206608c(const u8 *packed, int length, u16 *out, int outSize)
{
    int i = 0;
    int written = 0;

    for (; i < length; i += 3) {
        if (written + 1 >= outSize) {
            break;
        }
        out[written] = packed[i] | ((u16)(packed[i + 2] & 0xf0) << 4);
        out[written + 1] = packed[i + 1] | ((u16)(packed[i + 2] & 0xf) << 8);
        out[written] = RemapCharHighByte_02065fc8(out[written]);
        out[written + 1] = RemapCharHighByte_02065fc8(out[written + 1]);
        written += 2;
    }
    return written;
}
