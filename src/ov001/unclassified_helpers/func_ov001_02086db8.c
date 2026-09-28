#include "nitro/types.h"

extern void func_0202a1c4(void *ptr);
extern void func_ov001_020868d0(int arg);
extern u32 data_ov001_020a04dc;

void func_ov001_02086db8(void) {
    u32 base = data_ov001_020a04dc;
    int i = 0;
    func_ov001_020868d0(0);
    do {
        void *entry = *(void **)(base + i * 8 + 0x13c);
        if (entry != 0) {
            func_0202a1c4(entry);
        }
        i = i + 1;
    } while (i < 8);
    func_0202a1c4((void *)data_ov001_020a04dc);
    data_ov001_020a04dc = 0;
}
