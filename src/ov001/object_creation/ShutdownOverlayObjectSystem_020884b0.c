#include "nitro/types.h"

typedef struct ActorManager {
    u8 pad_000[0x140];
    u8 pad_140[0x3DA4];
    void *heapHandle;
    void *rootObject;
} ActorManager;

extern ActorManager *g_actorManager_020a04e0;
extern void func_020257e4(void *dst);
extern void StoreGlobalArrayEntry_02025668(int index, void *value);
extern void func_0202a638(void *arg0);

void ShutdownOverlayObjectSystem_020884b0(void)
{
    ActorManager *manager;

    manager = g_actorManager_020a04e0;
    func_020257e4((u8 *)g_actorManager_020a04e0 + 0x140);
    StoreGlobalArrayEntry_02025668(1, 0);
    func_0202a638(manager->rootObject);
    g_actorManager_020a04e0 = 0;
}
