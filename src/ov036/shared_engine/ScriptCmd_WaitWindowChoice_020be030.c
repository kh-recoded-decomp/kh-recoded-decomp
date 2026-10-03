#include "nitro/types.h"

typedef struct ScriptVm {
    u8 pad_000[0x628];
    s32 skipWait;
} ScriptVm;

extern void func_ov036_020bd9e0(void);
extern int GetTextWindowStatus_020c3080(void);
extern u32 PXI_Init_020c30d8(void);
extern void PXI_Init_020c3354(void);
extern void WriteSessionPackedBits_0206459c(int bitOffset, u32 bitCount, u32 value);

BOOL ScriptCmd_WaitWindowChoice_020be030(ScriptVm *vm)
{
    int status;

    if (vm->skipWait != 0) {
        func_ov036_020bd9e0();
        return TRUE;
    }
    status = GetTextWindowStatus_020c3080();
    switch (status) {
    case 0:
        WriteSessionPackedBits_0206459c(0x3521, 4, PXI_Init_020c30d8());
        func_ov036_020bd9e0();
        return TRUE;
    case 3:
        PXI_Init_020c3354();
        break;
    }
    return FALSE;
}
