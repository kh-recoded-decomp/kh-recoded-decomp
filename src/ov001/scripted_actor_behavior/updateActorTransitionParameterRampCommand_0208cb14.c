/* Behavior: Updates a script command that ramps an actor transition parameter over several frames.
 * Inputs/outputs and evidence: Reads actor/from/to/frame operands, decrements remaining frames, interpolates the parameter, requeues until complete, and returns completion status.
 * Uncertainty: Script operands and callees identify a script-driven actor transition; the meaning of mode 1 is not established.
 * Source: khdays-decomp/src/overlays/ov023/calls/func_ov023_020845a0.c; CC0, commit ab832f38b943c15f461228968a89002e1a99c03e.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef signed short   s16;

typedef struct ScriptOperand {
    s16  nType;
    u8   pad_02[6];
} ScriptOperand;

typedef struct ActorTransitionRampCommand {
    ScriptOperand operand[4];
    int  nField20;
    int  framesRemaining;
} ActorTransitionRampCommand;

extern int   func_02025de4(void *scriptContext, ScriptOperand *pOperand);
extern int   func_02025df8(void *scriptContext, ScriptOperand *pOperand);
extern void *func_02036240(u16 nEntity);
extern void  func_02036198(u16 nEntity, int bEnable, int parameterValue);
extern int   func_02025718(int nMode, int nTotal, int framesRemaining);
extern int   func_020257b0(int nFactor, int startParameter, int targetParameter);
extern void  func_02025e18(void *scriptContext, void *command);

int updateActorTransitionParameterRampCommand_0208cb14(void *scriptContext, ActorTransitionRampCommand *command)
{
    int actorId;
    int rampDurationFrames;
    int startParameter;
    int targetParameter;

    actorId = func_02025de4(scriptContext, &command->operand[0]);
    rampDurationFrames = func_02025de4(scriptContext, &command->operand[3]);
    startParameter = func_02025df8(scriptContext, &command->operand[1]);
    targetParameter = func_02025df8(scriptContext, &command->operand[2]);
    func_02036240((u16)actorId);
    command->framesRemaining--;
    if (command->framesRemaining == 0) {
        func_02036198((u16)actorId, 1, targetParameter);
        return 1;
    }
    func_02036198((u16)actorId, 1, func_020257b0(func_02025718(2, rampDurationFrames, command->framesRemaining), targetParameter, startParameter));
    func_02025e18(scriptContext, command);
    return 0;
}
