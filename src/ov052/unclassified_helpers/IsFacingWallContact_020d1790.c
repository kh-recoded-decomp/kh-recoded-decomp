#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x80];
    u8 meshIndices[4];
} ContactSurface;

typedef struct {
    ContactSurface *surface;
    int kind;
    int pad_08;
} ContactHit;

typedef struct {
    ContactHit hits[16];
    VecFx32 normals[16];
    u8 count;
} ContactList;

extern void *GetWorldMeshNamedEntry_0203625c(int index);
extern BOOL func_ov001_020681e8(void *entry, u32 kind);
extern u16 GetLinkedAngleOffset_020ceb7c(int entity);
extern int FixedPointAtan2_020062bc(int vertical, int horizontal);

BOOL IsFacingWallContact_020d1790(int entity)
{
    BOOL result = FALSE;
    ContactList *contacts;
    int i;
    int j;
    BOOL skip;
    int facing;
    int diff;
    void *mesh;

    if (*(u8 *)(entity + 0x9b4) != 0) {
        return result;
    }
    contacts = (ContactList *)(entity + 0x344);
    for (i = 0; i < contacts->count; i++) {
        ContactHit *hit = &contacts->hits[i];
        skip = FALSE;
        if (hit->kind != 2) {
            continue;
        }
        for (j = 0; j < 4; j++) {
            mesh = GetWorldMeshNamedEntry_0203625c(hit->surface->meshIndices[j]);
            if (mesh != NULL && func_ov001_020681e8(mesh, 2)) {
                skip = TRUE;
                break;
            }
        }
        if (skip) {
            continue;
        }
        facing = (u16)(GetLinkedAngleOffset_020ceb7c(entity) + 0x8000);
        diff = (u16)(facing - (u16)FixedPointAtan2_020062bc(-contacts->normals[i].x, -contacts->normals[i].z));
        if (diff <= 0x2100 || diff >= 0xdf00) {
            result = TRUE;
            break;
        }
    }
    return result;
}
