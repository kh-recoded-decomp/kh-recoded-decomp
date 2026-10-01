#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct {
    u8 pad_00[0x18];
    s32 groupId;
    u8 pad_1c[0x28 - 0x1c];
} ModelPart;

typedef struct {
    u8 pad_00[0x2c];
    ModelPart *parts;
} ModelPartSet;

typedef struct {
    u32 unk_00;
    ModelPartSet *set;
    u32 flags;
    u8 pad_0c[0xae - 0x0c];
    u8 groupId;
} PartOwner;

extern void CaptureGeometryMatrices_02019d00(MtxFx43 *m, MtxFx33 *n);
extern void func_ov001_02089618(ModelPart *part, MtxFx33 *out);
extern void MTX_Concat43_01ff98c0(const MtxFx43 *a, const MtxFx43 *b, MtxFx43 *ab);
extern void QueueOrSendGeometryCommand_01ffa37c(u32 op, const void *args, u32 numWords);

static inline void SetGeMtxMode(u32 mode) {
    u32 arg = mode;
    QueueOrSendGeometryCommand_01ffa37c(0x10, &arg, 1);
}

static inline void LoadGeMtx43(const void *mtx) {
    QueueOrSendGeometryCommand_01ffa37c(0x17, mtx, 12);
}

void ApplyPartRotationToGeometry_02089724(PartOwner *owner) {
    MtxFx33 vecMtx;
    MtxFx43 posMtx;
    MtxFx33 partMtx;
    ModelPart *parts = owner->set->parts;
    int i;

    for (i = 0; i < 7; i++) {
        ModelPart *part = &parts[i];
        if (part != NULL) {
            s32 group;
            if (owner->flags & 0x10) {
                group = owner->groupId;
            } else {
                group = -1;
            }
            if (part->groupId == group) {
                fx32 x;
                fx32 y;
                fx32 z;
                CaptureGeometryMatrices_02019d00(&posMtx, &vecMtx);
                y = posMtx._31;
                x = posMtx._30;
                z = posMtx._32;
                func_ov001_02089618(part, &partMtx);
                MTX_Concat43_01ff98c0((MtxFx43 *)&partMtx, &posMtx, &posMtx);
                posMtx._30 = x;
                posMtx._31 = y;
                posMtx._32 = z;
                SetGeMtxMode(2);
                LoadGeMtx43(&vecMtx);
                SetGeMtxMode(1);
                LoadGeMtx43(&posMtx);
                SetGeMtxMode(2);
            }
        }
    }
}
