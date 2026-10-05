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
extern char data_ov041_020cf928[];
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void func_01ff8740(u32 value, void *dst, u32 size);
extern int OS_SPrintf_02002428(char *dst, const char *fmt, ...);
extern void *Msg_OpenContainerAndReadHeader_0202cc6c(const char *path, int kind, int flags);

MessageContainer *GetOrOpenMessageContainer_020bd62c(int index)
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
    container = scene->containers[index] = NNSi_FndAllocFromDefaultHeap_0202a178(sizeof(MessageContainer));
    func_01ff8740(0, container, sizeof(MessageContainer));
    OS_SPrintf_02002428(path, data_ov041_020cf928, index);
    container->header = Msg_OpenContainerAndReadHeader_0202cc6c(path, 0x12, 0);
    return container;
}
