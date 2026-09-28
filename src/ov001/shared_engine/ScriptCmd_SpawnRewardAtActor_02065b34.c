#include "nitro/types.h"

extern int ScriptVm_ReadOperandInt_02025de4(void *vm, void *operand);
extern void ResumeTaskAndClearFlags_02066780(void);
extern u8 *func_02036810(u16 actorId);
extern void func_ov001_02066514(u16 *amounts, void *position, int flags);

int ScriptCmd_SpawnRewardAtActor_02065b34(void *vm, u8 *operands) {
    int category = ScriptVm_ReadOperandInt_02025de4(vm, operands);
    int amount = ScriptVm_ReadOperandInt_02025de4(vm, operands + 8);
    int actorId = ScriptVm_ReadOperandInt_02025de4(vm, operands + 0x10);

    ResumeTaskAndClearFlags_02066780();
    {
        u16 amounts[6] = {0};
        u8 *actor = func_02036810(actorId);
        amounts[category] = amount;
        func_ov001_02066514(amounts, actor + 0xb8, 0);
    }
    return 0;
}
