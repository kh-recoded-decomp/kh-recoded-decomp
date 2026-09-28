#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct G3dGlobalFlags {
    u8 pad_00[0xd4];
    u32 flags;
} G3dGlobalFlags;

extern G3dGlobalFlags g_g3dGlobal_0205a924;
extern MtxFx44 g_projectionMtx_0205a92c;
extern MtxFx43 g_cameraMtx_0205a970;
extern VecFx32 g_cameraPosition_0205ab3c;
extern VecFx32 g_cameraUp_0205ab48;
extern VecFx32 g_cameraTarget_0205ab54;

extern void camera_commit_explicit_projection_0202a8c4(void *camera, int top, int bottom, int left, int right);
extern void Scene_DrawNode_01ffb12c(void *node);
extern void func_01ff9b70(const VecFx32 *camPos, const VecFx32 *camUp, const VecFx32 *target, MtxFx43 *mtx);
extern void MIi_CpuCopyFast_01ff878c(const void *src, void *dst, u32 size);

void DrawNodeWithExplicitProjection_0202f1b0(void *node, void *camera, int top, int bottom, int left, int right)
{
    VecFx32 savedPosition = g_cameraPosition_0205ab3c;
    VecFx32 savedUp = g_cameraUp_0205ab48;
    VecFx32 savedTarget = g_cameraTarget_0205ab54;
    MtxFx44 savedProjection = g_projectionMtx_0205a92c;

    camera_commit_explicit_projection_0202a8c4(camera, top, bottom, left, right);
    Scene_DrawNode_01ffb12c(node);
    g_cameraPosition_0205ab3c = savedPosition;
    g_cameraUp_0205ab48 = savedUp;
    g_cameraTarget_0205ab54 = savedTarget;
    func_01ff9b70(&savedPosition, &savedUp, &savedTarget, &g_cameraMtx_0205a970);
    g_g3dGlobal_0205a924.flags &= ~0xe8;
    MIi_CpuCopyFast_01ff878c(&savedProjection, &g_projectionMtx_0205a92c, sizeof(MtxFx44));
    g_g3dGlobal_0205a924.flags &= ~0x50;
}
