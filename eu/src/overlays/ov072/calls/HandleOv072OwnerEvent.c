#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    void *owner;
} Ov072SceneTask;

extern void StopLoopingSounds(Ov072SceneTask *task, void *owner);

void HandleOv072OwnerEvent(Ov072SceneTask *task, void *owner)
{
    if (task->owner == owner) {
        StopLoopingSounds(task, owner);
    }
}
