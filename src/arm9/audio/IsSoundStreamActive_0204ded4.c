#include "nitro/types.h"

extern u8 *g_soundWork_0206084c;
extern int func_02020320(void *handle);

BOOL IsSoundStreamActive_0204ded4(int handleIndex)
{
    int result = func_02020320(g_soundWork_0206084c + 0xb44c0 + handleIndex * 4);
    return result != 0;
}
