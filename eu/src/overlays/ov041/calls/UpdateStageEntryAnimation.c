#include "src/overlays/ov041/StageEntryRender.h"

typedef struct ActorRegistry ActorRegistry;

extern u32 Flags16_ClearBit1(void *flags);
extern ActorRegistry *GetActorRegistry(void);
extern u32 Obj_UpdateQuadTreeLink(ActorRegistry *registry, void *entity, int frameStep);
extern int func_0202f4cc(void *node, int animation);

void UpdateStageEntryAnimation(StageEntrySlot *slot)
{
    StageWork *work = gMovieContextState->stageWork;
    int i;

    for (i = 0; i < work->entryCount; ++i) {
        StageEntry *entry = &work->entries[i];
        if (slot == &entry->slot) {
            int step = entry->frameStep;

            if (entry->delay > 0) {
                entry->delay -= step;
                if (entry->delay <= 0) {
                    int j;
                    entry->delay = 0;
                    Flags16_ClearBit1(&entry->slot.node.flags);
                    entry->flags &= 0xffff7fff;
                    if (entry->kind == 0xff) {
                        Flags16_ClearBit1(&work->primaryActor.node.flags);
                        Flags16_ClearBit1(&work->shadowActors[0]->node.flags);
                        work->shadowActors[0]->stateFlags &= 0xdf;
                    } else if (entry->kind == 0xfd) {
                        Flags16_ClearBit1(&work->shadowActors[1]->node.flags);
                        work->shadowActors[1]->stateFlags &= 0xdf;
                    } else if (entry->kind == 0x16) {
                        Flags16_ClearBit1(&entry->attachment->node.flags);
                    }
                    for (j = 0; j < 5; ++j) {
                        StageTrackedNode *node = entry->trackedNodes[j];
                        if (node != NULL) {
                            node->flags &= 0xdf;
                        }
                    }
                }
            }
            if (!(entry->flags & 0x8000)) {
                Obj_UpdateQuadTreeLink(GetActorRegistry(), (u8 *)slot + 0x10, step);
                entry->animationFrame += step;
                if (func_0202f4cc(&slot->node.flags, 0) <= entry->animationFrame + step) {
                    entry->flags &= ~2;
                }
            }
            return;
        }
    }
}
