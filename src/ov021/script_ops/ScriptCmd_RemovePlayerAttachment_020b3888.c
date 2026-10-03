#include "nitro/types.h"

typedef struct {
    s16 tag;
    s16 pad_02;
    s32 value;
} TaggedValue;

typedef struct ScriptContext ScriptContext;
typedef struct PlayerActor PlayerActor;

typedef struct {
    u32 unk_00;
    u32 unk_04;
    PlayerActor *player;
} ScriptGlobals;

extern ScriptGlobals data_ov021_020b56a4;
extern TaggedValue *ResolveTaggedValueRef_020b0374(ScriptContext *context, TaggedValue *value);
extern s32 TaggedValueToInt_020b0398(TaggedValue *value);
extern void func_ov001_02091ac0(PlayerActor *player, u16 firstId, u16 secondId, int arg3);

int ScriptCmd_RemovePlayerAttachment_020b3888(ScriptContext *context, TaggedValue *args)
{
    TaggedValue *first = ResolveTaggedValueRef_020b0374(context, args);
    TaggedValue *second = ResolveTaggedValueRef_020b0374(context, args + 1);
    PlayerActor *player = data_ov021_020b56a4.player;
    s32 firstId;

    if (player == NULL) {
        return 0;
    }
    firstId = TaggedValueToInt_020b0398(first);
    func_ov001_02091ac0(player, firstId, TaggedValueToInt_020b0398(second), 0);
    return 0;
}
