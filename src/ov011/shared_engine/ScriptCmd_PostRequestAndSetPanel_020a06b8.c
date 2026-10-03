#include "nitro/types.h"

typedef struct ScriptOperand {
    u32 type;
    u32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt_02025de4(void *vm, ScriptOperand *op);
extern void PostPendingRequest_0207d630(u16 requestId, u8 requestArg);
extern void SetupSlotPanelMode_020640d8(int mode, int enable);

int ScriptCmd_PostRequestAndSetPanel_020a06b8(void *vm, ScriptOperand *op)
{
    int value = ScriptVm_ReadOperandInt_02025de4(vm, op);
    u16 requestId = op[1].value;
    u8 requestArg = (u16)(op[1].value >> 16);
    if (value != 0) {
        PostPendingRequest_0207d630(requestId, requestArg);
    }
    SetupSlotPanelMode_020640d8(2, value);
    return 1;
}
