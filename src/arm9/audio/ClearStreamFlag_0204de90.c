#include "nitro/types.h"

extern u8 *g_soundWork_0206084c;

void ClearStreamFlag_0204de90(int index)
{
    *(u8 *)(g_soundWork_0206084c + index * 8 + 0xb44ce) = 0;
}
