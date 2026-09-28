#include "nitro/types.h"

extern int g_stageEventsState_0209f2c8;
extern BOOL CreateStageManagerTask_02099ad0(void *userData);

void StageEvents_StartIfIdle_0208765c(void *userData)
{
    if (g_stageEventsState_0209f2c8 == -1) {
        g_stageEventsState_0209f2c8 = 0;
        CreateStageManagerTask_02099ad0(userData);
    }
}
