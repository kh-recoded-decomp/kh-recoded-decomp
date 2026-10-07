#include "nitro/types.h"

extern void BindPanelEntryScreen(void);
extern void QueryPanelEntry(void);

const u32 data_ov014_0206f894[6] = {
    0x00000000, 0x00000001, 0x00000000, 0x00000000,
    0x00000014, 0x00000000,
};

void *const data_ov014_0206f880[5] = {
    (void *)0x00000008,
    (void *)0x00000002,
    (void *)0x00000005,
    (void *)BindPanelEntryScreen,
    (void *)QueryPanelEntry,
};
