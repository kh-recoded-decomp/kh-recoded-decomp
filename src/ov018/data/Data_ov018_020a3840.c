#include "nitro/types.h"

extern void ScriptCmd_CreateGroupObject_020a1e10(void);
extern void ScriptCmd_CreateSlotObject_020a1de0(void);

void (*data_ov018_020a3840[4])(void) = {
    ScriptCmd_CreateSlotObject_020a1de0,
    NULL,
    ScriptCmd_CreateGroupObject_020a1e10,
    NULL,
};
