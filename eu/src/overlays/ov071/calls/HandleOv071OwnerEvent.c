#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    void *owner;
} Ov071SceneTask;

extern void func_ov071_020d8290(Ov071SceneTask *task, void *owner);

void HandleOv071OwnerEvent(Ov071SceneTask *task, void *owner)
{
    if (task->owner == owner) {
        func_ov071_020d8290(task, owner);
    }
}
