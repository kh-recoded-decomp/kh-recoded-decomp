#include "nitro/types.h"

extern u32 data_ov001_020a0478;
extern s32 func_ov001_02069030(void);
extern void func_01ff8684(u32 value, void *dest, u32 size);

void func_ov001_020691d4(void)
{
    s32 node;

    node = *(s32 *)(*(u32 *)(data_ov001_020a0478 + 0x34) + 4);
    while (node != 0) {
        if (*(u16 *)(node + 0x50) < 0xf8) {
            node = *(s32 *)(node + 4);
        } else {
            node = func_ov001_02069030();
        }
    }
    func_01ff8684(0xffff, (void *)data_ov001_020a0478, 0x10);
    *(u8 *)(data_ov001_020a0478 + 0x10) = 0;
}
