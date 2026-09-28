#include "nitro/types.h"

extern void func_ov059_020cd364(int value);
extern void func_ov031_020bc618(void *ptr);

void func_ov001_02085d5c(int state) {
    int packed = *(int *)(state + 0x58);
    func_ov059_020cd364((packed << 5) >> 0x15);
    func_ov031_020bc618(*(void **)(state + 0x74));
}
