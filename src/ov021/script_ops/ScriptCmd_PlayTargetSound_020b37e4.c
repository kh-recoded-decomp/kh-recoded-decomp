#include "nitro/types.h"

typedef struct {
    s16 tag;
    s16 pad_02;
    s32 value;
} TaggedValue;

typedef struct {
    void *actor;
    u32 pad_04;
    void *target;
} StageGlobals;

extern StageGlobals data_ov021_020b56a4;
extern TaggedValue *ResolveTaggedValueRef_020b0374(void *context, TaggedValue *value);
extern int TaggedValueToInt_020b0398(TaggedValue *tagged);
extern BOOL Session_Exists_02063a24(void);
extern int func_ov001_02063a38(void);
extern void PlayActorSound_02091b24(void *actor, u16 bank, u16 soundId, u32 flags, u16 volume);

int ScriptCmd_PlayTargetSound_020b37e4(void *context, TaggedValue *operands)
{
    TaggedValue *bank;
    TaggedValue *sound;
    TaggedValue *loop;
    TaggedValue *sessionOnly;
    void *target;
    int sessionFlag;
    u32 flags;
    int mode;

    bank = ResolveTaggedValueRef_020b0374(context, operands);
    sound = ResolveTaggedValueRef_020b0374(context, operands + 1);
    loop = ResolveTaggedValueRef_020b0374(context, operands + 2);
    sessionOnly = ResolveTaggedValueRef_020b0374(context, operands + 3);
    target = data_ov021_020b56a4.target;
    sessionFlag = 0;
    flags = 0;
    if (target == NULL) {
        return 0;
    }
    if (Session_Exists_02063a24()) {
        mode = func_ov001_02063a38();
    } else {
        mode = 0;
    }
    if (mode == 7) {
        sessionFlag = TaggedValueToInt_020b0398(sessionOnly);
    }
    if (TaggedValueToInt_020b0398(loop) != 0) {
        flags |= 1;
    }
    if (sessionFlag != 0) {
        flags |= 4;
    }
    PlayActorSound_02091b24(target, TaggedValueToInt_020b0398(bank), TaggedValueToInt_020b0398(sound), flags, 0);
    return 0;
}
