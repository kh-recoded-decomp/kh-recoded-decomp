#include "nitro/types.h"

typedef struct ScriptOperand {
    u32 words[2];
} ScriptOperand;

typedef struct ScriptVm {
    u8 pad_000[0x628];
    s32 skipWait;
} ScriptVm;

typedef struct PanelPoint {
    s32 x;
    s32 y;
} PanelPoint;

extern int ScriptVm_ReadOperandInt_02025de4(ScriptVm *vm, ScriptOperand *operand);
extern int func_0202b788(void);
extern void SetPanelCursorOverride_020bd9a4(s32 selection, PanelPoint *position);

BOOL ScriptCmd_SetCursorOverride_020be7d4(ScriptVm *vm, ScriptOperand *operands)
{
    int target = ScriptVm_ReadOperandInt_02025de4(vm, &operands[0]);
    int selection = ScriptVm_ReadOperandInt_02025de4(vm, &operands[1]);
    PanelPoint position;

    position.x = ScriptVm_ReadOperandInt_02025de4(vm, &operands[2]);
    position.y = ScriptVm_ReadOperandInt_02025de4(vm, &operands[3]);
    if (vm->skipWait != 0) {
        return TRUE;
    }
    if (target != func_0202b788() - 1) {
        return TRUE;
    }
    SetPanelCursorOverride_020bd9a4(selection, &position);
    return TRUE;
}
