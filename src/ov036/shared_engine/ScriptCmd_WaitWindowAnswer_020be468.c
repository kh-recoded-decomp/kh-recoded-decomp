#include "nitro/types.h"

typedef struct ScriptOperand {
    u32 words[2];
} ScriptOperand;

extern int GetTextWindowStatus_020c3080(void);
extern int ScriptVm_ReadOperandInt_02025de4(void *vm, ScriptOperand *operand);
extern int PXI_Init_020c30d8(void);
extern BOOL func_ov001_020645c8(u32 bitOffset);
extern void WriteSessionPackedBits_0206459c(int bitOffset, u32 bitCount, u32 value);
extern void func_ov036_020bd9e0(void);
extern void PXI_Init_020c3354(void);

BOOL ScriptCmd_WaitWindowAnswer_020be468(void *vm, ScriptOperand *operands)
{
    int expected;
    int choice;

    switch (GetTextWindowStatus_020c3080()) {
    case 0:
        expected = ScriptVm_ReadOperandInt_02025de4(vm, &operands[2]);
        choice = PXI_Init_020c30d8();
        if (func_ov001_020645c8(choice + 0x3700)) {
            if (choice == expected) {
                WriteSessionPackedBits_0206459c(0x3521, 4, 2);
            } else {
                WriteSessionPackedBits_0206459c(0x3521, 4, 1);
            }
        } else {
            WriteSessionPackedBits_0206459c(0x3521, 4, 0);
        }
        func_ov036_020bd9e0();
        return TRUE;
    case 3:
        PXI_Init_020c3354();
        break;
    }
    return FALSE;
}
