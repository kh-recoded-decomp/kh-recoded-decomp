#ifndef KH_RECODED_GROUP_ENTRY_TABLE_H
#define KH_RECODED_GROUP_ENTRY_TABLE_H

#include "nitro/types.h"

#define GROUP_ENTRY_COUNT 0x103
#define GROUP_ENTRY_SEPARATOR (-1)

/* Separator records also carry group metadata in bytes 2 and 3. */
typedef struct GroupEntry {
    s16 id;
    u8 parameter02;
    u8 parameter03;
    u32 value04;
    s8 state;
    u8 parameter09;
    u16 parameter0a;
} GroupEntry;

typedef char GroupEntrySizeCheck[(sizeof(GroupEntry) == 12) ? 1 : -1];

extern GroupEntry gGroupEntries[GROUP_ENTRY_COUNT];

#endif
