#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    u8 payload[6];
} ScriptOperand;

typedef struct ActorNode {
    u32 flags;
    u16 stateFlags;
    u8 unknown006[0x7a];
    u16 rotation;
    u8 unknown082[0x26];
    VecFx32 position;
} ActorNode;

typedef struct MtxFx43 {
    fx32 m[4][3];
} MtxFx43;

extern int ScriptVm_ReadOperandInt_02025de4(void *scriptContext, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32_02025df8(void *scriptContext, ScriptOperand *operand);
extern int ScriptCmd_ReturnValue_02025960(void *scriptContext, int actorId);
extern VecFx32 *GetSharedCommandDataOffset44_0208bcf8(void);
extern ActorNode *func_02036240(u16 actorId);
extern void func_01ff9480(MtxFx43 *matrix);
extern void func_01ff9530(MtxFx43 *matrix, fx32 sine, fx32 cosine);
extern void MTX_MultVec43_01ff9ad8(const VecFx32 *vector, const MtxFx43 *matrix, VecFx32 *result);
extern void VEC_Add_01ff9e0c(const VecFx32 *left, const VecFx32 *right, VecFx32 *result);
extern void func_020359f8(u16 actorId, int mode, VecFx32 *position);
extern void ActorSlot_SetFlag8ByIndex_02036120(u16 actorId, int flag);
extern void ScriptActor_DispatchAndMarkFlag_0208c2c4(void *scriptContext, int mode, VecFx32 *position, int actorId);
extern s16 data_0205356c[];

int PlaceActorRelativeToActor_0208df48(void *scriptContext, ScriptOperand *operands) {
    int actorId;
    int referenceId;
    fx32 height;
    VecFx32 orientation;
    VecFx32 position;
    MtxFx43 matrix;
    VecFx32 offset;
    ActorNode *node;
    u16 heading;
    int angle;
    fx32 depth;

    actorId = ScriptVm_ReadOperandInt_02025de4(scriptContext, operands);
    referenceId = ScriptVm_ReadOperandInt_02025de4(scriptContext, operands + 1);
    height = ScriptVm_ReadOperandFx32_02025df8(scriptContext, operands + 2);
    actorId = ScriptCmd_ReturnValue_02025960(scriptContext, actorId);
    orientation = *GetSharedCommandDataOffset44_0208bcf8();
    position = func_02036240(referenceId)->position;
    depth = operands[3].type == 0 ? height : ScriptVm_ReadOperandFx32_02025df8(scriptContext, operands + 3);
    offset.x = 0;
    offset.y = height;
    offset.z = depth;
    func_01ff9480(&matrix);
    heading = orientation.x;
    angle = heading >> 4;
    func_01ff9530(&matrix, data_0205356c[angle], data_0205356c[(0x400 - angle) & 0xfff]);
    MTX_MultVec43_01ff9ad8(&offset, &matrix, &offset);
    offset.x = -offset.x;
    VEC_Add_01ff9e0c(&position, &offset, &position);
    func_020359f8(actorId, 0, &position);
    node = func_02036240(actorId);
    if ((node->flags & 0x20) == 0) {
        node->rotation = heading;
        node->stateFlags |= 0x20;
    }
    ActorSlot_SetFlag8ByIndex_02036120(actorId, 1);
    ScriptActor_DispatchAndMarkFlag_0208c2c4(scriptContext, 0, &position, actorId);
    return 1;
}
