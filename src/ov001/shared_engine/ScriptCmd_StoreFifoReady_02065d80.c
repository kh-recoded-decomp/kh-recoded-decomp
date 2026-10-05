#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    u32 value;
} ScriptOperand;

typedef struct ScriptContext ScriptContext;

extern int ScriptVm_ReadOperandInt_02025de4(ScriptContext *context, ScriptOperand *operand);
extern void *PXI_Init_02064a30(void);
extern void WriteSessionPackedBits_0206459c(u16 bitOffset, u8 bitCount, u32 value);

BOOL ScriptCmd_StoreFifoReady_02065d80(ScriptContext *context, ScriptOperand *operands)
{
    u32 field = operands[0].value;
    u16 bitOffset = field;
    u8 bitCount = (u16)(field >> 16);
    BOOL ready;

    ScriptVm_ReadOperandInt_02025de4(context, &operands[1]);
    if (PXI_Init_02064a30() != NULL) {
        ready = TRUE;
    } else {
        ready = FALSE;
    }
    WriteSessionPackedBits_0206459c(bitOffset, bitCount, ready);
    return TRUE;
}
