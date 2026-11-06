#include "nitro/types.h"

extern void BindPanelEntryScreen(void);
extern void QueryPanelEntry(void);

const u32 gRecordPanelMainObjConfig[6] = {
    0x00000000, 0x00000001, 0x00000000, 0x00000000,
    0x00000014, 0x00000000,
};

void *const gRecordPanelSubBgConfig[5] = {
    (void *)0x00000008,
    (void *)0x00000002,
    (void *)0x00000005,
    (void *)BindPanelEntryScreen,
    (void *)QueryPanelEntry,
};
