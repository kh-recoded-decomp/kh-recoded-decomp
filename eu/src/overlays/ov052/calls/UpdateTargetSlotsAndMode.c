<<<<<<< HEAD
#define GetWaitTargetPosition_0206c3f4 GetWaitTargetPosition
#define InitSlotEntry_020d19f8 func_ov052_020d1a18
#define IsFlag10Set_020aa4b4 IsFlag10Set
#define IsObjHandleBit0Set_020aa4e4 IsObjHandleBit0Set
#define IsPlayerEntryFlagSet_02050014 IsPlayerEntryFlagSet
#define UpdateTargetSlotsAndMode_020cb6dc UpdateTargetSlotsAndMode
#define func_ov052_020cfdb4 func_ov052_020cfdd4
#define func_ov052_020cff8c ApplyAnimRootMotion
#define func_ov052_020d012c ProcessTargetHitEntries
#define func_ov052_020d0294 UpdateActionPhase
#define func_ov052_020d03b8 func_ov052_020d03d8
#include "src/ov052/unclassified_helpers/UpdateTargetSlotsAndMode_020cb6dc.c"
=======
#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Actor Actor;
typedef BOOL (*QueryFunc)(Actor *actor, int arg);
typedef void (*SetModeFunc)(Actor *actor, int mode);
typedef void (*ExitFunc)(Actor *actor, int arg, int value);

typedef struct {
    u8 pad0[0x3c];
    u32 flags;
} Target;

typedef struct {
    u8 pad0[0xc];
    VecFx32 position;
    u16 flags;
    u8 pad1a[6];
} SlotEntry;

typedef struct {
    int flags;
    u8 pad_04[0x5c];
    Target **target;
} ObjHandle;

struct Actor {
    u8 pad_0000[0x1f8];
    ExitFunc onModeExit;
    u8 pad_01fc[0x228 - 0x1fc];
    QueryFunc canWait;
    u8 pad_022c[0x234 - 0x22c];
    u32 flags;
    u8 pad_0238[0x768 - 0x238];
    BOOL modeChangePending;
    u8 pad_076c[0x9ac - 0x76c];
    u64 stateFlags;
    u8 player;
    u8 pad_09b5[0xfc8 - 0x9b5];
    ObjHandle handle;
    u8 pad_102c[0x1048 - 0x102c];
    u8 waitTarget[0x10ec - 0x1048];
    SetModeFunc setMode;
};

extern BOOL IsFlag10Set(int *flags);
extern BOOL IsObjHandleBit0Set(int *flags);
extern BOOL IsPlayerEntryFlagSet(int player, u32 id);
extern VecFx32 *GetWaitTargetPosition(void *wait);
extern void func_ov052_020cfdd4(Actor *actor, Target *target, BOOL mirrored);
extern void ApplyAnimRootMotion(Actor *actor, Target *target);
extern void func_ov052_020d1a18(SlotEntry *entry, Target *source, int mirrored, int player);
extern BOOL ProcessTargetHitEntries(Actor *actor, Target *target, SlotEntry *entry);
extern BOOL UpdateActionPhase(Actor *actor, Target *target, BOOL mirrored);
extern BOOL HandlePendingCommand(Actor *actor);

void UpdateTargetSlotsAndMode(Actor *actor)
{
    ObjHandle *handle = &actor->handle;
    Target *target = *handle->target;
    BOOL mirrored = IsFlag10Set(&handle->flags);
    SlotEntry entry;
    BOOL waiting;
    u32 flagSet;

    func_ov052_020cfdd4(actor, target, mirrored);
    ApplyAnimRootMotion(actor, target);
    func_ov052_020d1a18(&entry, target, mirrored, actor->player);
    entry.flags |= 0x100;
    if (ProcessTargetHitEntries(actor, target, &entry)) {
        return;
    }
    if (actor->canWait != NULL) {
        waiting = actor->canWait(actor, 0);
    } else {
        waiting = FALSE;
    }
    if (waiting && IsPlayerEntryFlagSet(actor->player, 0x30)) {
        entry.flags |= 2;
        entry.position = *GetWaitTargetPosition(actor->waitTarget);
        ProcessTargetHitEntries(actor, target, &entry);
    }
    if (UpdateActionPhase(actor, target, mirrored)) {
        return;
    }
    if (!actor->modeChangePending) {
        return;
    }
    flagSet = actor->flags & 4;
    if (HandlePendingCommand(actor)) {
        return;
    }
    if (flagSet) {
        if (IsObjHandleBit0Set(&handle->flags) && !(target->flags & 4)) {
            actor->setMode(actor, 1);
            if (actor->onModeExit != NULL) {
                actor->onModeExit(actor, 0, -1);
            }
            return;
        }
        actor->setMode(actor, 5);
        return;
    }
    if (!IsObjHandleBit0Set(&handle->flags)) {
        actor->stateFlags |= 0x100;
    }
    actor->setMode(actor, 4);
}
>>>>>>> 6429ce2ea7ff13b674e183a6843387d9844d00d4
