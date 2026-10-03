#include "nitro/types.h"

extern u32 DispatchContextCommand_02066c78(u32 command, u32 value, u32 extra, void *buffer);

int GetPanelPageCount_020779dc(void)
{
    int count = DispatchContextCommand_02066c78(1, 0, 0, NULL);

    return count + (count + (count + 1) / 10 + 1) / 10;
}
