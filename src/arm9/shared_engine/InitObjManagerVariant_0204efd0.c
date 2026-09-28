#include "nitro/types.h"

extern void func_01ff8830(void *dest, u32 value, u32 size);
extern u32 func_0204ef3c(int manager, u32 *config);

void InitObjManagerVariant_0204efd0(int manager, u32 *config)
{
    func_01ff8830((void *)manager, 0, 0x6434);
    *(u32 *)(manager + 0x6020) = 1;
    func_0204ef3c(manager, config);
}
