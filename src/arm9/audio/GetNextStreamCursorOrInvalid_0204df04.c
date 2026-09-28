#include "nitro/types.h"

extern u8 *g_soundWork_0206084c;
extern int func_02020320(void *handle);
extern u32 func_02020354(void *handle);

u32 GetNextStreamCursorOrInvalid_0204df04(int handleIndex)
{
    u32 next = func_02020320(g_soundWork_0206084c + 0xb44c0 + handleIndex * 4) + 1;
    u32 limit = func_02020354(g_soundWork_0206084c + 0xb44c0 + handleIndex * 4);

    if (next >= limit) {
        next = 0xffffffff;
    }
    return next;
}
