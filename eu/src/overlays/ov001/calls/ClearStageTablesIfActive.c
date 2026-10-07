#include "nitro/types.h"

extern s32 g_stageEventsState;
extern void ClearStageTables(void);

void ClearStageTablesIfActive(void)
{
    if (g_stageEventsState != -1) {
        ClearStageTables();
    }
}
