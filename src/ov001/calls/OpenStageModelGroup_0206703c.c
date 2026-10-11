#include "nitro/types.h"

typedef struct NamedMeshValue {
    const char *name;
    u32 value;
} NamedMeshValue;

extern const NamedMeshValue gStageMeshValues_0209d9f0[10];

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

extern StageModelState *data_ov001_020a046c;
extern char sOv001_ColWall_0209ea64[];
extern void OpenActorModelGroupResource_020357b4(int group, u32 resource);
extern void SetWorldMeshEntryValueByName_02036368(const char *name, const u32 *value);
extern void SelectMode3StateHandler_0206700c(int mode, u32 *cleared, void *handler);
extern void ApplyToNamedCollisionFaces_020680fc(const char *name, int flags, int value);

void OpenStageModelGroup_0206703c(void)
{
    u32 i;
    StageModelState *state = data_ov001_020a046c;
    OpenActorModelGroupResource_020357b4(0,
        (state->resources->entries[state->mode]->id & 0x1ff)
        | (0x80000000 | (((state->group + 0x8000) & 0xfffffc) << 7)));
    i = 0;
    do {
        SetWorldMeshEntryValueByName_02036368(gStageMeshValues_0209d9f0[i].name,
                                   &gStageMeshValues_0209d9f0[i].value);
        i++;
    } while (i < 10);
    SelectMode3StateHandler_0206700c(state->mode, &state->modeCleared, &state->modeHandler);
    ApplyToNamedCollisionFaces_020680fc(sOv001_ColWall_0209ea64, 8, 0);
}
