#include "nitro/types.h"

typedef struct SceneRequest {
    char name[0x10];
    u32 param;
} SceneRequest;

typedef struct ActorManager {
    u8 pad_000[0x3ee4];
    void *rootObject;
    u8 pad_3ee8[4];
    char resourceName[0x14];
    s32 field_3f00;
    s32 field_3f04;
    s32 slots[5];
    u32 field_3f1c;
} ActorManager;

extern ActorManager *g_actorManager_020a04e0;
extern void *OS_SPrintf_02002428(char *dst, const char *fmt, ...);
extern void func_ov001_020883fc(void);
extern void func_ov001_02088384(void);
extern void *func_0202a5ac(void *object, void (*callback)(void));

void ActorManager_StartScene_02088974(SceneRequest *request)
{
    ActorManager *manager = g_actorManager_020a04e0;
    int slotIndex;

    manager->field_3f1c = request->param;
    OS_SPrintf_02002428(manager->resourceName, request->name);
    manager->field_3f00 = -1;
    manager->field_3f04 = 0x1f;
    for (slotIndex = 0; slotIndex < 5; slotIndex++) {
        manager->slots[slotIndex] = -1;
    }
    func_ov001_020883fc();
    func_0202a5ac(manager->rootObject, func_ov001_02088384);
}
