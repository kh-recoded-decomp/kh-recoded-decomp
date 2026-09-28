#include "nitro/types.h"

extern void *func_0202a178(u32 size);
extern void func_01ff8740(u32 fillValue, void *dest, u32 size);
extern void func_01ff878c(void *src, void *dest, u32 size);

void func_ov001_02073cb0(void **outBuffer, void *source, u32 size)
{
    void *buffer;

    buffer = func_0202a178(size);
    *outBuffer = buffer;
    if (source == 0) {
        func_01ff8740(0, buffer, size);
        return;
    }
    func_01ff878c(source, buffer, size);
}
