#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct ScriptContext ScriptContext;

typedef struct PathRequest {
    int target;
    u16 duration;
    u8 flags;
    s8 pointCount;
    s16 *pointsX;
    s16 *pointsY;
    int speed;
    int finish;
} PathRequest;

extern int ScriptVm_ReadOperandInt_02025de4(ScriptContext *context, ScriptOperand *operand);
extern void *NNSi_FndAllocFromDefaultHeapEx_0202a19c(u32 size, int align);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern void CreateFieldTaskNode_02069274(int actorId, BOOL immediate, int mode, PathRequest *request);

int ScriptCmd_QueueFlagTaskKind2_02065010(ScriptContext *context, ScriptOperand *operands)
{
    int immediate = ScriptVm_ReadOperandInt_02025de4(context, operands);
    int actorId = ScriptVm_ReadOperandInt_02025de4(context, operands + 1);
    PathRequest request;
    int i;

    request.target = ScriptVm_ReadOperandInt_02025de4(context, operands + 2);
    request.pointCount = ScriptVm_ReadOperandInt_02025de4(context, operands + 3);
    operands += 4;
    request.flags = ScriptVm_ReadOperandInt_02025de4(context, operands++);
    request.pointsX = NNSi_FndAllocFromDefaultHeapEx_0202a19c(request.pointCount * 2, -4);
    request.pointsY = NNSi_FndAllocFromDefaultHeapEx_0202a19c(request.pointCount * 2, -4);
    for (i = 0; i < request.pointCount; i++) {
        request.pointsX[i] = operands->value;
        request.pointsY[i] = (operands++)->value >> 16;
    }
    request.speed = ScriptVm_ReadOperandInt_02025de4(context, operands);
    request.duration = ScriptVm_ReadOperandInt_02025de4(context, operands + 1);
    request.finish = ScriptVm_ReadOperandInt_02025de4(context, operands + 2);
    CreateFieldTaskNode_02069274(actorId, immediate != 0, 2, &request);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(request.pointsY);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(request.pointsX);
    return 1;
}
