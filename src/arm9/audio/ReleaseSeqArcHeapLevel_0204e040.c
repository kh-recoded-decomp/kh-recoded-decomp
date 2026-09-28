#include "nitro/types.h"

extern u8 *g_soundWork_0206084c;
extern void func_0201f1a4(void *heap, s32 level);

void ReleaseSeqArcHeapLevel_0204e040(int index)
{
    s32 level = *(s32 *)(g_soundWork_0206084c + index * 4 + 0xa8);

    if (level < 0) {
        return;
    }
    func_0201f1a4(*(void **)(g_soundWork_0206084c + 0xb04b4), level);
}
