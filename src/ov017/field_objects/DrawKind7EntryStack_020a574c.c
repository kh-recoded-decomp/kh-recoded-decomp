#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ActorModel {
    u8 data[0x84];
} ActorModel;

typedef struct FieldActor {
    u8 pad_00[4];
    ActorModel model;
} FieldActor;

typedef struct Kind7Entry {
    u8 pad_00[4];
    void *owner;
    u8 pad_08[0x2a];
    u8 slot;
    u8 pad_33[0x15];
    void *effect;
    u8 pad_4C[4];
    s8 state;
    u8 pad_51[3];
    u16 flags;
    s16 belowIndex;
    s16 parentIndex;
} Kind7Entry;

extern void SceneNode_Draw_01ffb12c(void *node);
extern FieldActor *func_02036240(int slot);
extern Kind7Entry *func_ov001_0208635c(void *owner, int index);
extern int func_ov017_020a5248(Kind7Entry *entry);
extern s8 GetCtxModeByte_02068084(void);
extern void DrawTexturedGridQuads_020866ac(void *model, fx32 size, int rows, int cols, void *node, int alpha, BOOL lit);

static inline void DrawStackShadow(Kind7Entry *base, int count)
{
    FieldActor *actor = func_02036240(base->slot);

    DrawTexturedGridQuads_020866ac(&actor->model, 0x1800, 1, count, (u8 *)&actor->model + 0x80, 0x1f, GetCtxModeByte_02068084() != 6);
}

void DrawKind7EntryStack_020a574c(Kind7Entry *entry)
{
    Kind7Entry *current;
    Kind7Entry *parent;
    int group;
    int nextGroup;
    int count;
    BOOL active;

    if (entry->flags & 0x20) {
        SceneNode_Draw_01ffb12c(entry->effect);
    }
    if (!(entry->flags & 0x40)) {
        return;
    }
    if (entry->flags & 0x10) {
        SceneNode_Draw_01ffb12c(&func_02036240(entry->slot)->model);
        return;
    }
    if (entry->parentIndex != -1) {
        parent = func_ov001_0208635c(entry->owner, entry->parentIndex);
        active = TRUE;
        if (parent->state != 2 && parent->state != 1) {
            active = FALSE;
        }
        if (!active) {
            return;
        }
    }
    current = entry;
    group = func_ov017_020a5248(entry);
    count = 1;
    for (;;) {
        if (current->belowIndex < 0) {
            break;
        }
        current = func_ov001_0208635c(current->owner, current->belowIndex);
        active = TRUE;
        if (current->state != 2 && current->state != 1) {
            active = FALSE;
        }
        if (active) {
            break;
        }
        nextGroup = func_ov017_020a5248(current);
        if (nextGroup != group) {
            DrawStackShadow(entry, count);
            group = nextGroup;
            count = 0;
            entry = current;
        }
        count++;
    }
    DrawStackShadow(entry, count);
}
