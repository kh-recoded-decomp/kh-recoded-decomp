#include "nitro/types.h"

extern u8 data_ov040_020be20c;
extern void *OS_SPrintf_02002428();
extern int Strlen_02021e44();
extern void func_ov001_020680fc();

void func_ov040_020bc754(u32 firstArg, int count, u32 unusedArg, u32 secondArg)
{
    int length;
    u8 buffer[16];
    u32 secondArgSlot;

    secondArgSlot = secondArg;
    OS_SPrintf_02002428(buffer, &data_ov040_020be20c, firstArg);
    length = Strlen_02021e44(buffer);
    func_ov001_020680fc(buffer, length, 1 < count);
}
