/* Reads one actor ID and three script values, then forwards the selected actor
 * and values to its ov001 animation/state routine. The specific animation mode
 * represented by the operands is not established. */
typedef struct ScriptOperand { short type; unsigned char payload[6]; } ScriptOperand;
extern int func_02025de4(void *scriptContext, ScriptOperand *operand);
extern int func_02025dac(void *scriptContext, ScriptOperand *operand);
extern int func_02025960(void *scriptContext, int actorId);
extern void func_ov001_0208a848(void *actor, int animationArgument, int animationIndex, int enabled);

int Script_ApplyActorAnimationState_0208de3c(void *scriptContext, ScriptOperand *commandOperands)
{
    int actorId = func_02025de4(scriptContext, commandOperands);
    int animationArgument = func_02025dac(scriptContext, commandOperands + 1);
    int animationIndex = func_02025de4(scriptContext, commandOperands + 2);
    int enabled = func_02025de4(scriptContext, commandOperands + 3) != 0;
    int resolvedActorId = func_02025960(scriptContext, actorId);
    void *actor = *(void **)(*(int *)(*(int *)((char *)scriptContext + 0x1c8) + 0x4c) + resolvedActorId * 4);
    func_ov001_0208a848(actor, animationArgument, animationIndex, enabled);
    return 1;
}
