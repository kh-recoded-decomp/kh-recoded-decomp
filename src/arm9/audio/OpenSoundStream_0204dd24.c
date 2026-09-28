#include "nitro/types.h"

extern u8 *g_soundWork_0206084c;
extern BOOL func_02020240(void *handle, int strmNo, u32 offset);

void OpenSoundStream_0204dd24(int handleIndex, int strmNo)
{
    func_02020240(g_soundWork_0206084c + 0xb44c0 + handleIndex * 4, strmNo, 0);
}
