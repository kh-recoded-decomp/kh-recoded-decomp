/* Stores a converted script value in the selected actor's observed +0x80
 * halfword and, under object state checks, mirrors it through an ov001 helper.
 * The value's units and visible gameplay effect remain unknown. */
typedef struct ScriptOperand { short type; unsigned char payload[6]; } ScriptOperand;
typedef struct ActorNode {
    unsigned int flags_000;
    unsigned short flags_004;
    unsigned char reserved_006[0x76];
    unsigned int modelResource;
    unsigned short halfword_080;
} ActorNode;
extern int func_02025de4(void *scriptContext, ScriptOperand *operand);
extern int func_02025960(void *scriptContext, int actorId);
extern int func_02023dbc(int fixedValue, int divisorOrScale);
extern ActorNode *func_02036240(unsigned short actorId);
extern void func_ov001_0208a2fc(void *object, unsigned short value);

int Script_SetActorParameterFromInteger_0208cbb4(void *scriptContext, ScriptOperand *commandOperands)
{
    int actorId = func_02025de4(scriptContext, commandOperands);
    int scriptValue = func_02025de4(scriptContext, commandOperands + 1);
    unsigned int resolvedActorId = (unsigned int)func_02025960(scriptContext, actorId);
    unsigned int scaledScriptValue = (unsigned int)scriptValue << 16;
    unsigned short convertedValue = (unsigned short)func_02023dbc((int)scaledScriptValue, 0x168);
    ActorNode *actorNode = func_02036240((unsigned short)resolvedActorId);
    if ((actorNode->flags_000 & 0x20) == 0) {
        actorNode->halfword_080 = convertedValue;
        actorNode->flags_004 |= 0x20;
    }
    void *actorObject = (void *)*(int *)(*(int *)(*(int *)((char *)scriptContext + 0x1c8) + 0x4c) +
                                          resolvedActorId * 4);
    if (actorObject != 0 && (*(int *)((char *)actorObject + 0xd18) != 0 ||
                             (*(unsigned int *)((char *)actorObject + 0xef4) & 0x4000) != 0)) {
        func_ov001_0208a2fc(actorObject, convertedValue);
    }
    return 1;
}
