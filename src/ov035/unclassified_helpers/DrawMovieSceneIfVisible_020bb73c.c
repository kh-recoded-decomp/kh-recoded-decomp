#include "nitro/types.h"

typedef struct MovieScene {
    u8 pad_000[0x10b];
    u8 visible;
} MovieScene;

extern MovieScene *data_ov035_020bc4e4;
extern void SceneNode_Draw_01ffb12c(MovieScene *node);

void DrawMovieSceneIfVisible_020bb73c(void)
{
    if (data_ov035_020bc4e4->visible) {
        SceneNode_Draw_01ffb12c(data_ov035_020bc4e4);
    }
}