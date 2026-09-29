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
    u8 pad_08[0x828 - 0x8];
    u8 dataPool[0x100];
    u32 dataPoolUsed;
} CollisionWorld;

extern MeshNamedEntry *FindMeshNamedEntry_020338c0(MeshData *mesh, const char *name);
extern void MI_CpuCopy8_01ff89a8(const void *src, void *dst, u32 size);
extern CollisionWorld *g_collisionWorld_0206083c;

void SetWorldMeshEntryDataByName_020363a4(const char *name, const void *src, u32 size)
{
    CollisionWorld *world = g_collisionWorld_0206083c;
    int meshIndex;

    for (meshIndex = 0; meshIndex < world->meshCount; meshIndex++) {
        MeshData *mesh = world->meshes[meshIndex];
        if (mesh != NULL) {
            MeshNamedEntry *entry = FindMeshNamedEntry_020338c0(mesh, name);
            if (entry != NULL) {
                u8 *dest = &g_collisionWorld_0206083c->dataPool[g_collisionWorld_0206083c->dataPoolUsed];
                g_collisionWorld_0206083c->dataPoolUsed += size;
                MI_CpuCopy8_01ff89a8(src, dest, size);
                entry->data = dest;
                return;
            }
        }
    }
}
