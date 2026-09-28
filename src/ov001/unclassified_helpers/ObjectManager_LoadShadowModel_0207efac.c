#include "nitro/types.h"

typedef struct ShadowModel {
    u8 pad_00[0x78];
    void *resModel;
    u8 pad_7C[0x88];
} ShadowModel;

typedef struct ObjectManager {
    u8 pad_000[0x14];
    u8 flags;
    u8 pad_015[0x107];
    ShadowModel *shadowModel;
} ObjectManager;

extern ObjectManager *g_objectManager_020a04d8;
extern char s_shadowModelPath_0209f020[];
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void func_0202ecf8(void *dst, const char *path, void *info, int b);
extern void Model_SetAllMaterialAlpha_0201a900(void *resModel, int alpha);

void ObjectManager_LoadShadowModel_0207efac(void)
{
    ObjectManager *manager;

    manager = g_objectManager_020a04d8;
    manager->flags |= 2;
    manager->shadowModel = NNSi_FndAllocFromDefaultHeap_0202a178(sizeof(ShadowModel));
    func_0202ecf8(manager->shadowModel, s_shadowModelPath_0209f020, (void *)1, 3);
    Model_SetAllMaterialAlpha_0201a900(manager->shadowModel->resModel, 8);
}
