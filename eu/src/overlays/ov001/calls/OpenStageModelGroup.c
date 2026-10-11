#include "src/overlays/ov001/StageMeshValues.h"
#pragma opt_propagation off

typedef struct StageModelResource {
    u32 parameter00;
    u16 id;
} StageModelResource;

typedef struct StageModelState {
    struct StageModelResourceTable *resources;
    u32 parameter04;
    u32 group;
    u8 parameter0c;
    s8 mode;
    u8 reserved00e[0x10cc - 0xe];
    u32 modeCleared;
    void *modeHandler;
} StageModelState;

typedef struct StageModelResourceTable {
    u32 reserved[2];
    StageModelResource *entries[1];
} StageModelResourceTable;

extern StageModelState *data_ov001_020a048c;
extern char sOv001_ColWall_0209ea84[];
extern void OpenActorModelGroupResource(int group, u32 resource);
extern void SetWorldMeshEntryValueByName(const char *name, const u32 *value);
extern void SelectMode3StateHandler(int mode, u32 *cleared, void *handler);
extern void ApplyToNamedCollisionFaces(const char *name, int flags, int value);

void OpenStageModelGroup(void)
{
    u32 i;
    StageModelState *state = data_ov001_020a048c;
    OpenActorModelGroupResource(0,
        (state->resources->entries[state->mode]->id & 0x1ff)
        | (0x80000000 | (((state->group + 0x8000) & 0xfffffc) << 7)));
    i = 0;
    do {
        SetWorldMeshEntryValueByName(gStageMeshValues[i].name,
                                   &gStageMeshValues[i].value);
        i++;
    } while (i < 10);
    SelectMode3StateHandler(state->mode, &state->modeCleared, &state->modeHandler);
    ApplyToNamedCollisionFaces(sOv001_ColWall_0209ea84, 8, 0);
}
