#include "libs/nitro/os/os_mutex_internal.h"

/* Prefix of the scheduler's global storage. OSThreadInfo immediately follows
 * it at +0x1c and retains its existing allocation. */
typedef struct OSThreadSystemPrefix {
    u32 reserved00;
    u32 rescheduleCount;
    OSThread **currentThreadPtr;
    BOOL initialized;
    u32 reserved10[2];
    u32 threadIdCount;
} OSThreadSystemPrefix;

typedef char ThreadSystemPrefixMustBe28Bytes[
    sizeof(OSThreadSystemPrefix) == 28 ? 1 : -1];
typedef char ThreadInitializedMustStartAt12Bytes[
    (u32)&((OSThreadSystemPrefix *)0)->initialized == 12 ? 1 : -1];

OSThreadSystemPrefix OSi_ThreadSystemState;
