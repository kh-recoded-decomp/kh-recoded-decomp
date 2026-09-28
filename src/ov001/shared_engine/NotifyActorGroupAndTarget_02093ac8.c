#include "nitro/types.h"

extern void func_ov001_0209c040(s16 groupId);
extern void func_ov001_0209c0c4(u16 targetId);

BOOL NotifyActorGroupAndTarget_02093ac8(u8 *actor)
{
    func_ov001_0209c040(*(s16 *)(actor + 0x10));
    func_ov001_0209c0c4(*(u16 *)(actor + 0x12));
    return FALSE;
}
