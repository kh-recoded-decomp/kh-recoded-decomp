#include "nitro/types.h"

extern void ScriptCmd_CreateSlotObjectKind5_020a1de0(void);
extern void ScriptCmd_SpawnLinkedObject_020a1e10(void);

void (*data_ov019_020a3680[4])(void) = {
    ScriptCmd_CreateSlotObjectKind5_020a1de0,
    NULL,
    ScriptCmd_SpawnLinkedObject_020a1e10,
    NULL,
};
