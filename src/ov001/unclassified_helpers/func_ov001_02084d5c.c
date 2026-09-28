#include "nitro/types.h"

extern u32 func_02034ff0();
extern u32 func_02036b7c();
extern u32 func_ov001_0207f244();

void
func_ov001_02084d5c(int self)
{
    func_02034ff0(self + 0xa0);
    func_02036b7c(*(int *)(self + 0xc) + 0x1a8);
    func_ov001_0207f244(self);
}
