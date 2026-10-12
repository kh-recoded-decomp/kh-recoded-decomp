#ifndef ENTRY_GRID_TILES_H
#define ENTRY_GRID_TILES_H

#include "nitro/types.h"

/* Six batches of five entries share a 27-tile-wide background. */
typedef struct EntryGridBatchBoundaries { s32 entries[7]; } EntryGridBatchBoundaries;
typedef struct EntryGridColumnStarts { s32 entries[5]; } EntryGridColumnStarts;

extern const EntryGridBatchBoundaries gEntryGridBatchBoundaries;
extern const EntryGridColumnStarts gEntryGridColumnStarts;

#endif
