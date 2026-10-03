#include "nitro/types.h"

extern void ScriptCmd_CreateObjectAtOrigin_020a0660(void);
extern void ScriptCmd_CreateObjectWithAngle_020a05ac(void);
extern void ScriptCmd_CreateShapedObjectClass_020a0520(void);
extern void ScriptCmd_SpawnObjectIntoSlot_020a0634(void);

void (*data_ov010_020a1d80[8])(void) = {
    ScriptCmd_CreateShapedObjectClass_020a0520,
    NULL,
    ScriptCmd_CreateObjectWithAngle_020a05ac,
    NULL,
    ScriptCmd_SpawnObjectIntoSlot_020a0634,
    NULL,
    ScriptCmd_CreateObjectAtOrigin_020a0660,
    NULL,
};
