#include "nitro/types.h"

typedef struct {
    u16 refCount;
    u16 loadedCount;
} SharedRecord;

extern SharedRecord *RetainOrInitializeSharedRecord_0202c80c(u32 fileId, int kind);
extern void *func_0202c48c(u32 fileId, int kind);
extern void func_020358b0(u16 actorIndex, SharedRecord *record, void *data, int kind);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);

void SetActorResource_02026a00(int actorIndex, u32 resourceFileId, u32 dataFileId)
{
    void *data = NULL;
    SharedRecord *record = RetainOrInitializeSharedRecord_0202c80c(resourceFileId, 0xd);

    if (record->loadedCount == 0) {
        data = func_0202c48c(dataFileId, 0xd);
    }
    func_020358b0(actorIndex, record, data, 0xd);
    if (data != NULL) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4(data);
    }
}
