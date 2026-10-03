#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x14];
    u32 packedArgs;
} ScriptCommand;

extern int ScriptVm_ReadOperandInt_02025de4(void *vm, void *operand);
extern void *func_ov001_0207f028(int actorId);
extern void func_ov007_020a183c(void *actor, u16 emoteId, u16 duration, u8 flags);

BOOL ScriptCmd_ShowActorEmote_020a057c(void *vm, ScriptCommand *cmd) {
    int actorId = ScriptVm_ReadOperandInt_02025de4(vm, cmd);
    int emoteId = ScriptVm_ReadOperandInt_02025de4(vm, (u8 *)cmd + 8);
    u32 packed = cmd->packedArgs;

    func_ov007_020a183c(func_ov001_0207f028(actorId), emoteId, packed, (u16)(packed >> 16));
    return TRUE;
}
