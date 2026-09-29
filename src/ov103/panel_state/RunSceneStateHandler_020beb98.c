#include "nitro/types.h"

typedef struct MenuScene MenuScene;
typedef void (*SceneStateHandler)(MenuScene *scene);

extern int func_ov103_020c030c(MenuScene *scene);
extern SceneStateHandler data_ov103_020c047c[];

void RunSceneStateHandler_020beb98(MenuScene *scene)
{
    SceneStateHandler handler = data_ov103_020c047c[func_ov103_020c030c(scene)];

    if (handler != NULL) {
        handler(scene);
    }
}
