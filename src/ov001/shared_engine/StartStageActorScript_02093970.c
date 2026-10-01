#include "nitro/types.h"

typedef struct ScriptRunner {
    u16 targetKind;
    u16 targetId;
} ScriptRunner;

typedef struct StageActor {
    u8 pad_000[0x1d0];
    ScriptRunner runner;
    u8 pad_1d4[0xa8];
    u16 scriptId;
    u8 pad_27e[0xa];
    u16 motionFlags;
    u8 pad_28a[0xa];
    s32 speed;
    s32 velocityX;
    s32 velocityZ;
    u32 unk_2a0;
    s32 accel;
    u32 unk_2a8;
    s32 turnRate;
} StageActor;

typedef struct StageTask {
    u8 pad_00[4];
    u16 unk_04_0 : 3;
    u16 keepMotion : 1;
    u16 unk_04_4 : 12;
    u8 pad_06[0xa];
    s16 actorId;
    u16 objectId;
} StageTask;

extern StageActor *GetStageActor_0209c040(int id);
extern void *GetStageObjectHandle_0209c0c4(u16 index);
extern u32 func_ov001_0209c584(u32 mask);
extern int func_ov021_020b4bdc(ScriptRunner *runner, int slot);
extern void func_ov001_02093e54(StageTask *task);

BOOL StartStageActorScript_02093970(StageTask *task)
{
    StageActor *actor = GetStageActor_0209c040(task->actorId);
    BOOL runScript;

    GetStageObjectHandle_0209c0c4(task->objectId);
    runScript = TRUE;
    if (!task->keepMotion) {
        actor->velocityX = 0;
        actor->speed = 0;
        actor->velocityZ = 0;
        actor->turnRate = 0;
        actor->accel = 0;
        actor->motionFlags |= 0x1000;
    }
    if (func_ov001_0209c584(2) && !task->keepMotion && (actor->scriptId == 0 || actor->scriptId == 0xffff)) {
        runScript = FALSE;
    }
    if (runScript && func_ov021_020b4bdc(&actor->runner, 7) != 4) {
        return FALSE;
    }
    func_ov001_02093e54(task);
    return TRUE;
}
