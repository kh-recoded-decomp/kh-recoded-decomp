#include "nitro/types.h"

typedef struct {
    u8 data[0x108];
} EntryModel;

typedef struct {
    u8 pad_000[4];
    EntryModel models[7];
    u8 pad_73c[0x744 - 0x73c];
    s32 modelCount;
} EntryMenu;

extern void ReleaseResourceAndDetach(EntryModel *model);

void ReleaseEntryModels(EntryMenu *menu)
{
    int i;

    for (i = 0; i < menu->modelCount; i++) {
        ReleaseResourceAndDetach((EntryModel *)((u8 *)menu + i * sizeof(EntryModel) + 4));
    }
}
