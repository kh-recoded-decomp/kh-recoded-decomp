#include "nitro/types.h"

extern int func_ov001_0209c584(int kind);
extern void func_ov001_0209c5b0(int errorCode);

int AllocateActorSlotOrReportError_02093ae0(void)
{
    if (func_ov001_0209c584(1) == 0) {
        func_ov001_0209c5b0(0x30);
        return 3;
    }
    return 0;
}
