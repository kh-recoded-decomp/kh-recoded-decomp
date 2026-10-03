#include "nitro/types.h"

typedef struct MovieScene {
    u8 pad_000[0x78];
    void *model;
    u8 pad_07c[0x8a];
    s16 modelIndex;
} MovieScene;

extern MovieScene *data_ov035_020bc4e4;
extern s8 data_ov035_020bc3ec[];
extern void Model_SetAllMaterialAlpha_0201a900(void *model, int alpha);

void SetMovieModelAlpha_020bb758(int level)
{
    if (data_ov035_020bc4e4->modelIndex >= 0) {
        if (level == 0xff) {
            level = 0;
        }
        Model_SetAllMaterialAlpha_0201a900(data_ov035_020bc4e4->model, data_ov035_020bc3ec[level]);
    }
}