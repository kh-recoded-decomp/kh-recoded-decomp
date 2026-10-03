#include "nitro/types.h"

typedef struct {
    u32 type;
    u32 value;
} ScriptOperand;

typedef struct {
    s16 node;
    u8 speed;
    u8 wait;
} PathNode;

extern int ScriptVm_ReadOperandInt_02025de4(void *vm, ScriptOperand *operand);
extern void *func_ov001_0207f028(int actorId);
extern void SetPathTable_020a1ad4(void *set, int index, int count, const PathNode *nodes);

BOOL ScriptCmd_SetActorPath_020a0714(void *vm, ScriptOperand *op) {
    int actorId = ScriptVm_ReadOperandInt_02025de4(vm, op++);
    int pathIndex = ScriptVm_ReadOperandInt_02025de4(vm, op++);
    int count = ScriptVm_ReadOperandInt_02025de4(vm, op++);
    PathNode nodes[32];
    int i;

    for (i = 0; i < count; i++) {
        nodes[i].node = ScriptVm_ReadOperandInt_02025de4(vm, op++);
        nodes[i].speed = ScriptVm_ReadOperandInt_02025de4(vm, op++);
        nodes[i].wait = ScriptVm_ReadOperandInt_02025de4(vm, op++);
    }
    SetPathTable_020a1ad4(func_ov001_0207f028(actorId), pathIndex, count, nodes);
    return TRUE;
}
