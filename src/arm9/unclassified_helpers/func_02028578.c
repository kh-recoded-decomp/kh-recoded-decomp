#include "nitro/types.h"

extern void *g_ptr_0205fe24;
extern void *func_02029f48(void);
extern int func_0202198c(void *value);

BOOL func_02028578(void) {
    void *value = func_02029f48();
    *(void **)((u8 *)g_ptr_0205fe24 + 0x9c) = value;
    if (func_0202198c(*(void **)((u8 *)g_ptr_0205fe24 + 0x9c)) == 0) {
        return 1;
    }
    return 0;
}
