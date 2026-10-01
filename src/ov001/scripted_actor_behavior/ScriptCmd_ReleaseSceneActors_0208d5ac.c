#include "nitro/types.h"

typedef struct ScriptSceneData {
    u8 pad_00[0x4c];
    void **actorObjects;
} ScriptSceneData;

typedef struct ScriptContext {
    u8 pad_000[0x1c8];
    ScriptSceneData *scene;
} ScriptContext;

extern void PopVramState_020365f0(void);
extern void *func_02036810(u16 slotIndex);
extern u16 func_02036588(u16 slotIndex);
extern void func_ov001_02089f1c(void *actor);

int ScriptCmd_ReleaseSceneActors_0208d5ac(ScriptContext *context)
{
    int index;

    PopVramState_020365f0();
    if (context->scene->actorObjects != NULL) {
        for (index = 0; index < 0x200; index++) {
            if (func_02036810(index) == NULL || (func_02036588(index) & 4) == 0) {
                if (context->scene->actorObjects[index] != NULL) {
                    func_ov001_02089f1c(context->scene->actorObjects[index]);
                }
            }
        }
    }
    return 1;
}
