#include "nitro/types.h"

typedef struct ScriptObj {
    u8 pad_00[0x1cc];
    s32 armed;
    s32 valueA;
    s32 valueB;
} ScriptObj;

extern int ScriptVm_ReadOperandInt_02025de4(void *vm, void *cmd);

int ScriptCmd_ArmPair_02026554(ScriptObj *obj, void *cmd)
{
    obj->armed = 1;
    obj->valueA = ScriptVm_ReadOperandInt_02025de4(obj, cmd);
    obj->valueB = ScriptVm_ReadOperandInt_02025de4(obj, (u8 *)cmd + 8);
    return 3;
}
