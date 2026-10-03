#include "nitro/types.h"

extern void *NNSi_FndAllocFromDefaultHeapEx_0202a19c(u32 size, int align);
extern void func_0202ed9c(void *object, u16 *counter, int arg, int count);
extern void RebindAnimTracks_020809d0(void *anim, int blendIndex, int frame);
extern void func_0202f4d8(void *object);

void CreateFieldModelObject_020a26e8(void **out, u16 *counter, int arg)
{
    *out = NNSi_FndAllocFromDefaultHeapEx_0202a19c(0x104, 4);
    func_0202ed9c(*out, counter, arg, 4);
    RebindAnimTracks_020809d0(*out, 0, 0);
    func_0202f4d8(*out);
    (*counter)++;
}
