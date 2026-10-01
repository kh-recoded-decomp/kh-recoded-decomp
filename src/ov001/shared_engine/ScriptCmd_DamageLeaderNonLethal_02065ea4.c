#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct ScriptContext ScriptContext;

typedef struct MemberStats {
    u16 unk_00;
    u16 hp;
} MemberStats;

typedef struct PartyMember {
    u8 pad_000[0x1d4];
    MemberStats *stats;
} PartyMember;

extern fx32 ScriptVm_ReadOperandFx32_02025df8(ScriptContext *context, ScriptOperand *operand);
extern PartyMember *GetBoundedEntryField_0206db5c(int index);
extern fx32 ScaleValueByPercentField_020a7650(PartyMember *member, s32 value);
extern void func_ov021_020a75ec(PartyMember *member, s16 amount);
extern void func_ov052_020ceb60(PartyMember *member, VecFx32 *position);

BOOL ScriptCmd_DamageLeaderNonLethal_02065ea4(ScriptContext *context, ScriptOperand *operands)
{
    VecFx32 position;
    PartyMember *leader;
    int damage;
    int hp;

    position.x = ScriptVm_ReadOperandFx32_02025df8(context, &operands[0]);
    position.y = ScriptVm_ReadOperandFx32_02025df8(context, &operands[1]);
    position.z = ScriptVm_ReadOperandFx32_02025df8(context, &operands[2]);
    leader = GetBoundedEntryField_0206db5c(0);
    damage = -(ScaleValueByPercentField_020a7650(leader, 0x14000) >> 12);
    hp = leader->stats->hp;
    if (hp <= damage) {
        damage = hp - 1;
    }
    func_ov021_020a75ec(leader, damage);
    func_ov052_020ceb60(leader, &position);
    return TRUE;
}
