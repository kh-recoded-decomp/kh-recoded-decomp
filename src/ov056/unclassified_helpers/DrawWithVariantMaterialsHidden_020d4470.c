#include "nitro/types.h"

typedef struct {
    void *slots;
    s8 slotCount;
} EffectPool;

typedef struct {
    u8 pad_000[0xbc];
    void *model;
    u8 pad_0c0[0x18c - 0xc0];
    EffectPool effectPool;
    s32 variant;
} VariantActor;

extern void SetMaterialCullMode_0201a55c(void *model, u32 materialIndex, int cullMode);
extern void func_ov021_020aeb28(VariantActor *actor);
extern void func_ov056_020d7f18(EffectPool *pool);

void DrawWithVariantMaterialsHidden_020d4470(VariantActor *actor)
{
    int materialIndex;
    int endMaterial;
    int firstMaterial;

    if (actor->variant > 0) {
        switch (actor->variant) {
        case 1:
            firstMaterial = 5;
            endMaterial = 6;
            break;
        case 2:
            firstMaterial = 9;
            endMaterial = 15;
            break;
        case 3:
            firstMaterial = 9;
            endMaterial = 23;
            break;
        }
        for (materialIndex = firstMaterial; materialIndex < endMaterial; materialIndex++) {
            SetMaterialCullMode_0201a55c(actor->model, materialIndex, 0);
        }
    }
    func_ov021_020aeb28(actor);
    if (actor->variant > 0) {
        for (; firstMaterial < endMaterial; firstMaterial++) {
            SetMaterialCullMode_0201a55c(actor->model, firstMaterial, 3);
        }
    }
    func_ov056_020d7f18(&actor->effectPool);
}
