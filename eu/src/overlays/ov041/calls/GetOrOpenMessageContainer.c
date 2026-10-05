#include "nitro/types.h"

typedef struct {
    void *header;
    u8 released;
    u8 pad_05[3];
} MessageContainer;

typedef struct {
    u8 pad_000[0x4bc];
    MessageContainer *containers[1];
} SceneWork;

extern u8 *data_ov035_020bc4e0;
extern char sOv041_RpgEnFormat02dP2_020cf948[];
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void MIi_CpuClearFast(u32 value, void *dst, u32 size);
extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern void *Msg_OpenContainerAndReadHeader(const char *path, int kind, int flags);

MessageContainer *GetOrOpenMessageContainer(int index)
{
    char path[16];
    MessageContainer *container;
    SceneWork *scene;

    scene = *(SceneWork **)(data_ov035_020bc4e0 + 0xb8);

    container = scene->containers[index];
    if (container != NULL) {
        container->released = 0;
        return container;
    }
    container = scene->containers[index] = NNSi_FndAllocFromDefaultHeap(sizeof(MessageContainer));
    MIi_CpuClearFast(0, container, sizeof(MessageContainer));
    OS_SPrintf(path, sOv041_RpgEnFormat02dP2_020cf948, index);
    container->header = Msg_OpenContainerAndReadHeader(path, 0x12, 0);
    return container;
}
