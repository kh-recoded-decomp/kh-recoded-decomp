#include "nitro/types.h"

typedef struct StageManager {
    u8 pad_00000[0x18df6];
    u16 spawnCounter;
    u8 pad_18df8[0xc4];
    void *pendingHandlerB;
    void *pendingHandlerA;
} StageManager;

typedef struct StageActor {
    u8 pad_000[0x320];
    u8 drawPriority;
} StageActor;

typedef struct SpawnRequest {
    int state;
    int kind;
    u16 active : 1;
    u16 flagBits : 15;
    u16 pad_0a;
    u16 busy;
    u16 spawnIndex;
    u8 pad_10[4];
    void *handlerA;
    void *handlerB;
} SpawnRequest;

extern u8 data_ov001_020a030c[];
extern StageManager *func_ov001_0209c3c0(void);
extern void func_01ff8830(void *dst, int value, u32 size);
extern int GetSmallRecordIndex_0209c248(SpawnRequest *request);
extern int func_ov001_02091834(void *table, int index, int arg, u16 type, int arg4, int arg5);
extern StageActor *GetStageActor_0209c040(s16 groupId);

int InitStageSpawnRequest_020982ac(SpawnRequest *request, int type, int arg)
{
    StageManager *manager;
    int actorId;
    StageActor *actor;

    manager = func_ov001_0209c3c0();
    func_01ff8830(request, 0, sizeof(SpawnRequest));
    if (request->busy != 0) {
        return 0;
    }
    actorId = func_ov001_02091834(data_ov001_020a030c, GetSmallRecordIndex_0209c248(request), arg, type, 0, 0);
    actor = GetStageActor_0209c040(actorId);
    if (actor != NULL) {
        manager->spawnCounter = (manager->spawnCounter + 1) % 20;
        request->spawnIndex = manager->spawnCounter;
        actor->drawPriority = 0x1f;
    }
    request->state = 0;
    request->kind = 2;
    if (manager->pendingHandlerB != NULL) {
        request->handlerB = manager->pendingHandlerB;
    }
    if (manager->pendingHandlerA != NULL) {
        request->handlerA = manager->pendingHandlerA;
    }
    manager->pendingHandlerB = NULL;
    manager->pendingHandlerA = NULL;
    request->active = 1;
    return actorId;
}
