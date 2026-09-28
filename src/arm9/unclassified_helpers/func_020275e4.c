#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xc];
    u8 *data;
} MainDataHolder_0205fe00;

extern MainDataHolder_0205fe00 g_mainDataHolder_0205fe00;

int func_020275e4(void)
{
    u8 *base = g_mainDataHolder_0205fe00.data + 0x2788;
    int count = 0;
    int byteIndex = 0;
    do {
        for (int bit = 0; bit < 8; bit++) {
            if ((1 << bit) & base[byteIndex]) {
                count++;
            }
        }
        byteIndex++;
    } while (byteIndex < 0x67);
    return count;
}
