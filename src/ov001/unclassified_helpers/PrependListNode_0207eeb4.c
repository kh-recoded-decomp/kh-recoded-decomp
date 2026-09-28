#include "nitro/types.h"

extern u32 data_ov001_020a04d8;
extern void *func_ov001_0207f038();
extern void func_ov001_0207f4c0(void *node, u32 param3);

void PrependListNode_0207eeb4(u32 param1, u32 param2, u32 param3)
{
    u8 *node;

    node = func_ov001_0207f038();
    *(u16 *)(node + 0x4e) = *(u16 *)(node + 0x4e) | 2;
    *(u8 **)(node + 4) = *(u8 **)(data_ov001_020a04d8 + 8);
    *(u8 **)node = 0;
    if (*(u8 **)(data_ov001_020a04d8 + 8) != 0) {
        *(u8 **)*(u8 **)(data_ov001_020a04d8 + 8) = node;
    }
    *(u8 **)(data_ov001_020a04d8 + 8) = node;
    func_ov001_0207f4c0(node, param3);
}
