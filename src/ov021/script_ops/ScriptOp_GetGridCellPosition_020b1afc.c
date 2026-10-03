#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s16 tag;
    s16 pad_02;
    s32 value;
} TaggedValue;

typedef struct {
    u8 pad_00[0x34];
    VecFx32 vector;
} ScriptContext;

typedef struct {
    u8 pad_00[0x16];
    u16 motionId;
} ScriptOwner;

typedef struct {
    u8 pad_000[0x2c0];
    VecFx32 position;
} PlayerActor;

typedef struct {
    ScriptOwner *owner;
    u32 unk_04;
    PlayerActor *player;
} ScriptGlobals;

typedef struct {
    u8 pad_00[0x18];
    s32 cellCount;
    u8 pad_1c[4];
    s32 *cells;
} StageGrid;

extern ScriptGlobals data_ov021_020b56a4;
extern TaggedValue *ResolveTaggedValueRef_020b0374(ScriptContext *context, TaggedValue *value);
extern s32 TaggedValueToInt_020b0398(TaggedValue *value);
extern StageGrid *GetStageMotionRecord_0209c18c(u32 id);
extern void GetGridCellCenter_020a1370(StageGrid *grid, s32 cell, VecFx32 *out);

int ScriptOp_GetGridCellPosition_020b1afc(ScriptContext *context, TaggedValue *args)
{
    TaggedValue *index = ResolveTaggedValueRef_020b0374(context, args + 1);
    PlayerActor *player = data_ov021_020b56a4.player;
    StageGrid *grid = GetStageMotionRecord_0209c18c(data_ov021_020b56a4.owner->motionId);

    if (grid != NULL) {
        if (index->value < grid->cellCount) {
            GetGridCellCenter_020a1370(grid, grid->cells[TaggedValueToInt_020b0398(index)], &context->vector);
        } else {
            context->vector = player->position;
        }
    }
    return 0;
}
