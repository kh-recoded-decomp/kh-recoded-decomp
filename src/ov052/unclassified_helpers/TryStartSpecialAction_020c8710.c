#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xc];
    u16 flags;
} ActionSource;

typedef struct ActionActor ActionActor;

struct ActionActor {
    u8 pad_000[0x9ac];
    u64 stateFlags;
    u8 player;
    u8 pad_9b5[0x9c0 - 0x9b5];
    int mode;
    u8 pad_9c4[0x1034 - 0x9c4];
    s8 primarySlot;
    u8 pad_1035;
    s8 secondarySlot;
    u8 pad_1037[0x10ec - 0x1037];
    void (*changeMode)(ActionActor *actor, int mode);
};

extern void *func_ov001_0206db78(int player);
extern u16 GetId10_020a755c(void *self);
extern BOOL HasFlagsAt0xc_020a751c(void *holder, u16 mask);
extern BOOL AlarmCallback_020a7504(void *self);
extern BOOL IsPlayerEntryFlagSet_02050014(int player, u32 id);
extern BOOL AnySubObjectBit0Set_020cfb58(ActionActor *actor);
extern BOOL func_ov001_020645c8(u32 value);
extern void AddSessionCounter_02063a80(int index, int amount);
extern BOOL HandleMemberMenuInput_020d0524(ActionActor *actor);
extern BOOL ConsumeActionInterruptFlag_020cc274(ActionActor *actor);

BOOL TryStartSpecialAction_020c8710(ActionActor *actor)
{
    ActionSource *source = func_ov001_0206db78(actor->player);
    BOOL result = FALSE;
    int id = GetId10_020a755c(source);
    BOOL held = FALSE;
    int mode;

    if (IsPlayerEntryFlagSet_02050014(actor->player, 0x46) && id == 0) {
        if (IsPlayerEntryFlagSet_02050014(actor->player, 0x17)) {
            id = 1;
        } else {
            if (!IsPlayerEntryFlagSet_02050014(actor->player, 0x18)) {
                goto checked;
            }
            source->flags |= 0x400;
        }
        held = TRUE;
    }
checked:
    if (id == 1) {
        if (AnySubObjectBit0Set_020cfb58(actor) && !func_ov001_020645c8(0x3520)) {
            if (IsPlayerEntryFlagSet_02050014(actor->player, 0x17)) {
                if (!(actor->stateFlags & 0x800000000ULL)) {
                    AddSessionCounter_02063a80(7, 1);
                }
                actor->stateFlags |= 0x10100000;
            }
            actor->changeMode(actor, 0xc);
            result = TRUE;
        }
    } else {
        if (HandleMemberMenuInput_020d0524(actor)) {
            mode = 0;
            if (actor->primarySlot >= 0) {
                mode = 0x15;
            } else if (actor->secondarySlot >= 0) {
                mode = 0x17;
            }
            if (mode != 0) {
                actor->changeMode(actor, mode);
                if (ConsumeActionInterruptFlag_020cc274(actor)) {
                    result = TRUE;
                }
            }
            if (result && IsPlayerEntryFlagSet_02050014(actor->player, 0x18)) {
                if (!(actor->stateFlags & 0x800000000ULL)) {
                    AddSessionCounter_02063a80(7, 1);
                }
                actor->stateFlags |= 0x10000000;
            }
        }
        if (held) {
            source->flags &= ~0x400;
        }
    }
    if (!result && HasFlagsAt0xc_020a751c(source, 2)) {
        actor->changeMode(actor, 2);
        if (actor->mode == 2) {
            result = TRUE;
        }
    }
    if (!result && HasFlagsAt0xc_020a751c(source, 0x800) && IsPlayerEntryFlagSet_02050014(actor->player, 10)
        && AlarmCallback_020a7504(source)) {
        actor->changeMode(actor, 8);
        result = TRUE;
    }
    return result;
}
