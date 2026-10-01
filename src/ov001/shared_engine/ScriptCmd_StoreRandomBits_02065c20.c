#include "nitro/types.h"

typedef struct ScriptCmd {
    u32 opcode;
    u32 bitField;
    u8 operand[1];
} ScriptCmd;

extern int ScriptVm_ReadOperandInt_02025de4(void *vm, void *operand);
extern u32 func_0202a9d0(u32 range);
extern void WriteSessionPackedBits_0206459c(int bitOffset, u32 bitCount, u32 value);

BOOL ScriptCmd_StoreRandomBits_02065c20(void *vm, ScriptCmd *cmd)
{
    u32 bitField = cmd->bitField;
    u32 value = func_0202a9d0((u16)ScriptVm_ReadOperandInt_02025de4(vm, cmd->operand));

    WriteSessionPackedBits_0206459c((u16)bitField, (u8)(u16)(bitField >> 16), value);
    return TRUE;
}
