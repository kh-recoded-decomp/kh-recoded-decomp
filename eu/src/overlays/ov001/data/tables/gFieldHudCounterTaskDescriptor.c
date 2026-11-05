#include "src/overlays/ov001/StageActorTables.h"

#pragma explicit_zero_data on

extern void InitFieldPanelScene(void);
extern void ReleaseSubscenePanelWork(void);

StageManagerTaskDescriptor gFieldHudCounterTaskDescriptor = {
    0x000e001a,
    (void *)InitFieldPanelScene,
    (void *)ReleaseSubscenePanelWork,
    0x114,
    NULL,
};
