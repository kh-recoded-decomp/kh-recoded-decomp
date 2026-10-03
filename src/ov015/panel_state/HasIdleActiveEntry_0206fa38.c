#include "nitro/types.h"

typedef struct PanelEntry {
    u8 pad_00[0x94];
    u32 visible : 1;
    u32 active : 1;
} PanelEntry;

typedef struct PanelContext {
    u8 pad_0000[0x6ac0];
    u8 entryManager[1];
} PanelContext;

extern PanelContext *data_ov015_0207e960;
extern PanelEntry *func_ov027_020b90a4(void *manager, int id);
extern int func_ov027_020b9100(PanelEntry *entry);

BOOL HasIdleActiveEntry_0206fa38(void)
{
    PanelEntry *entry;
    int i;

    for (i = 0; i < 3; i++) {
        entry = func_ov027_020b90a4(data_ov015_0207e960->entryManager, i + 1);
        if (entry != NULL && entry->active && func_ov027_020b9100(entry) == 0) {
            return TRUE;
        }
    }
    return FALSE;
}
