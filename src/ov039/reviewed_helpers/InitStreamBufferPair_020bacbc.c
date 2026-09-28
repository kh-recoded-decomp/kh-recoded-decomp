#include "nitro/types.h"

extern int data_ov039_020bea00;
extern void func_02052514(void *record, int value0, int value1, int value2, int value3);
extern void func_0205255c(void *record);

void InitStreamBufferPair_020bacbc(int blockCount, u32 flag)
{
    int base = data_ov039_020bea00;
    int size = blockCount << 0xc;

    func_02052514((void *)(base + 0xc9d0), 0, *(int *)(base + 0xc9c8), size, flag);
    func_02052514((void *)(base + 0xc9ec), 0, *(int *)(base + 0xc9cc), size, flag);
    func_0205255c((void *)(base + 0xc9d0));
    func_0205255c((void *)(base + 0xc9ec));
}
