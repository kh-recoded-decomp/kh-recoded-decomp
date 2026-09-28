#include "nitro/types.h"

extern void ReleaseResourceAndDetach_0202eee8(void *object);
extern void func_0202a1c4(void *ptr);

void ReleaseAndFreeResource_020a2abc(int self) {
    if (*(void **)(self + 0x48) != NULL) {
        ReleaseResourceAndDetach_0202eee8(*(void **)(self + 0x48));
        func_0202a1c4(*(void **)(self + 0x48));
        *(void **)(self + 0x48) = NULL;
    }
}
