#include "nitro/types.h"

typedef struct Entity Entity;

struct Entity {
    u8 pad_000[0x9AC];
    u64 stateFlags;
    u8 pad_9B4[0x38];
    int unk_9EC;
    u8 pad_9F0[0x6FC];
    void (*changeState)(Entity *entity, int state);
    u8 pad_10F0[0x4];
    void (*postUpdate)(Entity *entity);
    u8 pad_10F8[0x10];
    u8 unk_1108[4];
};

extern void func_ov021_020ab854(void *target, int value);

void func_ov052_020c97a4(Entity *entity)
{
    if ((entity->stateFlags & 0x20820) == 0) {
        if ((entity->stateFlags & 0x10) != 0) {
            entity->changeState(entity, 10);
            entity->stateFlags &= ~(u64)0x10;
        }
        func_ov021_020ab854(entity->unk_1108, entity->unk_9EC);
    }
    if (entity->postUpdate != NULL) {
        entity->postUpdate(entity);
    }
}
