#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct MoveOperands {
    u8 x[8];
    u8 y[8];
    u8 z[8];
    u8 pad18[4];
    int frames;
} MoveOperands;

typedef struct PlayerObject {
    u8 pad0[0x2f0];
    VecFx32 position;
} PlayerObject;

typedef struct ActiveContext {
    void *stage;
    void *source;
    PlayerObject *object;
} ActiveContext;

extern ActiveContext data_ov021_020b56a4;
extern void *ResolveTaggedValueRef_020b0374(void *context, void *value);
extern s32 TaggedValueToFixed_020b03b0(void *tagged);
extern void StartWalkerMove_0209113c(PlayerObject *walker, VecFx32 *target, fx32 duration);

int ScriptOp_MovePlayerTo_020b3918(void *context, MoveOperands *operands)
{
    VecFx32 target;
    void *tagX = ResolveTaggedValueRef_020b0374(context, operands->x);
    void *tagY = ResolveTaggedValueRef_020b0374(context, operands->y);
    void *tagZ = ResolveTaggedValueRef_020b0374(context, operands->z);
    PlayerObject *player = data_ov021_020b56a4.object;

    target.x = TaggedValueToFixed_020b03b0(tagX);
    target.y = TaggedValueToFixed_020b03b0(tagY);
    target.z = TaggedValueToFixed_020b03b0(tagZ);
    if (operands->frames == 0) {
        player->position = target;
    } else {
        StartWalkerMove_0209113c(player, &target, operands->frames << 12);
    }
    return 0;
}
