#include "nitro/types.h"

extern void *NNSi_FndAllocFromDefaultHeapEx_0202a19c(u32 size, int align);
extern int func_02026b00(int mode, void *buffer, int size);
extern int compareByteStrings_02021c54(unsigned char *leftBytes, unsigned char *rightBytes, int length);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);

typedef struct {
    u8 pad_00[4];
    u8 *referenceBytes;
} IdTable;

extern IdTable g_idTable_02055f30;

int func_02026ce0(void)
{
    void *buffer;
    int result;
    int status;
    u8 *reference;
    int count;
    int offset;
    int cmpResult;

    buffer = NNSi_FndAllocFromDefaultHeapEx_0202a19c(0x20, 0x20);
    result = 0;
    status = func_02026b00(0, buffer, 0x20);
    if (status == 0) {
        reference = g_idTable_02055f30.referenceBytes;
        count = 0;
        offset = 0;
        do {
            cmpResult = compareByteStrings_02021c54((u8 *)buffer + offset, reference, 8);
            if (cmpResult != 0) {
                break;
            }
            count = count + 1;
            offset = offset + 8;
        } while (count < 4);
        result = 1;
        if (count != 4) {
            result = 0;
        }
    }
    NNSi_FndFreeFromDefaultHeap_0202a1c4(buffer);
    return result;
}
