#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x18];
    void *bufferA;
    void *bufferB;
    void *bufferC;
} DataBuffers;

extern void func_0202a1c4(void);

void Obj_FreeDataBuffers_02034ff0(DataBuffers *obj)
{
    if (obj->bufferA != 0) {
        func_0202a1c4();
        obj->bufferA = 0;
    }
    if (obj->bufferB != 0) {
        func_0202a1c4();
        obj->bufferB = 0;
    }
    if (obj->bufferC == 0) {
        return;
    }
    func_0202a1c4();
    obj->bufferC = 0;
}
