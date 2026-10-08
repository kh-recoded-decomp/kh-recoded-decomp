#include "nitro/types.h"

extern void CreateLayerTask(void); /* CreateLayerTask */
extern void CreateEffectTask(void); /* CreateEffectTask */
extern void CreateScriptedEffectTask(void);
extern void DispatchCommandHandler(void); /* DispatchCommandHandler */
extern void CreatePageEffectTask(void);

void (*gEffectCreationHandlers[7])(void) = {
    NULL,
    CreateLayerTask, /* CreateLayerTask */
    CreateEffectTask, /* CreateEffectTask */
    CreateScriptedEffectTask,
    DispatchCommandHandler, /* DispatchCommandHandler */
    CreatePageEffectTask,
    CreateScriptedEffectTask,
};
