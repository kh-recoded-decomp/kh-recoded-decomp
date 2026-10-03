#include "nitro/types.h"

extern int func_ov009_020a0634(void *vm, int mode);

int ScriptCmd_SpawnModeTwo_020a0950(void *vm)
{
    func_ov009_020a0634(vm, 2);
    return 0;
}
