#include "nitro/types.h"

extern void func_0202a1c4(void *ptr);

void func_ov001_02085d4c(int state) {
    void *handle = *(void **)(state + 0x74);
    func_0202a1c4(handle);
    *(void **)(state + 0x74) = 0;
}
