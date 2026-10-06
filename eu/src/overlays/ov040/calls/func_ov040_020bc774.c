#include "nitro/types.h"

extern u8 sOv040_BugcolFormat02d_020be22c;
extern void *OS_SPrintf();
extern int strlen();
extern void ApplyToNamedCollisionFaces();

void func_ov040_020bc774(u32 firstArg, int count, u32 unusedArg, u32 secondArg)
{
    int length;
    u8 buffer[16];
    u32 secondArgSlot;

    secondArgSlot = secondArg;
    OS_SPrintf(buffer, &sOv040_BugcolFormat02d_020be22c, firstArg);
    length = strlen(buffer);
    ApplyToNamedCollisionFaces(buffer, length, 1 < count);
}
