#include "nitro/types.h"

extern u32 Obj_FreeDataBuffers();
extern u32 FSi_DefaultStepDoneA();
extern u32 FreeFieldObjectShapeStorage();

void
ReleaseFieldObjectDataAndShape(int self)
{
    Obj_FreeDataBuffers(self + 0xa0);
    FSi_DefaultStepDoneA(*(int *)(self + 0xc) + 0x1a8);
    FreeFieldObjectShapeStorage(self);
}
