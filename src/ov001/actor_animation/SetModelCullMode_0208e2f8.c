#include "nitro/types.h"

typedef struct ActorModel {
    u8 pad_00[0x78];
    void *modelResource;
} ActorModel;

extern void Model_SetAllMaterialCullMode_0201a880(void *model, int cullMode);
extern void SetAllMaterialsPolyAttrMask_0201a3c4(void *model, BOOL enable, u32 mask);

void SetModelCullMode_0208e2f8(ActorModel *actor, BOOL cullBack, BOOL cullNone)
{
    if (cullBack) {
        Model_SetAllMaterialCullMode_0201a880(actor->modelResource, 2);
        return;
    }
    if (cullNone) {
        Model_SetAllMaterialCullMode_0201a880(actor->modelResource, 3);
        return;
    }
    SetAllMaterialsPolyAttrMask_0201a3c4(actor->modelResource, TRUE, 0xc0);
}
