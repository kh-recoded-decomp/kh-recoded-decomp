#include "nitro/types.h"

extern void ScriptCmd_ApplyOperandPair_020a0844(void);
extern void ScriptCmd_CreateEntryObjectInSlot_020a0520(void);
extern void ScriptCmd_CreateFieldTask_020a078c(void);
extern void ScriptCmd_EnterPhase_020a0650(void);
extern void ScriptCmd_EnterPhase_020a0874(void);
extern void ScriptCmd_ForceRequest_020a0690(void);
extern void ScriptCmd_PlayValueSequence_020a06b4(void);
extern void ScriptCmd_SetActorPath_020a0714(void);
extern void ScriptCmd_SetActorTarget_020a07f0(void);
extern void ScriptCmd_SetActorWander_020a05b8(void);
extern void ScriptCmd_ShowActorEmote_020a057c(void);
extern void func_ov007_020a0660(void);

void (*data_ov007_020a1c00[23])(void) = {
    ScriptCmd_CreateEntryObjectInSlot_020a0520,
    NULL,
    ScriptCmd_ShowActorEmote_020a057c,
    NULL,
    ScriptCmd_SetActorWander_020a05b8,
    NULL,
    ScriptCmd_EnterPhase_020a0650,
    NULL,
    func_ov007_020a0660,
    NULL,
    ScriptCmd_ForceRequest_020a0690,
    NULL,
    ScriptCmd_PlayValueSequence_020a06b4,
    NULL,
    ScriptCmd_SetActorPath_020a0714,
    NULL,
    ScriptCmd_CreateFieldTask_020a078c,
    NULL,
    ScriptCmd_SetActorTarget_020a07f0,
    NULL,
    ScriptCmd_ApplyOperandPair_020a0844,
    NULL,
    ScriptCmd_EnterPhase_020a0874,
};
