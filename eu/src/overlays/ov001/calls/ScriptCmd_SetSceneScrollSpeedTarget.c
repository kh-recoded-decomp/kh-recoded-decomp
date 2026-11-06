#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct {
    ScriptOperand operands[2];
} ScriptCommand;

extern int ScriptVm_ReadOperandInt(void *context, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32(void *context, ScriptOperand *operand);
extern u32 GetCurrentRecordTargetScrollSpeed(void);
extern void SetSceneScrollSpeedTarget(u32 a, u32 b);

int ScriptCmd_SetSceneScrollSpeedTarget(void *context, ScriptCommand *command)
{
    int useCurrent = ScriptVm_ReadOperandInt(context, &command->operands[0]);
    fx32 amount = ScriptVm_ReadOperandFx32(context, &command->operands[1]);

    SetSceneScrollSpeedTarget(useCurrent != 0 ? GetCurrentRecordTargetScrollSpeed() : 0, amount);
    return 1;
}
