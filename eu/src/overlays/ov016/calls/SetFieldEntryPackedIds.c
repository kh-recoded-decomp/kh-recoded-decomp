#include "nitro/types.h"

typedef struct PackedIds {
    u32 kind : 6;
    u32 first : 10;
    u32 second : 10;
} PackedIds;

typedef union StoredIds {
    u32 value;
    struct {
        u32 first : 10;
        u32 second : 10;
        u32 reserved : 12;
    } fields;
} StoredIds;

typedef struct FieldEntry {
    u8 pad_000[0xb8];
    StoredIds *idsByKind;
} FieldEntry;

void SetFieldEntryPackedIds(FieldEntry *entry, const PackedIds *ids)
{
    StoredIds *stored = &entry->idsByKind[ids->kind];

    stored->fields.first = ids->first;
    stored->fields.second = ids->second;
}
