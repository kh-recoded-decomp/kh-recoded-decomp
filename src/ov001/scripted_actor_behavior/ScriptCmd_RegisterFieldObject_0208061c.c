#include "nitro/types.h"

typedef struct FieldObjectSpawn {
    u16 param;
    u8 variant;
} FieldObjectSpawn;

extern int ScriptVm_ReadOperandInt_02025de4(void *vm, void *operand);
extern void *func_ov001_0208614c(u16 classId, FieldObjectSpawn *spawn);
extern void func_ov001_0207ee04(int index, void *entry);

BOOL ScriptCmd_RegisterFieldObject_0208061c(void *vm, u8 *cmd)
{
    int index = ScriptVm_ReadOperandInt_02025de4(vm, cmd);
    int classId = ScriptVm_ReadOperandInt_02025de4(vm, cmd + 8);
    FieldObjectSpawn spawn;

    spawn.param = ScriptVm_ReadOperandInt_02025de4(vm, cmd + 0x10);
    spawn.variant = ScriptVm_ReadOperandInt_02025de4(vm, cmd + 0x18);
    func_ov001_0207ee04(index, func_ov001_0208614c(classId, &spawn));
    return TRUE;
}
