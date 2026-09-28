#include "nitro/types.h"

typedef struct ActorTableManager {
    u8 pad_000[0x4c];
    void **actors;
} ActorTableManager;

typedef struct ScriptContext {
    u8 pad_000[0x1c8];
    ActorTableManager *actorTableManager;
} ScriptContext;

extern u32 func_02036588(u16 actorId);
extern void func_02025964(ScriptContext *scriptContext, u32 actorId);
extern void func_ov001_02089db0(void *actor, u32 param2, u32 param3, u32 actorId);

void ScriptActor_DispatchAndMarkFlag_0208c2c4(ScriptContext *scriptContext, u32 param2, u32 param3, u32 actorId)
{
    void *actor;

    if ((scriptContext->actorTableManager->actors != 0) &&
        ((func_02036588((u16)actorId) & 0x20) == 0)) {
        func_02025964(scriptContext, actorId);
        func_ov001_02089db0(scriptContext->actorTableManager->actors[actorId], param2, param3, actorId);
        actor = scriptContext->actorTableManager->actors[actorId];
        *(u16 *)((u8 *)actor + 0xd2c) = *(u16 *)((u8 *)actor + 0xd2c) | 0x200;
    }
}
