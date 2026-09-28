#include "nitro/types.h"

typedef struct TargetInfo {
    u8 kind;
    u8 pad_01[0x13];
} TargetInfo;

typedef struct Manager {
    u8 pad_00[0x18];
    TargetInfo target;
} Manager;

extern Manager *g_manager_020a0484;
extern u32 func_ov001_0206c2b8(void);
extern BOOL func_ov001_0206c328(TargetInfo *target);
extern BOOL func_ov001_0206c3f4(TargetInfo *target);

BOOL func_ov001_0206c284(void)
{
    Manager *manager = g_manager_020a0484;

    if (manager == NULL || func_ov001_0206c2b8() == 0) {
        return FALSE;
    }
    if (func_ov001_0206c328(&manager->target)) {
        return func_ov001_0206c3f4(&manager->target);
    }
    return FALSE;
}
