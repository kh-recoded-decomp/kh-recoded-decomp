#include "nitro/types.h"

typedef struct TargetInfo {
    u8 kind;
    u8 pad_01[0x13];
} TargetInfo;

typedef struct Manager {
    u8 pad_00[0x18];
    TargetInfo target;
} Manager;

extern Manager *gFieldTargetSelectionWork;
extern u32 GetTargetSelectionActiveMask(void);
extern BOOL ReadActiveMenuState(TargetInfo *target);
extern BOOL GetWaitTargetPosition(TargetInfo *target);

BOOL ResolveSelectedTargetPosition(void)
{
    Manager *manager = gFieldTargetSelectionWork;

    if (manager == NULL || GetTargetSelectionActiveMask() == 0) {
        return FALSE;
    }
    if (ReadActiveMenuState(&manager->target)) {
        return GetWaitTargetPosition(&manager->target);
    }
    return FALSE;
}
