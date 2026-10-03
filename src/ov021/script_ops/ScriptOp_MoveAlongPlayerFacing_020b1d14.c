#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptContext {
    u8 pad0[0x34];
    VecFx32 position;
} ScriptContext;

typedef struct PlayerObject {
    u8 pad0[0x2e6];
    u16 facing;
} PlayerObject;

typedef struct ActiveContext {
    void *stage;
    void *source;
    PlayerObject *object;
} ActiveContext;

extern ActiveContext data_ov021_020b56a4;
extern const s16 data_0205356c[];
extern void *ResolveTaggedValueRef_020b0374(ScriptContext *context, void *value);
extern s32 TaggedValueToFixed_020b03b0(void *tagged);
extern void VEC_Normalize_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern void VEC_MultAdd_01ffa09c(int scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);

int ScriptOp_MoveAlongPlayerFacing_020b1d14(ScriptContext *context, u8 *operands)
{
    VecFx32 facing;
    VecFx32 direction;
    void *tagged = ResolveTaggedValueRef_020b0374(context, operands + 8);
    PlayerObject *player = data_ov021_020b56a4.object;

    facing.x = data_0205356c[player->facing >> 4];
    facing.y = 0;
    facing.z = data_0205356c[(0x400 - (player->facing >> 4)) & 0xfff];
    VEC_Normalize_01ff9f88(&facing, &direction);
    VEC_MultAdd_01ffa09c(TaggedValueToFixed_020b03b0(tagged), &direction, &context->position, &context->position);
    return 0;
}
