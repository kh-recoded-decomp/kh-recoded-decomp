#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *context, ScriptOperand *operand);
extern void StartActorFocusTransition(int entryId, int direction, int duration);

int PanelScriptCmd_StartActorFocusTransition(void *context, ScriptOperand *operands)
{
    int entryId = ScriptVm_ReadOperandInt(context, &operands[0]);
    int direction = ScriptVm_ReadOperandInt(context, &operands[1]);
    int duration = ScriptVm_ReadOperandInt(context, &operands[2]);

    StartActorFocusTransition(entryId, direction, duration);
    return 0;
}
