#include "nitro/types.h"

extern u8 *g_stageManager_020a0508;
extern void func_ov001_0206dc98(void);

void RefreshStageEntriesIfLoaded_020992cc(void)
{
    if (g_stageManager_020a0508 == 0) {
        return;
    }
    func_ov001_0206dc98();
}
