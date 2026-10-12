#include "src/overlays/ov001/StageActorTables.h"

#pragma explicit_zero_data on

extern void InitFieldPanelScene(void);
extern void func_ov001_0207ae58(void);

StageManagerTaskDescriptor gFieldHudCounterTaskDescriptor = {
    0x000e001a,
    (void *)InitFieldPanelScene,
    (void *)func_ov001_0207ae58,
    0x114,
    NULL,
};
