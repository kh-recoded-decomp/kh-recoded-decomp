#include "nitro/types.h"

typedef struct {
    u8 pad0[4];
    int target;
    u8 pad8[0xbc];
    int lockMode;
} LockOnInfo;

extern u32 func_0202f5b4(u32 anim, u32 speed);
extern BOOL IsBit0Set_020a9d1c(u32 *flags);

void SyncLockOnAnimSpeed_020cc1fc(int entity)
{
    LockOnInfo *lock = (LockOnInfo *)(entity + 0x274);
    u16 speed;
    int i;
    if (lock->lockMode == 2 && lock->target != 0) {
        speed = *(u16 *)(lock->target + 0x84);
        if (speed == 0) {
            if (*(u16 *)(*(int *)(entity + 0x230) + 0x100) != 0) {
                return;
            }
            speed = 0x7fff;
        }
        func_0202f5b4(*(int *)(entity + 0x230) + 4, speed);
        for (i = 0; i < 2; i++) {
            if (IsBit0Set_020a9d1c((u32 *)(entity + 0xb68 + i * 0x230))) {
                func_0202f5b4(entity + 0xb70 + i * 0x230, speed);
            }
        }
    }
}
