#include "nitro/types.h"

extern void func_ov059_020cd384(int value);
extern void UnlinkPendingNode(void *ptr);

void func_ov001_02085d84(int state) {
    int packed = *(int *)(state + 0x58);
    func_ov059_020cd384((packed << 5) >> 0x15);
    UnlinkPendingNode(*(void **)(state + 0x74));
}
