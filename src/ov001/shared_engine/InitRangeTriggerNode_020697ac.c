#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct RangeNode RangeNode;
typedef BOOL (*RangeTest)(RangeNode *node, const VecFx32 *point);

typedef struct RangeNodeParams {
    u32 id;
    VecFx32 place;
    s32 shape;
    u8 extent[0xC];
    s32 value;
} RangeNodeParams;

struct RangeNode {
    void *update;
    s32 state;
    void *release;
    s32 value;
    u8 pad_10[2];
    u8 id;
    u8 pad_13;
    RangeTest test;
    u8 extent[0xC];
    VecFx32 place;
};

extern void func_01ff8710(const void *src, void *dst, u32 size);
extern BOOL IsPointWithinEntityRadius_02069618(RangeNode *node, const VecFx32 *point);
extern BOOL IsPointInNodeRange_02069644(RangeNode *node, const VecFx32 *point);
extern BOOL func_ov001_020696c8(RangeNode *node, const VecFx32 *point);
extern BOOL PointInBox3D_02069718(RangeNode *node, const VecFx32 *point);
extern BOOL PointInBoxXZ_0206976c(RangeNode *node, const VecFx32 *point);
extern void func_ov001_020695b8(void);
extern void func_ov001_02069608(void);

void InitRangeTriggerNode_020697ac(RangeNode *node, RangeNodeParams *params)
{
    node->place = params->place;
    node->id = params->id;
    node->value = params->value;
    func_01ff8710(params->extent, node->extent, sizeof(node->extent));
    switch (params->shape) {
    case 0:
        node->test = IsPointWithinEntityRadius_02069618;
        break;
    case 1:
        node->test = IsPointInNodeRange_02069644;
        break;
    case 2:
        node->test = func_ov001_020696c8;
        break;
    case 3:
        node->test = PointInBox3D_02069718;
        break;
    case 4:
        node->test = PointInBoxXZ_0206976c;
        break;
    }
    node->update = func_ov001_020695b8;
    node->state = 0;
    node->release = func_ov001_02069608;
}
