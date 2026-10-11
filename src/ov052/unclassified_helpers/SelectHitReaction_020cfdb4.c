#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x4c];
    u16 low : 4;
    u16 backHit : 1;
    u16 mid : 2;
    u16 strength : 2;
    u16 high : 7;
} HitSource;

typedef struct {
    u8 pad_000[0x760];
    int frame;
    u8 pad_764[0x9ac - 0x764];
    u64 stateFlags;
    u8 player;
    u8 pad_9b5[0xfc8 - 0x9b5];
    u8 handle[0x1030 - 0xfc8];
    int reaction;
    u8 memberIndex;
    u8 pad_1035[0x1070 - 0x1035];
    u8 members[4];
} ReactActor;

extern void *func_ov001_0206db78(int player);
extern u16 GetId10_020a755c(void *self);
extern s32 GetFieldAt0x12_020a7560(void *obj);
extern BOOL HasFlagsAt0xc_020a751c(void *holder, u16 mask);
extern BOOL IsFrameInSubObjectRange_020aa568(void *obj, s32 frame, s32 which);
extern BOOL IsObjHandleOverLimit_020aa674(void *handle);
extern s32 func_ov021_020ad8c4(void *self);
extern BOOL CanUseMemberSlot_020d0600(ReactActor *entity, int index);
extern BOOL HandleMemberMenuInput_020d0524(ReactActor *actor);
extern BOOL func_ov001_02072040(void);
extern BOOL func_ov001_0206e2b0(void);
extern void func_ov001_0207e07c(void);
extern BOOL IsPlayerEntryFlagSet_02050014(int player, u32 id);

void SelectHitReaction_020cfdb4(ReactActor *actor, HitSource *source, s32 which)
{
    BOOL flag;
    int reaction;
    s32 index;
    void *handle;
    void *self = func_ov001_0206db78(actor->player);

    if (!(actor->stateFlags & 0x100) && GetId10_020a755c(self) == 5) {
        switch (GetFieldAt0x12_020a7560(self)) {
        case 1:
            reaction = 4;
            break;
        case 3:
            reaction = 5;
            break;
        default:
            goto checked;
        }
        actor->reaction = reaction;
    }
checked:
    if (source != NULL && !IsFrameInSubObjectRange_020aa568(source, actor->frame, which)) {
        if (func_ov001_02072040() && GetId10_020a755c(self) == 5
            && actor->reaction != 4 && actor->reaction != 5) {
            func_ov001_0207e07c();
        }
        return;
    }
    if (!(actor->stateFlags & 0x100)) {
        flag = FALSE;
        switch (GetId10_020a755c(self)) {
        case 1:
            handle = actor->handle;
            if (which != 0 || source->strength != 0) {
                flag = TRUE;
            } else if (IsObjHandleOverLimit_020aa674(handle)) {
                if (source->backHit) {
                    flag = TRUE;
                }
                if (actor->player != 0) {
                    flag = TRUE;
                }
                if (!func_ov001_0206e2b0() && IsPlayerEntryFlagSet_02050014(actor->player, 0x10d)) {
                    flag = TRUE;
                }
            }
            if (flag) {
                actor->reaction = 1;
            }
            break;
        case 7:
            index = func_ov021_020ad8c4(actor->members);
            if (CanUseMemberSlot_020d0600(actor, index)) {
                actor->memberIndex = index;
                actor->reaction = 7;
                actor->stateFlags |= 0x100;
            }
            break;
        case 0:
            if (HandleMemberMenuInput_020d0524(actor)) {
                actor->reaction = 6;
                actor->stateFlags |= 0x100;
            }
            break;
        }
        if (HasFlagsAt0xc_020a751c(self, 0x800)) {
            actor->reaction = 2;
        }
        if (HasFlagsAt0xc_020a751c(self, 2)) {
            actor->reaction = 3;
        }
    }
    if (func_ov001_02072040() && actor->reaction != 4 && actor->reaction != 5) {
        func_ov001_0207e07c();
    }
}
