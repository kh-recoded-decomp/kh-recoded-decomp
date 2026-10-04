#include "nitro/types.h"

extern int PXI_Init_0204f0b4(void *base, void *arg, int flags);
extern void func_0204f13c(void *base, int index, void *value);
extern void func_0204f2e4(void *base, int index);
extern void func_0204f204(void *base, int index, u16 value);

void AddTaggedIndexedRecord_020c1470(void *base, void *arg, void *value, int tag)
{
    int index = PXI_Init_0204f0b4(base, arg, 0);
    func_0204f13c(base, index, value);
    func_0204f2e4(base, index);
    func_0204f204(base, index, tag);
}
