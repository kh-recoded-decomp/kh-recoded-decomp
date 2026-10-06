#include "nitro/types.h"

typedef struct TargetInfo {
    u8 kind;
    u8 pad_01[0x13];
} TargetInfo;

typedef struct Manager {
    u8 pad_00[0x18];
    TargetInfo target;
} Manager;

extern Manager *data_ov001_020a04a4;
extern u32 func_ov001_0206c2b8(void);
extern BOOL ReadActiveMenuState(TargetInfo *target);
extern BOOL GetWaitTargetPosition(TargetInfo *target);

BOOL func_ov001_0206c284(void)
{
    Manager *manager = data_ov001_020a04a4;

    if (manager == NULL || func_ov001_0206c2b8() == 0) {
        return FALSE;
    }
    if (ReadActiveMenuState(&manager->target)) {
        return GetWaitTargetPosition(&manager->target);
    }
    return FALSE;
}
