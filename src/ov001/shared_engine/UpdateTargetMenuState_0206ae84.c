#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct MenuRequest {
    u32 kind;
    u8 pad_04[0x4];
} MenuRequest;

typedef struct MenuContext {
    u32 flags;
    MenuRequest request;
    u8 pad_0c[0x20];
    fx32 fadeLevels[3];
} MenuContext;

typedef struct EntryCallbacks EntryCallbacks;

struct EntryCallbacks {
    u8 pad_000[0x21c];
    u32 (*getFlags)(EntryCallbacks *entry);
};

extern MenuContext *func_0202a764(void);
extern void UpdateStageEventMessage_0206c528(int id);
extern BOOL func_ov001_0206bc0c(void);
extern u32 func_ov001_02064490(void);
extern void ResetPendingRequest_0206c614(void);
extern EntryCallbacks *GetBoundedEntryField_0206db5c(int index);
extern BOOL FindNearestTargetInRange_0206af7c(MenuRequest *result, void *origin);
extern void SetMenuOpenState_0206bb74(int open, BOOL withSound);
extern void CloseMenuIfTargetLost_0206bc20(void);
extern void UpdateTargetMenu_0206bcbc(void);
extern void ApplyPendingTargetRequest_0206bdbc(void);

static inline fx32 StepFadeLevel(fx32 level)
{
    level += 0x1000;
    if (level > 0xf000) {
        level = 0xf000;
    } else if (level < 0) {
        level = 0;
    }
    return level;
}

int UpdateTargetMenuState_0206ae84(void)
{
    MenuContext *menu = func_0202a764();
    BOOL keepTarget;

    UpdateStageEventMessage_0206c528(-1);
    if (menu->flags & 4) {
        return 0;
    }
    if (func_ov001_0206bc0c() || func_ov001_02064490()) {
        ResetPendingRequest_0206c614();
        return 0;
    }
    keepTarget = TRUE;
    if (!(menu->flags & 2)) {
        keepTarget = FALSE;
        if (menu->request.kind == 1 || menu->request.kind == 3) {
            u32 entryFlags = 0;
            EntryCallbacks *entry = GetBoundedEntryField_0206db5c(0);

            if (entry->getFlags != NULL) {
                entryFlags = entry->getFlags(entry);
            }
            if (entryFlags & 4) {
                keepTarget = TRUE;
            }
        }
        if (!keepTarget) {
            if (FindNearestTargetInRange_0206af7c(&menu->request, NULL)) {
                SetMenuOpenState_0206bb74(TRUE, FALSE);
            } else {
                SetMenuOpenState_0206bb74(FALSE, FALSE);
            }
        }
    }
    if (keepTarget) {
        CloseMenuIfTargetLost_0206bc20();
    }
    if (menu->flags & 8) {
        UpdateTargetMenu_0206bcbc();
    }
    menu->fadeLevels[0] = StepFadeLevel(menu->fadeLevels[0]);
    menu->fadeLevels[1] = StepFadeLevel(menu->fadeLevels[1]);
    menu->fadeLevels[2] = StepFadeLevel(menu->fadeLevels[2]);
    ApplyPendingTargetRequest_0206bdbc();
    return 0;
}
