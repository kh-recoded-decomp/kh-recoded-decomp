#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x78];
    void *model;
    u8 pad_7c[0x28];
    VecFx32 position;
    fx32 scaleX;
    fx32 pad_b4;
    fx32 scaleZ;
} MarkerNode;

typedef struct {
    u8 pad_00[0xc];
    MarkerNode node;
} MarkerRecord;

typedef struct {
    u8 pad_000[8];
    u16 flags;
    u8 pad_00a[0x286];
    fx32 baseY;
    u8 pad_294[0x1c];
    fx32 size;
    u8 pad_2b4[0xc];
    VecFx32 position;
    u8 pad_2cc[0x50];
    fx32 scale;
    u8 pad_320[0x10];
    fx32 range;
} MarkerOwner;

extern void FindStageObjectByOwner_020995c4(int kind, int owner);
extern MarkerRecord *GetStageObjectRecord_0209c0a0(void);
extern fx32 FX_Div_01ff9c84(fx32 numer, fx32 denom);
extern fx32 FixedPointMultiply12_02006450(fx32 a, fx32 b);
extern BOOL Session_Exists_02063a24(void);
extern int func_ov001_02063a38(void);
extern void Model_SetAllMaterialAlpha_0201a900(void *model, int alpha);
extern void Model_SetAllPolygonIds_0201a8c0(void *model, int id);
extern void SceneNode_Draw_01ffb12c(MarkerNode *node);

void DrawProximityMarker_0208f760(MarkerOwner *owner)
{
    MarkerNode *node;
    fx32 distance;
    fx32 ratio;
    fx32 scale;
    int alpha;
    int mode;

    FindStageObjectByOwner_020995c4(0x1c, 1);
    node = &GetStageObjectRecord_0209c0a0()->node;
    if (!(owner->flags & 0x10)) {
        return;
    }
    distance = owner->position.y - owner->baseY;
    if (distance < 0) {
        distance = -distance;
    }
    if (distance < 0) {
        distance = -distance;
    }
    if (distance >= owner->range || owner->size <= 0) {
        return;
    }
    ratio = FX_Div_01ff9c84(distance, owner->range);
    if (ratio > 0x1000) {
        ratio = 0x1000;
    }
    scale = FixedPointMultiply12_02006450(FixedPointMultiply12_02006450(owner->size, owner->scale), 0x1000 - ratio);
    node->position = owner->position;
    node->position.y = owner->baseY + 0x29 + FixedPointMultiply12_02006450(owner->size, 0x7b);
    node->scaleX = scale;
    node->scaleZ = scale;
    alpha = 8 - ((ratio * 8) >> 12);
    if (Session_Exists_02063a24()) {
        mode = func_ov001_02063a38();
    } else {
        mode = 0;
    }
    if (mode == 7) {
        alpha = 0x1f;
    }
    Model_SetAllMaterialAlpha_0201a900(node->model, alpha);
    Model_SetAllPolygonIds_0201a8c0(node->model, 0x3f);
    SceneNode_Draw_01ffb12c(node);
}
