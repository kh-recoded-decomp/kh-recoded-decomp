#include "nitro/types.h"

typedef struct ActorManager {
    u8 pad_000[0x140];
    u8 pad_140[0x3DA4];
    void *heapHandle;
    void *rootObject;
} ActorManager;

extern ActorManager *g_actorManager_020a04e0;
extern u32 data_ov001_0209f304;
extern u32 data_ov001_0209f324;
extern void func_01ff8830(void *dst, int val, u32 size);
extern void StoreGlobalArrayEntry_02025668(int index, void *value);
extern void func_020257c4(void *dst, u32 size, int channel);
extern void *InstantiateClass_0202a448(void *arg0, int arg1);
extern void *func_0202a754(void);
extern void *NNSi_FndGetCurrentRootHeap_0202a764(void);

u32 InitOverlayObjectSystem_02088250(void)
{
    ActorManager *manager;

    manager = (ActorManager *)NNSi_FndGetCurrentRootHeap_0202a764();
    g_actorManager_020a04e0 = manager;
    func_01ff8830(manager, 0, 0x3f20);
    StoreGlobalArrayEntry_02025668(1, &data_ov001_0209f324);
    manager->heapHandle = func_0202a754();
    manager->rootObject = InstantiateClass_0202a448(&data_ov001_0209f304, 0);
    func_020257c4((u8 *)manager + 0x140, 0x8000, 0xd);
    return 0x20882ad;
}
