#include "nitro/types.h"

int ClassifyBranchInsn_020d25e4(u32 insn)
{
    u8 top = insn >> 24;
    if ((top & 0xe) == 0xa) {
        if ((top & 0xf0) == 0xf0) {
            return 1;
        }
        return (top & 1) ? 2 : 3;
    }
    return 0;
}
