#include "nitro/types.h"

int func_ov036_020bb8cc(int blockIndex) {
    int size = (0x100 - blockIndex) * 0x1000;
    if (blockIndex > 0xc0) {
        size = size + 0x40000;
    }
    return size;
}
