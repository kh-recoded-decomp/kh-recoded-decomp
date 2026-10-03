#include "nitro/types.h"

extern void ScriptCmd_CreatePanelObject_020a1f00(void);
extern void ScriptCmd_CreateSlotObjectKind1_020a1ed0(void);
extern void ScriptCmd_CreateSlotObjectKind2_020a1de0(void);
extern void ScriptCmd_CreateSlotObjectKind3_020a1ffc(void);
extern void ScriptCmd_SpawnPanelCollider_020a202c(void);
extern void func_ov020_020a1e10(void);

void (*data_ov020_020a3a40[11])(void) = {
    ScriptCmd_CreateSlotObjectKind2_020a1de0,
    NULL,
    func_ov020_020a1e10,
    NULL,
    ScriptCmd_CreateSlotObjectKind1_020a1ed0,
    NULL,
    ScriptCmd_CreatePanelObject_020a1f00,
    NULL,
    ScriptCmd_CreateSlotObjectKind3_020a1ffc,
    NULL,
    ScriptCmd_SpawnPanelCollider_020a202c,
};
