#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_000[0xa4];
    VecFx32 position;
    VecFx32 scale;
} ModelInstance;

typedef struct {
    u8 pad_000[0x128];
    fx32 baseScale;
    u8 pad_12c[0x27c];
    ModelInstance model;
} ModelActor;

typedef struct {
    u8 pad_000[0x538];
    u32 archiveId;
} StageWork;

extern u8 *data_ov035_020bc4e0;
extern char data_ov041_020cfa34[];
extern int OS_SPrintf_02002428(char *dst, const char *fmt, ...);
extern u32 Msg_OpenContainerAndReadHeader_0202cc6c(const char *path, int kind, int flags);
extern void *RetainOrInitializeSharedRecord_0202c80c(u32 key, int kind);
extern void *func_0202c48c(u32 key, int mode);
extern void func_0202ed9c(ModelInstance *model, void *record, void *block, int kind);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *ptr);
extern void GetPositionAboveGround_020c2ae0(VecFx32 *out, ModelActor *actor);
extern fx32 FixedPointMultiply12(fx32 a, fx32 b);

void LoadStageActorModel_020c26b8(ModelActor *actor) {
    StageWork *work = *(StageWork **)(data_ov035_020bc4e0 + 0xb8);
    void *record;
    void *block;
    fx32 scale;
    char path[16];
    VecFx32 pos;
    ModelInstance *model;

    if (work->archiveId == 0) {
        OS_SPrintf_02002428(path, data_ov041_020cfa34);
        work->archiveId = Msg_OpenContainerAndReadHeader_0202cc6c(path, 0x12, 0);
    }
    record = RetainOrInitializeSharedRecord_0202c80c((((work->archiveId + 0x8000) & 0xfffffc) << 7) | 0x80000000, 0x12);
    block = func_0202c48c((((work->archiveId + 0x8000) & 0xfffffc) << 7) | 0x80000001, 0xf);
    model = &actor->model;
    func_0202ed9c(model, record, block, 0x12);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(block);
    GetPositionAboveGround_020c2ae0(&pos, actor);
    model->position = pos;
    scale = FixedPointMultiply12(actor->baseScale, 0x2000);
    model->scale.x = scale;
    model->scale.y = scale;
    model->scale.z = scale;
}
