#include "nitro/types.h"

typedef struct MeshNamedEntry {
    char name[12];
    u32 value;
    void *data;
} MeshNamedEntry;

typedef struct MeshData {
    u8 reserved00[0x82];
    u16 namedEntryCount;
    u8 reserved84[0x28];
    MeshNamedEntry *namedEntries;
} MeshData;

extern int strncmp(const char *, const char *, u32);

MeshNamedEntry *FindMeshNamedEntry(MeshData *mesh, const char *name)
{
    int entryIndex;
    int entryCount;
    long entryOffset;
    int compareResult;
    MeshNamedEntry *entries;

    entryCount = mesh->namedEntryCount;
    entryIndex = 0;
    if (entryCount > 0) {
        entries = mesh->namedEntries;
        do {
            entryOffset = entryIndex * sizeof(MeshNamedEntry);
            compareResult = strncmp((const char *)entries + entryOffset, name, 12);
            if (compareResult == 0) {
                return (MeshNamedEntry *)((u8 *)entries + entryOffset);
            }
            entryIndex++;
        } while (entryIndex < entryCount);
    }
    return NULL;
}
