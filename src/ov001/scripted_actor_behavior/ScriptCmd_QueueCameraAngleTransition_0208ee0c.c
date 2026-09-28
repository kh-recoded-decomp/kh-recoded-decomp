#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    u8 payload[6];
} ScriptOperand;

extern int ScriptVm_ReadOperandInt_02025de4(void *context, ScriptOperand *operand);
extern void ActorChannel_QueueRequest_0208bcc0(u32 frameCount, u32 angle);

int ScriptCmd_QueueCameraAngleTransition_0208ee0c(void *context, ScriptOperand *operands)
{
    int angleDegrees = ScriptVm_ReadOperandInt_02025de4(context, operands);
    u32 frameCount = ScriptVm_ReadOperandInt_02025de4(context, operands + 1);

    ActorChannel_QueueRequest_0208bcc0(frameCount, angleDegrees * 0xb6);
    return 1;
}
