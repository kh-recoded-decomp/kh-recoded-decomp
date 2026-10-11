#ifndef KH_RECODED_LIST_HORIZONTAL_NEIGHBOR_H
#define KH_RECODED_LIST_HORIZONTAL_NEIGHBOR_H

/* SPDX-License-Identifier: MIT */
/* List layouts follow the shared US implementations; see eu/THIRD_PARTY_NOTICES.md. */
#include "nitro/types.h"
#pragma opt_propagation off
#pragma opt_common_subs off
#pragma opt_loop_invariants off

#define ABS_VALUE(value) ((value) < 0 ? -(value) : (value))

typedef struct ListEntry {
    u16 parameters00;
    u16 column;
    u16 row;
    u16 parameters06;
} ListEntry;

typedef struct ListTable {
    u8 reserved00[6];
    u16 count;
    ListEntry entries[1];
} ListTable;

typedef struct ListData {
    u8 reserved00[4];
    ListTable *table;
} ListData;

typedef struct ListView {
    u8 reserved00[4];
    ListData *data;
    u8 reserved08[0xa0];
    int selectedIndex;
} ListView;

#endif
