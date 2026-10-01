#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Matrix43 {
    fx32 m[12];
} Matrix43;

typedef struct AttachedMatrix {
    Matrix43 mtx;
    u16 nodeId;
} AttachedMatrix;

typedef struct ModelPart {
    u8 pad_00[4];
    u8 node[0x80];
    Matrix43 rootMtx;
} ModelPart;

typedef struct ModelOwner {
    u8 pad_00[0x10];
    ModelPart part;
} ModelOwner;

extern AttachedMatrix *GetAttachedObject_0208f724(ModelOwner *owner);
extern AttachedMatrix *GetObjectAttachment_0208f744(AttachedMatrix *object);
extern BOOL RestoreNodeMatrixWithRotationCorrection_0208f2b4(u8 *node, Matrix43 *posMtx, u32 nodeId, BOOL applyCorrection);

void GetNodeMatrix_020915ac(ModelOwner *owner, u32 nodeId, Matrix43 *out)
{
    ModelPart *part = &owner->part;
    AttachedMatrix *attached;

    if (nodeId == 0xFFFF) {
        *out = part->rootMtx;
        return;
    }
    for (attached = GetAttachedObject_0208f724(owner); attached != NULL; attached = GetObjectAttachment_0208f744(attached)) {
        if (attached->nodeId == nodeId) {
            *out = attached->mtx;
            return;
        }
    }
    RestoreNodeMatrixWithRotationCorrection_0208f2b4(part->node, out, nodeId, TRUE);
}
