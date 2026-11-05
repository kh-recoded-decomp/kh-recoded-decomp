#include "nitro/types.h"

typedef struct ActorManager {
    u8 pad_000[0x140];
    u8 pad_140[0x3DA4];
    void *heapHandle;
    void *rootObject;
} ActorManager;

extern ActorManager *data_ov001_020a0500;
extern u32 gActorChannelClassDescriptor;
extern u32 gActorScriptCommandHandlers;
extern void MI_CpuFill8(void *dst, int val, u32 size);
extern void StoreGlobalArrayEntry(int index, void *value);
extern void AllocateScriptVmBuffer(void *dst, u32 size, int channel);
extern void *CreateTaskObject(void *arg0, int arg1);
extern void *GetCurrentTaskObject(void);
extern void *GetRunningTaskWork(void);

u32 InitOverlayObjectSystem(void)
{
    ActorManager *manager;

    manager = (ActorManager *)GetRunningTaskWork();
    data_ov001_020a0500 = manager;
    MI_CpuFill8(manager, 0, 0x3f20);
    StoreGlobalArrayEntry(1, &gActorScriptCommandHandlers);
    manager->heapHandle = GetCurrentTaskObject();
    manager->rootObject = CreateTaskObject(&gActorChannelClassDescriptor, 0);
    AllocateScriptVmBuffer((u8 *)manager + 0x140, 0x8000, 0xd);
    return 0x20882d5;
}
