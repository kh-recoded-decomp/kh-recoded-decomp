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
    u32 unk_00;
    VecFx32 position;
} SlotEntry;

typedef struct SlotTable SlotTable;

extern ScriptGlobals data_ov021_020b56a4;
extern TaggedValue *ResolveTaggedValueRef_020b0374(ScriptContext *context, TaggedValue *value);
extern s32 TaggedValueToInt_020b0398(TaggedValue *value);
extern SlotTable *GetStageMotionRecord_0209c18c(u32 id);
extern SlotEntry *SlotTable_GetEntry_020a125c(SlotTable *table, int index);

int ScriptOp_GetSlotPosition_020b1a30(ScriptContext *context, TaggedValue *args)
{
    TaggedValue *index = ResolveTaggedValueRef_020b0374(context, args + 1);
    PlayerActor *player = data_ov021_020b56a4.player;
    SlotTable *table = GetStageMotionRecord_0209c18c(data_ov021_020b56a4.owner->motionId);
    SlotEntry *entry = SlotTable_GetEntry_020a125c(table, TaggedValueToInt_020b0398(index));

    if (entry != NULL) {
        context->vector = entry->position;
    } else if (player != NULL) {
        context->vector = player->position;
    }
    return 0;
}

