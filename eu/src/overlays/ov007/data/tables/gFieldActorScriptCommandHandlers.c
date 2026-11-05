#include "nitro/types.h"

extern void ScriptCmd_CreateEntryObjectInSlot(void); /* ScriptCmd_CreateEntryObjectInSlot */
extern void ScriptCmd_ShowActorEmote(void); /* ScriptCmd_ShowActorEmote */
extern void ScriptCmd_SetActorWander(void); /* ScriptCmd_SetActorWander */
extern void ScriptCmd_CommitSideResult(void); /* ScriptCmd_EnterPhase */
extern void ScriptCmd_SetAreaSceneDefinitionParams(void);
extern void ScriptCmd_ForceRequest(void); /* ScriptCmd_ForceRequest */
extern void ScriptCmd_PlayValueSequence(void); /* ScriptCmd_PlayValueSequence */
extern void ScriptCmd_SetActorPath(void); /* ScriptCmd_SetActorPath */
extern void ScriptCmd_CreateFieldTask(void); /* ScriptCmd_CreateFieldTask */
extern void ScriptCmd_SetActorTarget(void); /* ScriptCmd_SetActorTarget */
extern void ScriptCmd_ApplyOperandPair(void); /* ScriptCmd_ApplyOperandPair */
extern void ScriptCmd_ResetAreaSceneSelectionFlags(void); /* ScriptCmd_EnterPhase */

void (*gFieldActorScriptCommandHandlers[23])(void) = {
    ScriptCmd_CreateEntryObjectInSlot, /* ScriptCmd_CreateEntryObjectInSlot */
    NULL,
    ScriptCmd_ShowActorEmote, /* ScriptCmd_ShowActorEmote */
    NULL,
    ScriptCmd_SetActorWander, /* ScriptCmd_SetActorWander */
    NULL,
    ScriptCmd_CommitSideResult, /* ScriptCmd_EnterPhase */
    NULL,
    ScriptCmd_SetAreaSceneDefinitionParams,
    NULL,
    ScriptCmd_ForceRequest, /* ScriptCmd_ForceRequest */
    NULL,
    ScriptCmd_PlayValueSequence, /* ScriptCmd_PlayValueSequence */
    NULL,
    ScriptCmd_SetActorPath, /* ScriptCmd_SetActorPath */
    NULL,
    ScriptCmd_CreateFieldTask, /* ScriptCmd_CreateFieldTask */
    NULL,
    ScriptCmd_SetActorTarget, /* ScriptCmd_SetActorTarget */
    NULL,
    ScriptCmd_ApplyOperandPair, /* ScriptCmd_ApplyOperandPair */
    NULL,
    ScriptCmd_ResetAreaSceneSelectionFlags, /* ScriptCmd_EnterPhase */
};
