#include "nitro/types.h"

#define REG_POWCNT1 (*(volatile u16 *)0x04000304)

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt_02025de4(void *context, ScriptOperand *operand);
extern int func_ov001_0206e690(int index);
extern void WriteSessionPackedBits_0206459c(int bitOffset, u32 bitCount, u32 value);
extern void func_020365a4(void);

int ScriptCmd_SetScreenSwap_0208d22c(void *context, ScriptOperand *operands)
{
    switch (ScriptVm_ReadOperandInt_02025de4(context, operands)) {
    case 0:
        REG_POWCNT1 = REG_POWCNT1 | 0x8000;
        break;
    case 1:
        REG_POWCNT1 = REG_POWCNT1 & ~0x8000;
        break;
    }
    WriteSessionPackedBits_0206459c(0x351f, 1, func_ov001_0206e690(0));
    func_020365a4();
    return 1;
}
