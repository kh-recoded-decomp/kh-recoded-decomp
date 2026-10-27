#include "nitro/types.h"

#define OS_LOCK_ID_FIRST_BASE  0x40u
#define OS_LOCK_ID_SECOND_BASE 0x60u

typedef struct OSLockIdBitmaps {
    volatile u32 availableIds[2];
} OSLockIdBitmaps;

#define OS_LOCK_ID_BITMAPS ((OSLockIdBitmaps *)0x02ffffb0)

/* These caller-clobbered register bindings apply only to this leaf's file. */
register volatile u32 *sReleasedIdBitmap __asm("r3");
register u32 sReleasedIdMask __asm("r1");
register u32 sAvailableLockIds __asm("r2");

/* lockId must be an allocated ID in the range 0x40..0x7f. */
void OS_ReleaseLockID(u16 lockId)
{
    sReleasedIdBitmap = &OS_LOCK_ID_BITMAPS->availableIds[0];
    __schedule_barrier();

    u32 bitIndex;
    if ((s32)((u32)lockId - OS_LOCK_ID_SECOND_BASE) >= 0) {
        sReleasedIdBitmap++;
        __schedule_barrier();
        bitIndex = (u32)lockId - OS_LOCK_ID_SECOND_BASE;
    } else {
        bitIndex = (u32)lockId - OS_LOCK_ID_FIRST_BASE;
    }
    __schedule_barrier();

    sReleasedIdMask = 0x80000000u >> bitIndex;
    __schedule_barrier();
    sAvailableLockIds = *sReleasedIdBitmap;
    sAvailableLockIds |= sReleasedIdMask;
    *sReleasedIdBitmap = sAvailableLockIds;
}
