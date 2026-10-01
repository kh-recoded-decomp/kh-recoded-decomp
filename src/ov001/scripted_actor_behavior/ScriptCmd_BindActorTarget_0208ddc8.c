#include "nitro/types.h"

typedef struct ScriptActor {
    u8 pad_00[0xb4];
    void *target;
} ScriptActor;

typedef struct ScriptElem {
    u8 handleOperand[4];
    u32 actorId;
    u8 valueOperand[0x10];
    s16 state;
    u8 pad_1A[2];
    int mode;
    u8 pad_20[4];
    int value;
    u8 pad_28[4];
    void *target;
} ScriptElem;

extern int ScriptVm_ReadOperandInt_02025de4(void *vm, void *operand);
extern s32 ScriptCmd_ReturnValue_02025960(void *vm, s32 value);
extern ScriptActor *func_02036240(u16 id);
extern void ScriptCmd_SetElemField_02025e18(void *vm, ScriptElem *elem);
extern u32 ScriptCmd_SetElemFieldIfFlagSet_0208de1c(void *vm, ScriptElem *elem);

void ScriptCmd_BindActorTarget_0208ddc8(void *vm, ScriptElem *elem)
{
    int handle = ScriptVm_ReadOperandInt_02025de4(vm, elem->handleOperand);
    int value = ScriptVm_ReadOperandInt_02025de4(vm, elem->valueOperand);
    u32 actorId = ScriptCmd_ReturnValue_02025960(vm, handle);

    elem->actorId = actorId;
    elem->value = value;
    elem->target = func_02036240(actorId)->target;
    if (elem->state == 0) {
        elem->mode = 2;
        elem->state = 1;
    }
    ScriptCmd_SetElemField_02025e18(vm, elem);
    ScriptCmd_SetElemFieldIfFlagSet_0208de1c(vm, elem);
}
