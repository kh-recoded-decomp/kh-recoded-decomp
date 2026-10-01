#include "nitro/types.h"

extern void func_02052514(void *record, int value0, int value1, int value2, int value3);
extern void func_0205255c(void *record);

void StartTimerFromPackedPair_0207cb78(void *record, u32 packed, int extra) {
    s16 high = (u16)(packed >> 16);
    s16 low = (u16)packed;
    func_02052514(record, 0, high * 0xcccd, low * 0xcccd, extra);
    func_0205255c(record);
}
