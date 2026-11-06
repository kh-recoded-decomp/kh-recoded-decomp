#include "src/overlays/ov001/StageActorTables.h"

extern int ActorController_ReleasedActorKeepState(void *controller);
extern int ControllerStateActive(void *controller);
extern int ControllerRunnerDone(void *controller);
extern int ActorController_AwaitReleaseKeepState(void *controller);

ActorControllerStateHandler gActorControllerStateHandlers[5] = {
    NULL,
    ActorController_ReleasedActorKeepState,
    ControllerStateActive,
    ControllerRunnerDone,
    ActorController_AwaitReleaseKeepState
};
