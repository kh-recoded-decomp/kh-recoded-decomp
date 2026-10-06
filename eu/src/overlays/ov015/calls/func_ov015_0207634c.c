#include "nitro/types.h"

extern void DestroyOwnedObjectList(void *ptr);
extern void DestroyObjectsAndRelease(void *ptr);
extern void FreePointerIfSet(void *ptr);
extern u8 *data_ov015_020812e0;

void func_ov015_0207634c(void) {
    DestroyObjectsAndRelease(data_ov015_020812e0 + 0x160);
    FreePointerIfSet(data_ov015_020812e0 + 0x65e0);
    DestroyOwnedObjectList(data_ov015_020812e0 + 0x65ec);
    DestroyOwnedObjectList(data_ov015_020812e0 + 0x65f0);
    DestroyOwnedObjectList(data_ov015_020812e0 + 0x65f4);
}
