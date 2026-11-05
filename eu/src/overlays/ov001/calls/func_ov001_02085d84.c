#include "nitro/types.h"

extern void SetActorCommandTypeFromCommandId(int value);
extern void UnlinkPendingNode(void *ptr);

void func_ov001_02085d84(int state) {
    int packed = *(int *)(state + 0x58);
    SetActorCommandTypeFromCommandId((packed << 5) >> 0x15);
    UnlinkPendingNode(*(void **)(state + 0x74));
}
