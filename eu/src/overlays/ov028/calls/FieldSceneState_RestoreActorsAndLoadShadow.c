#include "nitro/types.h"

extern u32 gOv028FieldSceneWorkStorage;
extern s32 RestoreSessionActors(void);
extern void ObjectManager_LoadShadowModel(void);

u32 FieldSceneState_RestoreActorsAndLoadShadow(void)
{
    s32 result = RestoreSessionActors();

    if ((result == 1) && (*(s8 *)(gOv028FieldSceneWorkStorage + 8) != 3)) {
        *(u8 *)(gOv028FieldSceneWorkStorage + 8) = 0;
    }
    ObjectManager_LoadShadowModel();
    *(u16 *)(gOv028FieldSceneWorkStorage + 6) = *(u16 *)(gOv028FieldSceneWorkStorage + 6) | 0x8000;
    return 2;
}
