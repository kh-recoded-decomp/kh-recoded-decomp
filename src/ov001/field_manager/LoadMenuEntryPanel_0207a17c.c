#include "nitro/types.h"

typedef struct MenuEntry {
    u32 vramSlot;
    u32 unk_04;
} MenuEntry;

typedef struct MenuData {
    u8 pad_00[0xd0];
    MenuEntry *entries;
} MenuData;

typedef struct MenuLoader {
    u8 pad_00[8];
    int state;
} MenuLoader;

extern MenuData *data_ov001_020a04c4;
extern u32 MakePrimaryVramKey_02071248(u32 slot);
extern void *QueueFileLoadRequest_020ba114(char *path, int loadMode, void (*callback)(void), void *userData);
extern void func_ov001_02078d24(void);

void LoadMenuEntryPanel_0207a17c(MenuLoader *loader, int index)
{
    u32 slot = data_ov001_020a04c4->entries[index].vramSlot;

    loader->state = 2;
    QueueFileLoadRequest_020ba114((char *)MakePrimaryVramKey_02071248(slot), 1, func_ov001_02078d24, NULL);
}
