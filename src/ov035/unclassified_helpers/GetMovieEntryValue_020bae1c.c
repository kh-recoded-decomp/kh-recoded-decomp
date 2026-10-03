#include "nitro/types.h"

typedef struct MovieEntry {
    u8 unk_00;
    u8 kind : 7;
    u8 flag : 1;
    s16 value;
    u8 pad_04[0x18];
} MovieEntry;

typedef struct MovieContext {
    u8 pad_00[0x42];
    u8 entryCount;
    u8 pad_43[0xd];
    MovieEntry *entries;
} MovieContext;

extern MovieContext *g_movieContext_020bc4e0;

s16 GetMovieEntryValue_020bae1c(int index)
{
    MovieEntry *entry;

    if (index >= 0 && index < g_movieContext_020bc4e0->entryCount) {
        entry = &g_movieContext_020bc4e0->entries[index];
        if (entry != NULL) {
            return entry->value;
        }
    }
    return -1;
}