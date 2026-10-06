#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x32];
    u8 value;
} OverlayObject;

extern u32 ActorSlot_IsFlag8SetByIndex(u8 value);
extern void CacheEntry_SetActive(OverlayObject *obj, u32 value);

void func_ov017_020a5a98(OverlayObject *obj)
{
    u32 result = ActorSlot_IsFlag8SetByIndex(obj->value);
    CacheEntry_SetActive(obj, result);
}
