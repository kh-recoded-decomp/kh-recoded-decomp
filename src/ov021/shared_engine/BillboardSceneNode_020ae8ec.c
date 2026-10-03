#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ViewMatrix {
    fx32 m[4][3];
} ViewMatrix;

typedef struct RotationMatrix {
    fx32 m[3][3];
} RotationMatrix;

typedef struct SceneNode {
    u16 flags;
    u8 pad02[0x7e];
    RotationMatrix rotation;
} SceneNode;

extern ViewMatrix *GetCachedInverseViewMatrix_02019378(void);
extern void func_01ff87c4(const ViewMatrix *src, RotationMatrix *dst);
extern void func_ov021_020ae88c(SceneNode *node);

void BillboardSceneNode_020ae8ec(SceneNode *node)
{
    ViewMatrix view = *GetCachedInverseViewMatrix_02019378();
    func_01ff87c4(&view, &node->rotation);
    node->flags &= ~0x20;
    func_ov021_020ae88c(node);
}
