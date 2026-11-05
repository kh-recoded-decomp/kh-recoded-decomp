#include "src/overlays/ov027/FileLoadQueue.h"

/* Legacy name: retrieves current task work. */
extern void *NNSi_FndGetCurrentRootHeap(void);
extern void MI_CpuFill8(void *dest, int value, u32 size);
extern void NNS_FndInitList(void *list, u16 linkOffset);

FileLoadQueueStep InitFileLoadQueueTask(void *userData)
{
    FileLoadQueueWork *work;

    (void)userData; /* Obj_Construct passes it; this initializer does not use it. */
    work = NNSi_FndGetCurrentRootHeap();
    gFileLoadQueueStateWords[0] = (u32)work;
    MI_CpuFill8(work, 0, sizeof(FileLoadQueueWork));
    NNS_FndInitList(&work->pending, 0x18);
    NNS_FndInitList(&work->completed, 0x18);
    return UpdateFileLoadQueueTask;
}
