#include "nitro/types.h"

extern void ScriptCmd_CreateObjectAtPosition_020a054c(void);
extern void ScriptCmd_CreateObjectInSlot_020a0520(void);
extern void ScriptCmd_SetObjectElementFlag_020a05c0(void);
extern void ScriptCmd_SetObjectElementState_020a05f8(void);

void (*data_ov009_020a0c40[7])(void) = {
    ScriptCmd_CreateObjectInSlot_020a0520,
    NULL,
    ScriptCmd_CreateObjectAtPosition_020a054c,
    NULL,
    ScriptCmd_SetObjectElementFlag_020a05c0,
    NULL,
    ScriptCmd_SetObjectElementState_020a05f8,
};
