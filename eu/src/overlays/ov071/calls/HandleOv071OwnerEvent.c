#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    void *owner;
} Ov071SceneTask;

extern void DeactivateOv071TaskEntriesAndManager(Ov071SceneTask *task, void *owner);

void HandleOv071OwnerEvent(Ov071SceneTask *task, void *owner)
{
    if (task->owner == owner) {
        DeactivateOv071TaskEntriesAndManager(task, owner);
    }
}
