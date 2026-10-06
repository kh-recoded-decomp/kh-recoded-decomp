#include "nitro/types.h"

extern u32 data_ov028_020bb3a0;
extern s32 RestoreSessionActors(void);
extern void ObjectManager_LoadShadowModel(void);

u32 func_ov028_020ba6d4(void)
{
    s32 result = RestoreSessionActors();

    if ((result == 1) && (*(s8 *)(data_ov028_020bb3a0 + 8) != 3)) {
        *(u8 *)(data_ov028_020bb3a0 + 8) = 0;
    }
    ObjectManager_LoadShadowModel();
    *(u16 *)(data_ov028_020bb3a0 + 6) = *(u16 *)(data_ov028_020bb3a0 + 6) | 0x8000;
    return 2;
}
