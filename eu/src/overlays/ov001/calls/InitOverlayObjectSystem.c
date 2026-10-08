#include "nitro/types.h"

typedef struct ActorManager {
    u8 pad_000[0x140];
    u8 pad_140[0x3DA4];
    void *heapHandle;
    void *rootObject;
} ActorManager;

extern ActorManager *data_ov001_020a0500;
extern u32 data_ov001_0209f324;
extern u32 gActorScriptCommandHandlers;
extern void MI_CpuFill8(void *dst, int val, u32 size);
extern void StoreGlobalArrayEntry(int index, void *value);
extern void func_020257d8(void *dst, u32 size, int channel);
extern void *func_0202a45c(void *arg0, int arg1);
extern void *func_0202a768(void);
extern void *NNSi_FndGetCurrentRootHeap(void);

u32 InitOverlayObjectSystem(void)
{
    ActorManager *manager;

    manager = (ActorManager *)NNSi_FndGetCurrentRootHeap();
    data_ov001_020a0500 = manager;
    MI_CpuFill8(manager, 0, 0x3f20);
    StoreGlobalArrayEntry(1, &gActorScriptCommandHandlers);
    manager->heapHandle = func_0202a768();
    manager->rootObject = func_0202a45c(&data_ov001_0209f324, 0);
    func_020257d8((u8 *)manager + 0x140, 0x8000, 0xd);
    return 0x20882d5;
}
