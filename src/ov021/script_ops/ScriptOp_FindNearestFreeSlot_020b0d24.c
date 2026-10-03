#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s16 tag;
    s16 pad_02;
    s32 value;
} TaggedValue;

typedef struct {
    u8 pad_00[0x2c];
    u16 resultType;
    u8 pad_2e[2];
    s32 result;
} ScriptContext;

typedef struct {
    u8 pad_00[0x16];
    u16 motionId;
} ScriptOwner;

typedef struct SlotTable SlotTable;

extern ScriptOwner *data_ov021_020b56a4;
extern TaggedValue *ResolveTaggedValueRef_020b0374(ScriptContext *context, TaggedValue *value);
extern fx32 TaggedValueToFixed_020b03b0(TaggedValue *value);
extern SlotTable *GetStageMotionRecord_0209c18c(u32 id);
extern int SlotTable_FindNearestFree_020a1280(SlotTable *table, fx32 height, int heightSign, int distanceSign);

int ScriptOp_FindNearestFreeSlot_020b0d24(ScriptContext *context, TaggedValue *args)
{
    TaggedValue *height = ResolveTaggedValueRef_020b0374(context, args + 1);
    SlotTable *table;

    if (data_ov021_020b56a4 == NULL) {
        return 0;
    }
    table = GetStageMotionRecord_0209c18c(data_ov021_020b56a4->motionId);
    if (table == NULL) {
        return 0;
    }
    context->resultType = 1;
    context->result = SlotTable_FindNearestFree_020a1280(table, TaggedValueToFixed_020b03b0(height), -1, 1);
    return 0;
}
