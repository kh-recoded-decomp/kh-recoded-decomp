#include "nitro/types.h"

typedef struct {
    s16 tag;
    s16 pad_02;
    s32 value;
} TaggedValue;

typedef struct ScriptContext ScriptContext;

typedef struct {
    u8 pad_000[8];
    u16 flags;
    u8 pad_00a[0x2a6];
    s32 fixedParam;
} PlayerActor;

typedef struct {
    u32 unk_00;
    u32 unk_04;
    PlayerActor *player;
} ScriptGlobals;

extern ScriptGlobals data_ov021_020b56a4;
extern TaggedValue *ResolveTaggedValueRef_020b0374(ScriptContext *context, TaggedValue *value);
extern s32 TaggedValueToFixed_020b03b0(TaggedValue *value);

int ScriptCmd_SetPlayerFixedParam_020b30d4(ScriptContext *context, TaggedValue *args)
{
    PlayerActor *player;
    s32 value;

    ResolveTaggedValueRef_020b0374(context, args);
    args = ResolveTaggedValueRef_020b0374(context, args + 1);
    player = data_ov021_020b56a4.player;
    value = TaggedValueToFixed_020b03b0(args);
    player->fixedParam = value;
    if (value != 0) {
        player->flags |= 0x10;
    } else {
        player->flags &= ~0x10;
    }
    return 0;
}
