#include "src/overlays/ov093/EntryGridTiles.h"

typedef struct EntryGridCharacterData {
    u8 reserved00[0x14];
    u8 *characters;
} EntryGridCharacterData;
typedef struct EntryGridScene {
    u8 reserved00[0x1c8];
    EntryGridCharacterData *background;
    u8 reserved1cc[0xd1bc - 0x1cc];
    s32 loadingTiles;
    s32 tileLoadStep;
} EntryGridScene;
extern EntryGridScene *data_ov093_020c5100;
extern BOOL IsEntryFlagSet_020c22c4(s32 type, s32 entry);
extern void GX_LoadBG0Char(const void *source, u32 destination, u32 size);

/* Upload unlocked entries in five-entry batches, six tile rows per entry. */
void LoadEntryGridTilesIncrementally(void)
{
    EntryGridScene *work = data_ov093_020c5100;
    s32 first, limit, entry;
    s32 step;
    if (work->loadingTiles == 0) {
        return;
    }
    {
        EntryGridBatchBoundaries boundaries = gEntryGridBatchBoundaries;
        limit = boundaries.entries[work->tileLoadStep + 1];
        first = boundaries.entries[work->tileLoadStep];
        for (entry = first; entry < limit; entry++) {
            if (IsEntryFlagSet_020c22c4(0, entry) || IsEntryFlagSet_020c22c4(1, entry)) {
                s32 width = 5;
                s32 column = entry % 5;
                EntryGridColumnStarts columns = gEntryGridColumnStarts;
                s32 tile;
                s32 row;
                if (column % 2 == 1) {
                    width = 6;
                }
                tile = (entry / 5) * 162 + columns.entries[column];
                for (row = 0; row < 6; row++) {
                    GX_LoadBG0Char(work->background->characters + tile * 64, tile * 64, width * 64);
                    tile += 27;
                }
            }
        }
    }
    step = ++work->tileLoadStep;
    if (step >= 6) {
        work->loadingTiles = 0;
    }
}
