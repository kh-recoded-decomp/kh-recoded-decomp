#pragma thumb on

#include "nitro/types.h"

typedef struct {
    u16 flags;
    u16 count;
    void **models;
} ModelGroup;

extern int Obj_GetIndirectWord(void *pack, int kind);
extern void *Archive_GetMember(void *pack, int kind, int index);
extern void *NNSi_FndAllocFromDefaultExpHeap(unsigned int size);
extern void Coll_ResolveModelBlobPointers(void *model);

int ModelGroup_Open_0203510c(ModelGroup *g, void *res)
{
    int i;

    g->flags = 0;
    if (*(unsigned int *)res == 0x4850414b) {
        g->count = Obj_GetIndirectWord(res, 5);
        g->models = NNSi_FndAllocFromDefaultExpHeap(g->count << 2);
        for (i = 0; i < g->count; i++) {
            g->models[i] = Archive_GetMember(res, 5, i);
            Coll_ResolveModelBlobPointers(g->models[i]);
        }
    } else {
        g->count = 1;
        g->models = NNSi_FndAllocFromDefaultExpHeap(4);
        g->models[0] = res;
        Coll_ResolveModelBlobPointers(g->models[0]);
    }
    return 1;
}
