#include "nitro/types.h"

extern void ClearFixedSlots_020a0670(void);
extern void ScriptCmd_PostCrawlScoreLine_020a06a4(void);
extern void ScriptCmd_PostRequestAndSetPanel_020a06b8(void);
extern void ScriptCmd_ShuffleEntryPositions_020a0520(void);
extern void ScriptCmd_SpawnActorInSlot_020a0560(void);
extern void ScriptCmd_SpawnFieldObject_020a058c(void);

void (*data_ov011_020a1160[11])(void) = {
    ScriptCmd_ShuffleEntryPositions_020a0520,
    NULL,
    ScriptCmd_SpawnActorInSlot_020a0560,
    NULL,
    ScriptCmd_SpawnFieldObject_020a058c,
    NULL,
    ClearFixedSlots_020a0670,
    NULL,
    ScriptCmd_PostCrawlScoreLine_020a06a4,
    NULL,
    ScriptCmd_PostRequestAndSetPanel_020a06b8,
};
