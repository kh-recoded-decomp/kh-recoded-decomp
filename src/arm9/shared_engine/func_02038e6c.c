#include "nitro/types.h"

typedef struct {
    u32 flags;
    u8 pad_04[0x108];
    u32 node;
} Entity;

extern BOOL func_02038b50(Entity **handle, void *out, u32 arg);
extern void func_0203569c(Entity *entity, void *in);
extern u32 func_02036230(void);
extern void func_02033f10(u32 tree, u32 *node);

void func_02038e6c(Entity **handle, u32 arg)
{
    u8 buf[12];
    Entity *entity;
    u32 world;

    if (func_02038b50(handle, buf, arg) != 0) {
        func_0203569c(*handle, buf);
        entity = *handle;
        if (entity->node != 0) {
            world = func_02036230();
            func_02033f10(**(u32 **)(world + 4), &entity->node);
        }
    }
}
