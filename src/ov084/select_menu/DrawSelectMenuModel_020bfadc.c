#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraParams {
    fx32 fovySin;
    fx32 fovyCos;
    fx32 aspect;
    fx32 nearClip;
    fx32 farClip;
    VecFx32 position;
    VecFx32 target;
    VecFx32 up;
} CameraParams;

typedef struct CameraPreset {
    fx32 height;
    fx32 targetX;
    fx32 targetY;
    fx32 depth;
} CameraPreset;

typedef struct SelectMenu {
    u8 pad_00[0xd0];
    u8 model[1];
} SelectMenu;

extern CameraPreset data_ov084_020bfc50[2];

extern u32 func_ov039_020bc7f8(void);
extern void LoadDefaultProjectionValues_0202a7b4(CameraParams *params);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern void camera_commit_projection_0202a814(CameraParams *params);
extern void func_02006d3c(int value);
extern u16 AdvanceAnimationTracks_0202ef24(void *state, fx32 delta);
extern void SceneNode_Draw_01ffb12c(void *node);

void DrawSelectMenuModel_020bfadc(SelectMenu *menu)
{
    CameraParams camera;
    VecFx32 offset;
    CameraPreset *preset;
    int index;

    if (func_ov039_020bc7f8() & 0x8000) {
        index = 0;
    } else {
        index = 1;
    }
    preset = &data_ov084_020bfc50[index];
    LoadDefaultProjectionValues_0202a7b4(&camera);
    camera.position.y = preset->height;
    {
        VecFx32 depth;
        depth.x = 0;
        depth.y = 0;
        depth.z = preset->depth;
        offset = depth;
    }
    camera.position.x = 0;
    camera.position.z = 0;
    VEC_Add_01ff9e0c(&camera.position, &offset, &camera.target);
    camera.target.x += preset->targetX;
    camera.target.y += preset->targetY;
    camera_commit_projection_0202a814(&camera);
    func_02006d3c(-0x39);
    AdvanceAnimationTracks_0202ef24(menu->model, 0x1000);
    SceneNode_Draw_01ffb12c(menu->model);
}
