#include "nitro/types.h"

extern u8 *g_panelState_0206c460;

void *func_ov002_02061948(void) {
    void *slot = NULL;
    if (g_panelState_0206c460 != NULL) {
        slot = g_panelState_0206c460 + 0x30;
    }
    return slot;
}
