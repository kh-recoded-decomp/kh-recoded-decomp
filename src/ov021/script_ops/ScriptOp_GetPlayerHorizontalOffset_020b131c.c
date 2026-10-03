#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x2c];
    u16 resultType;
    u8 pad_2e[2];
    fx32 result;
} ScriptContext;

typedef struct PlayerActor PlayerActor;

typedef struct {
    u32 unk_00;
    u32 unk_04;
    PlayerActor *player;
} ScriptGlobals;

extern ScriptGlobals data_ov021_020b56a4;
extern void func_ov001_02091c34(PlayerActor *player, VecFx32 *out);
extern VecFx32 *func_ov001_02090f04(PlayerActor *player);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern fx32 VEC_Mag_01ff9f28(const VecFx32 *v);

int ScriptOp_GetPlayerHorizontalOffset_020b131c(ScriptContext *context)
{
    PlayerActor *player = data_ov021_020b56a4.player;
    VecFx32 current;
    VecFx32 reference;
    VecFx32 delta;

    if (player == NULL) {
        return 0;
    }
    func_ov001_02091c34(player, &current);
    reference = *func_ov001_02090f04(player);
    VEC_Subtract_01ff9e3c(&current, &reference, &delta);
    delta.y = 0;
    context->resultType = 0x10;
    context->result = VEC_Mag_01ff9f28(&delta);
    return 0;
}
