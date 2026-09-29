#include "nitro/types.h"

typedef struct MeshNamedEntry {
    char name[0xc];
    u32 value;
    void *data;
} MeshNamedEntry;

typedef struct MeshData MeshData;

typedef struct CollisionWorld {
    u16 unk_00;
    u16 meshCount;
    MeshData **meshes;
} CollisionWorld;

extern MeshNamedEntry *FindMeshNamedEntry_020338c0(MeshData *mesh, const char *name);
extern CollisionWorld *g_collisionWorld_0206083c;

void SetWorldMeshEntryValueByName_02036368(const char *name, const u32 *value)
{
    CollisionWorld *world = g_collisionWorld_0206083c;
    int meshIndex;

    for (meshIndex = 0; meshIndex < world->meshCount; meshIndex++) {
        MeshData *mesh = world->meshes[meshIndex];
        if (mesh != NULL) {
            MeshNamedEntry *entry = FindMeshNamedEntry_020338c0(mesh, name);
            if (entry != NULL) {
                entry->value = *value;
                return;
            }
        }
    }
}
