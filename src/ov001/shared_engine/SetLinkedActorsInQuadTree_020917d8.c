#include "nitro/types.h"

typedef struct CollisionWorld {
    u32 unk_00;
    void **quadTree;
} CollisionWorld;

extern void *GetFirstLinkedActor_0208f6e8(void *actor);
extern void *GetNextLinkedActor_0208f708(void *actor);
extern CollisionWorld *func_02036230(void);
extern void func_02033c3c(void *quadTree, void *object);
extern void QuadTree_RemoveObject_02033c60(void *quadTree, void *object);

void SetLinkedActorsInQuadTree_020917d8(void *actor, BOOL insert)
{
    void *link;
    CollisionWorld *world;

    link = GetFirstLinkedActor_0208f6e8(actor);
    world = func_02036230();
    if (world == NULL) {
        return;
    }
    for (link = GetNextLinkedActor_0208f708(link); link != NULL; link = GetNextLinkedActor_0208f708(link)) {
        if (insert) {
            func_02033c3c(*world->quadTree, link);
        } else {
            QuadTree_RemoveObject_02033c60(*world->quadTree, link);
        }
    }
}
