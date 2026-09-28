#include "nitro/types.h"

extern int func_02009ebc(void *rom, u32 dst, u32 src, u32 length,
                          void (*callback)(void *arc), void *arc, int mode);
extern void FS_CompleteArchiveAsyncRequest_0200d2b4(void *arc);
extern void *data_02057b1c;

int FSi_ReadRomCallback_0200d2d8(void *arc, u32 src, u32 dst, u32 length)
{
    func_02009ebc(data_02057b1c, dst, src, length, FS_CompleteArchiveAsyncRequest_0200d2b4, arc, 1);
    return 0x100;
}
