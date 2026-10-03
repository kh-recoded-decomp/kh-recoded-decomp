#include "nitro/types.h"

extern u16 UnmapCharHighByte_02065f7c(int code);

int PackWideChars12_02065ff4(const u16 *text, int length, u8 *out, int outSize)
{
    int i = 0;
    int written = 0;
    int first;
    int second;

    for (; i < length; i += 2) {
        if (written + 2 >= outSize) {
            break;
        }
        first = UnmapCharHighByte_02065f7c(text[i]);
        if (i + 1 < length) {
            second = UnmapCharHighByte_02065f7c(text[i + 1]);
        } else {
            second = 0;
        }
        out[written] = first;
        out[written + 1] = second;
        out[written + 2] = ((first & 0xf00) >> 4) | ((second & 0xf00) >> 8);
        written += 3;
    }
    return written;
}
