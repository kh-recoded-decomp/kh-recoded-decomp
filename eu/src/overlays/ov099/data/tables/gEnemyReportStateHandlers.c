#include "nitro/types.h"

extern void EnemyViewer_HandleState0Noop(void);
extern void RunViewerIntroMode(void);

void (*const gEnemyReportStateHandlers[2])(void) = {
    EnemyViewer_HandleState0Noop,
    RunViewerIntroMode,
};
