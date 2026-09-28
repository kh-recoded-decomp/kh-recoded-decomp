#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x74];
    u16 flags;
} CollisionMesh;

typedef struct {
    u16 unk_00;
    u16 meshCount;
    CollisionMesh **meshes;
} CollisionMeshList;

typedef struct {
    u8 data[0x114];
} CollisionQuery;

extern void func_020335d0(CollisionQuery *query, void *params);
extern void func_020337c4(CollisionQuery *query, CollisionMesh *mesh);

void TestQueryAgainstMeshList_02035270(CollisionMeshList *list, void *params)
{
    CollisionQuery query;
    int i;
    int count = list->meshCount;
    func_020335d0(&query, params);
    for (i = 0; i < count; i++) {
        CollisionMesh *mesh = list->meshes[i];
        if ((mesh->flags & 0x2000) == 0) {
            func_020337c4(&query, mesh);
        }
    }
}
