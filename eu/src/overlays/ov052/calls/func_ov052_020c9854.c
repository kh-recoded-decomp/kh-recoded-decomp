#include "nitro/types.h"

typedef struct CommandState {
    u16 unk_00;
    u16 pendingCount;
} CommandState;

typedef struct Entity {
    u8 pad_000[0x1D4];
    CommandState *command;
    u8 pad_1D8[0x7D4];
    u64 stateFlags;
} Entity;

extern void ApplyLinkedObjectMotion(Entity *entity);
extern int func_ov052_020c9968(Entity *entity);

void func_ov052_020c9854(Entity *entity)
{
    if ((entity->stateFlags & 0x20800) == 0 && entity->command->pendingCount != 0) {
        ApplyLinkedObjectMotion(entity);
        func_ov052_020c9968(entity);
    }
}
