#include "nitro/types.h"

extern u32 data_ov035_020bc4e0;
extern void StartIdleSceneObjects();
extern void func_ov001_02087650();

u32 func_ov040_020bd604(void)
{
    StartIdleSceneObjects();
    func_ov001_02087650(1);
    *(u16 *)(data_ov035_020bc4e0 + 6) = *(u16 *)(data_ov035_020bc4e0 + 6) | 0x20;
    return 0xf;
}
