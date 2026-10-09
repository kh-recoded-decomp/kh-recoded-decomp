#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_000[0xa4];
    VecFx32 position;
    VecFx32 scale;
    u8 pad_0bc[0x48];
} ModelNode;

typedef struct {
    u32 id;
    ModelNode model;
} ListEntry;

typedef struct {
    int step;
    int cursor;
    int entryCount;
    fx32 scrollX;
    fx32 scrollSpeed;
    ModelNode rootModel;
    ListEntry entries[8];
    u8 camera[0x218];
} PanelScene;

extern const VecFx32 data_ov087_020c7c94;
extern void camera_commit_projection_0202a814(void *camera);
extern u16 AdvanceAnimationTracks_0202ef24(ModelNode *node, fx32 delta);
extern void SceneNode_Draw_01ffb12c(ModelNode *node);
extern int FX_Div_01ff9c84(int numer, int denom);

static inline fx32 MulRound(fx32 a, fx32 b)
{
    return (fx32)(((s64)a * b + 0x800) >> 12);
}

void DrawEntryCarousel_020c6c84(PanelScene *scene)
{
    VecFx32 position = data_ov087_020c7c94;
    int i;
    int count;
    int index;
    fx32 offset;
    fx32 scale;

    camera_commit_projection_0202a814(scene->camera);
    AdvanceAnimationTracks_0202ef24(&scene->rootModel, 0x1000);
    SceneNode_Draw_01ffb12c(&scene->rootModel);
    count = scene->entryCount;
    if (count <= 5) {
        count = 5;
    }
    for (i = 0; i < count; i++) {
        position.x = (i - 2) * (fx32)0xc800 + scene->scrollX;
        index = (scene->entryCount + (scene->cursor - 2 + i)) % scene->entryCount;
        index = (scene->entryCount + index) % scene->entryCount;
        offset = position.x;
        if (offset > -0xc800 && offset < 0xc800) {
            if (offset < 0) {
                offset = -offset;
            }
            scale = 0x400 - FX_Div_01ff9c84(MulRound(offset, 0x400), 0xc800);
            scale += 0x400;
        } else {
            scale = 0x400;
        }
        scene->entries[index].model.scale.z = scale;
        scene->entries[index].model.scale.y = scale;
        scene->entries[index].model.scale.x = scale;
        scene->entries[index].model.position = position;
        AdvanceAnimationTracks_0202ef24(&scene->entries[index].model, 0x1000);
        SceneNode_Draw_01ffb12c(&scene->entries[index].model);
    }
}




