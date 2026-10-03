#include "nitro/types.h"

typedef struct ModelResource {
    u8 pad0[0x17];
    u8 jointCount;
    u8 pad18[0x28];
    u8 nameDict[4];
} ModelResource;

typedef struct AnimatedModel {
    u8 pad0[0x24];
    ModelResource *resource;
    u8 pad28[0x2c];
    void *jointWork;
    u8 pad58[0xac];
    void *jointBuffer;
    int rootJoint;
    u8 pad10c[0xc];
    int field118;
    int field11c;
    u8 pad120[4];
    int state;
    u8 pad128[0xc];
    u8 slot;
} AnimatedModel;

extern const char data_ov021_020b4fe4[];
extern void func_0202ecf8(AnimatedModel *model, int source, int flag, void *extra);
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern int FindResourceIndexByName_0201aafc(void *dict, const char *name);

void InitAnimatedModel_020ac864(AnimatedModel *model, int source, int slot)
{
    void *dict;
    void *buffer;
    int rootJoint;

    func_0202ecf8(model, source, 1, (u8 *)slot + 8);
    buffer = NNSi_FndAllocFromDefaultHeap_0202a178(model->resource->jointCount * 0x58);
    model->jointBuffer = buffer;
    model->jointWork = buffer;
    dict = model->resource != NULL ? model->resource->nameDict : NULL;
    if (dict != NULL) {
        rootJoint = FindResourceIndexByName_0201aafc(dict, data_ov021_020b4fe4);
    } else {
        rootJoint = -1;
    }
    model->rootJoint = rootJoint;
    model->state = 0;
    model->field11c = -1;
    model->slot = slot;
    model->field118 = 0;
}
