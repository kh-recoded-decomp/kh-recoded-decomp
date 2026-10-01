#include "nitro/types.h"

typedef void *(*SubModeUpdateFunc)(void);

typedef struct SubModeState {
    s32 mode;
    void *block;
    SubModeUpdateFunc update;
    void *heap;
} SubModeState;

extern SubModeState *data_ov021_020b56a0;

BOOL RunSubModeUpdate_020af364(void)
{
    SubModeUpdateFunc next = (SubModeUpdateFunc)data_ov021_020b56a0->update();
    if (next != NULL) {
        data_ov021_020b56a0->update = next;
    }
    return FALSE;
}
