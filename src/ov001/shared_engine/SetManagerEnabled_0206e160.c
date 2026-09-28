#include "nitro/types.h"

typedef struct FieldManager {
    u8 pad_00[0x90];
    u32 enabled;
    u32 isActive;
    u32 activeTimer;
} FieldManager;

extern FieldManager *g_manager_020a049c;
extern void func_ov001_0206cab4(u32 enabled);
extern int func_ov001_020642a0(void);

void SetManagerEnabled_0206e160(u32 enabled)
{
    FieldManager *manager = g_manager_020a049c;

    if (manager != NULL) {
        manager->enabled = enabled;
        manager->isActive = 0;
        func_ov001_0206cab4(enabled);
        if (func_ov001_020642a0() != 0) {
            manager->isActive = 1;
            manager->activeTimer = 0;
        }
    }
}
