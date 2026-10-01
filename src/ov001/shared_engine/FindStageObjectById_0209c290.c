#include "nitro/types.h"

typedef struct StageObject {
    u8 pad_000[0x280];
    u16 id;
} StageObject;

typedef struct StageData {
    u8 pad_00000[0x18d84];
    void *objectPool;
} StageData;

extern StageData *data_ov001_020a0508;
extern void *func_ov001_0208f27c(void *pool);
extern void *func_ov001_0208f28c(void *node);
extern StageObject *BindDescriptor0_0208f268(void *pool, void *node);

StageObject *FindStageObjectById_0209c290(u16 id)
{
    void *pool = data_ov001_020a0508->objectPool;
    void *node = func_ov001_0208f27c(pool);
    StageObject *object = BindDescriptor0_0208f268(pool, node);

    while (object != NULL) {
        if (object->id == id) {
            return object;
        }
        node = func_ov001_0208f28c(node);
        if (node == NULL) {
            break;
        }
        object = BindDescriptor0_0208f268(pool, node);
    }
    return NULL;
}
