#include "nitro/types.h"

typedef struct TaskManager {
    u16 activeIds[8];
    u8 activeCount;
    u8 secondaryCount;
} TaskManager;

extern TaskManager *gFieldTaskManagerWork;

void ClearSecondaryTaskCount(void)
{
    gFieldTaskManagerWork->secondaryCount = 0;
}
