#include "nitro/types.h"

typedef struct {
    u32 flags;
    void *resource;
    void *block;
} Entity;

extern u32 func_0203a994(void);
extern void *func_0202a268(u32 kind);
extern void NNS_FndFreeToAllocator_0201372c(void *allocator, void *block);
extern void func_0202c8a8(void *resource);

void Obj_ReleaseIfSet_0203a970(Entity *entity)
{
    if (func_0203a994() != 0) {
        NNS_FndFreeToAllocator_0201372c(func_0202a268(0), entity->block);
        func_0202c8a8(entity->resource);
    }
    entity->flags = 0;
}
