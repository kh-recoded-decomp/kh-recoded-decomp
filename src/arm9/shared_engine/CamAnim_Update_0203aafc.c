#include "nitro/types.h"

typedef struct RenderStateScratch {
    u8 bytes[0x188];
} RenderStateScratch;

typedef struct CameraAnim CameraAnim;

extern void CamAnim_ApplyPose_0203a9dc(CameraAnim *anim);
extern RenderStateScratch *data_0205ab60;

void CamAnim_Update_0203aafc(CameraAnim *anim)
{
    RenderStateScratch scratch;

    if (data_0205ab60 == NULL) {
        data_0205ab60 = &scratch;
        CamAnim_ApplyPose_0203a9dc(anim);
        data_0205ab60 = NULL;
    } else {
        CamAnim_ApplyPose_0203a9dc(anim);
    }
}
