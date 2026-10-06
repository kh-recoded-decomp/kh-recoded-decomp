#include "nitro/types.h"

extern u32 Obj_FreeDataBuffers();
extern u32 FSi_DefaultStepDoneA();
extern u32 func_ov001_0207f26c();

void
func_ov001_02084d84(int self)
{
    Obj_FreeDataBuffers(self + 0xa0);
    FSi_DefaultStepDoneA(*(int *)(self + 0xc) + 0x1a8);
    func_ov001_0207f26c(self);
}
