#include "nitro/types.h"

extern void FreeResourceBufferAndProbeHeap(u32 context);

void func_ov001_0206f1dc(u32 context)
{
    FreeResourceBufferAndProbeHeap(context + 0x9c);
    FreeResourceBufferAndProbeHeap(context + 0x78);
    FreeResourceBufferAndProbeHeap(context + 0x84);
    FreeResourceBufferAndProbeHeap(context + 0x90);
}
