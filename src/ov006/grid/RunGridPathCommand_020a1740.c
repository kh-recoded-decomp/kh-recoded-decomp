#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    int from;
    int to;
} SegmentLink;

typedef struct {
    u8 pad_00[0x2c];
    SegmentLink *links;
} PathGrid;

typedef struct {
    u8 pad_000[0x124];
    u32 slotCount;
    u32 slotStride;
    u8 *slots;
} LinkData;

typedef struct {
    u8 pad_00[0x8];
    LinkData *data;
} LinkTarget;

typedef struct {
    u16 id;
    u8 pad_02[2];
    LinkTarget *target;
} StageLink;

typedef struct {
    u8 pad_000[0x270];
    u16 gridLevel;
} StageActorInfo;

typedef struct {
    u8 pad_000[0x2c0];
    VecFx32 position;
} StageActor;

typedef struct {
    u8 pad_00[0xe];
    u16 linkId;
    s16 actorId;
    u8 pad_12[4];
    u16 gridId;
} GridPathCommand;

extern StageActor *GetStageActor_0209c040(int id);
extern PathGrid *GetStageMotionRecord_0209c18c(u32 id);
extern StageLink *FindStageLink_02099584(u32 id);
extern void SyncStageEntryPosition_02098fbc(u32 id, VecFx32 *outPosition);
extern void LoadGridLevel_020a1194(PathGrid *grid, int level, u32 *data);
extern void ResolveSegmentNodes_020a121c(PathGrid *grid);
extern int GetGridCellIndex_020a12d4(PathGrid *grid, const VecFx32 *position);
extern int FindGridPath_020a124c(PathGrid *grid, int goalCell, int startCell);
extern int func_ov006_020a1318(PathGrid *grid, int from, int to);

static inline u32 GetLinkSlotCount(StageLink *link)
{
    if (link == NULL) {
        return 0;
    }
    if (link->target == NULL) {
        return 0;
    }
    return link->target->data->slotCount;
}

static inline u32 *GetLinkSlot(StageLink *link, u16 index)
{
    u32 count;
    LinkTarget *target;
    LinkData *data;
    u8 *slots;

    if (link == NULL) {
        return NULL;
    }
    target = link->target;
    if (target == NULL) {
        return NULL;
    }
    count = GetLinkSlotCount(link);
    data = target->data;
    slots = data->slots;
    if (count == 0) {
        return NULL;
    }
    if (index >= count) {
        return NULL;
    }
    return (u32 *)(slots + index * data->slotStride);
}

void RunGridPathCommand_020a1740(GridPathCommand *cmd, int command)
{
    StageActorInfo *info = (StageActorInfo *)GetStageActor_0209c040(cmd->actorId);
    PathGrid *grid = GetStageMotionRecord_0209c18c(cmd->gridId);
    u16 level = info->gridLevel;
    StageLink *link = FindStageLink_02099584(cmd->linkId);
    u32 *slotData;

    if (link == NULL) {
        return;
    }
    slotData = GetLinkSlot(link, 0);
    if (slotData == NULL) {
        return;
    }
    LoadGridLevel_020a1194(grid, level, slotData);
    switch (command) {
    case 0x61:
        ResolveSegmentNodes_020a121c(grid);
        break;
    case 0x62: {
        StageActor *actor = GetStageActor_0209c040(cmd->actorId);
        VecFx32 target;
        int goal;

        SyncStageEntryPosition_02098fbc(1, &target);
        goal = GetGridCellIndex_020a12d4(grid, &actor->position);
        FindGridPath_020a124c(grid, goal, GetGridCellIndex_020a12d4(grid, &target));
        break;
    }
    case 0x63: {
        StageActor *actor = GetStageActor_0209c040(cmd->actorId);
        VecFx32 target;
        int goal;

        SyncStageEntryPosition_02098fbc(1, &target);
        goal = GetGridCellIndex_020a12d4(grid, &actor->position);
        FindGridPath_020a124c(grid, goal, func_ov006_020a1318(grid, grid->links[0].from, grid->links[0].to));
        break;
    }
    }
}
