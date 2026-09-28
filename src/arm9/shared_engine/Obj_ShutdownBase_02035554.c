#include "nitro/types.h"

typedef struct {
    u32 flags;
    u8 pad_04[0x12c];
    u32 sub130;
} Entity;

extern void func_020418dc(u32 *sub);
extern void func_020353a4(u32 *entity);
extern void Obj_RemoveFromQuadTree_020355f4(u32 *entity);

void Obj_ShutdownBase_02035554(Entity *entity)
{
    func_020418dc(&entity->sub130);
    func_020353a4(&entity->flags);
    Obj_RemoveFromQuadTree_020355f4(&entity->flags);
    entity->flags = 0;
}
