#include "nitro/types.h"

extern u32 gFieldSessionWork;

void InvokeFieldSceneTransitionHook(void) {
    void (*callback)(void) = *(void (**)(void))(gFieldSessionWork + 0x2838);
    if (callback != NULL) {
        callback();
    }
}
