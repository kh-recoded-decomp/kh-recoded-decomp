#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct ScriptContext ScriptContext;

typedef struct PartyEntry {
    u8 pad_000[0x9ac];
    u64 stateFlags;
} PartyEntry;

extern int ScriptVm_ReadOperandInt_02025de4(ScriptContext *context, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32_02025df8(ScriptContext *context, ScriptOperand *operand);
extern PartyEntry *GetBoundedEntryField_0206db5c(int index);
extern void func_ov052_020ceb60(PartyEntry *entry, VecFx32 *position);

BOOL ScriptCmd_PlacePartyMember_02065bb0(ScriptContext *context, ScriptOperand *operands)
{
    int index;
    VecFx32 position;
    PartyEntry *entry;

    index = ScriptVm_ReadOperandInt_02025de4(context, &operands[0]);
    position.x = ScriptVm_ReadOperandFx32_02025df8(context, &operands[1]);
    position.y = ScriptVm_ReadOperandFx32_02025df8(context, &operands[2]);
    position.z = ScriptVm_ReadOperandFx32_02025df8(context, &operands[3]);
    entry = GetBoundedEntryField_0206db5c(index);
    func_ov052_020ceb60(entry, &position);
    entry->stateFlags |= 0x8000000;
    return TRUE;
}
