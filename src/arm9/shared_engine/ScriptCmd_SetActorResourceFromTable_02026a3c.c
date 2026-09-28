#include "nitro/types.h"

extern int ScriptVm_ReadOperandInt_02025de4(void *ctx, void *cmd);
extern s32 ScriptCmd_ReturnValue_02025960(void *ctx, s32 value);
extern u32 func_ov001_0207ee14(int entryIndex);
extern u32 func_ov001_0207ee48(int entryIndex);
extern void func_02026a00(int actorIndex, u32 resourceFileId, u32 dataFileId);

int ScriptCmd_SetActorResourceFromTable_02026a3c(void *ctx, void *cmd)
{
    int actorOperand = ScriptVm_ReadOperandInt_02025de4(ctx, cmd);
    int entryIndex = ScriptVm_ReadOperandInt_02025de4(ctx, (u8 *)cmd + 8);
    int actorIndex = ScriptCmd_ReturnValue_02025960(ctx, actorOperand);
    u32 resourceFileId = func_ov001_0207ee14(entryIndex);
    u32 dataFileId = func_ov001_0207ee48(entryIndex);

    func_02026a00(actorIndex, resourceFileId, dataFileId);
    return 1;
}
