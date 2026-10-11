#include "src/overlays/ov001/StageActorTables.h"

extern int func_ov001_02097d84(void *controller);
extern int ControllerStateActive(void *controller);
extern int ControllerRunnerDone(void *controller);
extern int func_ov001_02097d7c(void *controller);

ActorControllerStateHandler gActorControllerStateHandlers[5] = {
    NULL,
    func_ov001_02097d84,
    ControllerStateActive,
    ControllerRunnerDone,
    func_ov001_02097d7c
};
