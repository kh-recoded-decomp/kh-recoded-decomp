#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s16 tag;
    s16 pad_02;
    s32 value;
} TaggedValue;

typedef struct {
    u8 pad_00[0x34];
    VecFx32 position;
} ScriptContext;

typedef struct {
    void *actor;
    u32 pad_04;
    void *target;
} StageGlobals;

extern StageGlobals data_ov021_020b56a4;
extern VecFx32 data_02053438;
extern TaggedValue *ResolveTaggedValueRef_020b0374(ScriptContext *context, TaggedValue *value);
extern fx32 TaggedValueToFixed_020b03b0(TaggedValue *tagged);
extern void ResolveVectorOperand_020b03c8(ScriptContext *context, TaggedValue *operand, VecFx32 *out);
extern s32 func_ov021_020b4aa4(ScriptContext *context, s32 offset);
extern u16 FindActorResourceIndexByName_02091248(void *actor, s32 name);
extern void GetNodePosition_02091600(void *owner, u32 nodeId, VecFx32 *out);
extern int func_02023dbc(int range, int value);
extern void func_ov021_020b0450(fx32 angle, fx32 length, VecFx32 *out);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);

u16 ResolveOffsetPosition_020b0508(ScriptContext *context, int flags, TaggedValue *operands, VecFx32 *out, s32 *outName) {
    VecFx32 offset;
    if (flags & 1) {
        *out = context->position;
    } else if (flags & 2) {
        ResolveVectorOperand_020b03c8(context, operands, out);
    } else {
        void *target = data_ov021_020b56a4.target;
        if (target != NULL) {
            s32 name = func_ov021_020b4aa4(context, operands->value);
            GetNodePosition_02091600(target, FindActorResourceIndexByName_02091248(target, name), out);
            *outName = name;
        }
    }
    offset = data_02053438;
    if (flags & 0x20) {
        ResolveVectorOperand_020b03c8(context, operands + 3, &offset);
    } else if (flags & 0x40) {
        TaggedValue *length = ResolveTaggedValueRef_020b0374(context, operands + 3);
        TaggedValue *angle = ResolveTaggedValueRef_020b0374(context, operands + 4);
        TaggedValue *scale = ResolveTaggedValueRef_020b0374(context, operands + 5);
        int turn = func_02023dbc(0xffff, angle->value);
        func_ov021_020b0450(turn * scale->value, TaggedValueToFixed_020b03b0(length), &offset);
    }
    VEC_Add_01ff9e0c(out, &offset, out);
    return flags;
}
