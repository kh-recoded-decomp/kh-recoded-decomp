#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct ScriptContext ScriptContext;

typedef struct TargetViewDesc {
    int actorKind;
} TargetViewDesc;

extern int ScriptVm_ReadOperandInt(ScriptContext *context, ScriptOperand *operand);
extern void *CreateTargetViewClass(u16 count, const TargetViewDesc *desc);
extern void func_ov001_0207ee2c(int index, void *entry);

BOOL ScriptCmd_CreateTargetViewInSlot(ScriptContext *context, ScriptOperand *operands)
{
    int slot;
    int count;
    TargetViewDesc desc;

    slot = ScriptVm_ReadOperandInt(context, &operands[0]);
    count = ScriptVm_ReadOperandInt(context, &operands[1]);
    desc.actorKind = ScriptVm_ReadOperandInt(context, &operands[2]);
    func_ov001_0207ee2c(slot, CreateTargetViewClass((u16)count, &desc));
    return TRUE;
}
