#include "nitro/types.h"

typedef struct ActorModel {
    u8 pad_00[0x78];
    void *modelResource;
    u8 pad_7c[0x44];
    struct ActorModel *child;
    struct ActorModel *next;
} ActorModel;

typedef struct Actor {
    u32 unk_00;
    ActorModel model;
} Actor;

typedef struct PartyEntry {
    u8 pad_000[0x204];
    void (*setAlpha)(struct PartyEntry *entry, u8 alpha);
} PartyEntry;

extern u32 func_02036240(u32 actorId);
extern PartyEntry *GetBoundedEntryField_0206db5c(int index);
extern void SetModelCullMode_0208e2f8(ActorModel *actor, BOOL cullBack, BOOL cullNone);
extern void Model_SetAllMaterialAlpha_0201a900(void *model, int alpha);

void SetActorModelAlpha_0208e320(int actorId, int alpha, BOOL cullBack)
{
    Actor *actor = (Actor *)func_02036240((u16)actorId);
    ActorModel *root;
    ActorModel *part;

    if (actorId < 3) {
        PartyEntry *entry = GetBoundedEntryField_0206db5c(actorId);
        SetModelCullMode_0208e2f8(&actor->model, cullBack, TRUE);
        if (entry->setAlpha != NULL) {
            entry->setAlpha(entry, (u8)alpha);
        }
        return;
    }
    root = &actor->model;
    SetModelCullMode_0208e2f8(root, cullBack, FALSE);
    Model_SetAllMaterialAlpha_0201a900(root->modelResource, alpha);
    part = root->child;
    if (part != NULL) {
        Model_SetAllMaterialAlpha_0201a900(part->modelResource, alpha);
        SetModelCullMode_0208e2f8(part, cullBack, FALSE);
        for (part = part->next; part != NULL; part = part->next) {
            Model_SetAllMaterialAlpha_0201a900(part->modelResource, alpha);
            SetModelCullMode_0208e2f8(part, cullBack, FALSE);
        }
    }
}
