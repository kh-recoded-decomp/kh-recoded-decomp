#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct AttachedMatrix {
    fx32 rotation[9];
    VecFx32 translation;
    u16 nodeId;
} AttachedMatrix;

typedef struct ModelOwner {
    u8 pad_000[0x2c0];
    VecFx32 position;
} ModelOwner;

extern const VecFx32 data_02053438;

extern AttachedMatrix *GetAttachedObject_0208f724(ModelOwner *owner);
extern AttachedMatrix *GetObjectAttachment_0208f744(AttachedMatrix *object);

void GetNodePosition_02091600(ModelOwner *owner, u32 nodeId, VecFx32 *out)
{
    AttachedMatrix *attached;

    *out = data_02053438;
    if (nodeId == 0xFFFF) {
        *out = owner->position;
        return;
    }
    for (attached = GetAttachedObject_0208f724(owner); attached != NULL; attached = GetObjectAttachment_0208f744(attached)) {
        if (attached->nodeId == nodeId) {
            *out = attached->translation;
            return;
        }
    }
}
