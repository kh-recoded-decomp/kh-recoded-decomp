#include "nitro/types.h"

extern void ScriptCmd_CreateChildSpawner_020a0668(void);
extern void ScriptCmd_CreateDelayedGimmick_020a054c(void);
extern void ScriptCmd_CreateObjectInSlot_020a0520(void);
extern void ScriptCmd_CreateObjectWithParamInSlot_020a0630(void);

void (*data_ov008_020a13c0[8])(void) = {
    ScriptCmd_CreateObjectInSlot_020a0520,
    NULL,
    ScriptCmd_CreateDelayedGimmick_020a054c,
    NULL,
    ScriptCmd_CreateObjectWithParamInSlot_020a0630,
    NULL,
    ScriptCmd_CreateChildSpawner_020a0668,
    NULL,
};
