#include "nitro/types.h"

typedef struct ActorSlot {
    u8 pad_000[0x10];
    u8 entity[0x1b4];
    s16 frameStep;
    u8 pad_1c6[0x42];
    u8 stateFlags;
} ActorSlot;

typedef struct StageWork {
    u8 pad_000[0x34c];
    ActorSlot *trackedActors[2];
} StageWork;

typedef struct MovieContextState {
    u8 pad_000[0xb8];
    StageWork *stageWork;
} MovieContextState;

typedef struct ActorRegistry ActorRegistry;

extern MovieContextState *gMovieContextState;
extern ActorRegistry *GetActorRegistry(void);
extern u32 Obj_UpdateQuadTreeLink(ActorRegistry *registry, void *entity, int frameStep);

void UpdateStageShadowActor(ActorSlot *actor)
{
    int i;
    StageWork *work = gMovieContextState->stageWork;

    for (i = 0; i < 2; ++i) {
        ActorSlot *trackedActor = work->trackedActors[i];
        if (trackedActor == actor) {
            int frameStep = actor->frameStep;

            if ((trackedActor->stateFlags & 1) != 0 &&
                (trackedActor->stateFlags & 0x20) == 0 &&
                Obj_UpdateQuadTreeLink(GetActorRegistry(), actor->entity, frameStep) != 0) {
                trackedActor->stateFlags = trackedActor->stateFlags & 0xfe;
            }
            return;
        }
    }
}
