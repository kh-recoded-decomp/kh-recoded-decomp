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
extern char sOv041_RpgEfKageP2_020cfa54[];
extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern u32 Msg_OpenContainerAndReadHeader(const char *path, int kind, int flags);
extern void *SND_RegisterSeq(u32 key, int kind);
extern void *func_0202c4a0(u32 key, int mode);
extern void func_0202edb0(ModelInstance *model, void *record, void *block, int kind);
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);
extern void GetPositionAboveGround(VecFx32 *out, ModelActor *actor);
extern fx32 FX_Mul(fx32 a, fx32 b);

void LoadStageActorModel(ModelActor *actor) {
    StageWork *work = *(StageWork **)(data_ov035_020bc4e0 + 0xb8);
    void *record;
    void *block;
    fx32 scale;
    char path[16];
    VecFx32 pos;
    ModelInstance *model;

    if (work->archiveId == 0) {
        OS_SPrintf(path, sOv041_RpgEfKageP2_020cfa54);
        work->archiveId = Msg_OpenContainerAndReadHeader(path, 0x12, 0);
    }
    record = SND_RegisterSeq((((work->archiveId + 0x8000) & 0xfffffc) << 7) | 0x80000000, 0x12);
    block = func_0202c4a0((((work->archiveId + 0x8000) & 0xfffffc) << 7) | 0x80000001, 0xf);
    model = &actor->model;
    func_0202edb0(model, record, block, 0x12);
    NNSi_FndFreeFromDefaultHeap(block);
    GetPositionAboveGround(&pos, actor);
    model->position = pos;
    scale = FX_Mul(actor->baseScale, 0x2000);
    model->scale.x = scale;
    model->scale.y = scale;
    model->scale.z = scale;
}
