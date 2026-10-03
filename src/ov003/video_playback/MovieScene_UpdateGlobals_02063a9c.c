#include "nitro/types.h"

typedef struct MovieScene {
    u8 pad_000[0x8b9];
    u8 queuePending;
} MovieScene;

extern MovieScene *data_ov003_020658c0;
extern void func_02014008(void);
extern void MovieScene_UpdateFade_02063a20(MovieScene *scene);
extern void SoundMgr_Update_0204d150(void);

void MovieScene_UpdateGlobals_02063a9c(void)
{
    MovieScene *scene = data_ov003_020658c0;

    if (scene == NULL) {
        return;
    }
    if (scene->queuePending) {
        func_02014008();
        data_ov003_020658c0->queuePending = 0;
    }
    MovieScene_UpdateFade_02063a20(scene);
    SoundMgr_Update_0204d150();
}
