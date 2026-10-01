#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt_02025de4(void *context, ScriptOperand *operand);
extern int func_ov001_02088064(u16 actorId);
extern void func_ov001_02088080(u16 eventId, u16 animationId);
extern void func_ov001_0208808c(u16 eventId, s32 layer, u16 animationId, s32 option, BOOL persistent);

int ScriptCmd_PlayStageEventAnimation_0208ec70(void *context, ScriptOperand *operands)
{
    int actorId;
    int animationId;
    int option;
    int eventId;

    actorId = ScriptVm_ReadOperandInt_02025de4(context, &operands[0]);
    animationId = ScriptVm_ReadOperandInt_02025de4(context, &operands[1]);
    option = ScriptVm_ReadOperandInt_02025de4(context, &operands[2]);
    eventId = func_ov001_02088064(actorId);
    func_ov001_02088080(eventId, animationId);
    func_ov001_0208808c(eventId, 0, animationId, option, TRUE);
    return 1;
}
