#include "nitro/types.h"

#define AlarmCallback func_ov021_020a7524

typedef struct ActionSource {
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

extern void *GetPlayerControlState(int player);
extern u16 SharedObject_GetId(void *self);
extern BOOL HasFlagsAt0xc(void *holder, u16 mask);
extern BOOL AlarmCallback(void *self);
extern BOOL IsPlayerEntryFlagSet(int player, u32 id);
extern BOOL AnySubObjectBit0Set(ActionActor *actor);
extern BOOL IsSessionFlagSet(u32 value);
extern void AddSessionCounter(int index, int amount);
extern BOOL HandleMemberMenuInput(ActionActor *actor);
extern BOOL ConsumeActionInterruptFlag(ActionActor *actor);

BOOL TryStartPlayerSpecialAction(ActionActor *actor)
{
    ActionSource *source = GetPlayerControlState(actor->player);
    BOOL result = FALSE;
    int id = SharedObject_GetId(source);
    BOOL held = FALSE;
    int mode;

    if (IsPlayerEntryFlagSet(actor->player, 0x46) && id == 0) {
        if (IsPlayerEntryFlagSet(actor->player, 0x17)) {
            id = 1;
        } else {
            if (!IsPlayerEntryFlagSet(actor->player, 0x18)) {
                goto checked;
            }
            source->flags |= 0x400;
        }
        held = TRUE;
    }
checked:
    if (id == 1) {
        if (AnySubObjectBit0Set(actor) && !IsSessionFlagSet(0x3520)) {
            if (IsPlayerEntryFlagSet(actor->player, 0x17)) {
                if (!(actor->stateFlags & 0x800000000ULL)) {
                    AddSessionCounter(7, 1);
                }
                actor->stateFlags |= 0x10100000;
            }
            actor->changeMode(actor, 0xc);
            result = TRUE;
        }
    } else {
        if (HandleMemberMenuInput(actor)) {
            mode = 0;
            if (actor->primarySlot >= 0) {
                mode = 0x15;
            } else if (actor->secondarySlot >= 0) {
                mode = 0x17;
            }
            if (mode != 0) {
                actor->changeMode(actor, mode);
                if (ConsumeActionInterruptFlag(actor)) {
                    result = TRUE;
                }
            }
            if (result && IsPlayerEntryFlagSet(actor->player, 0x18)) {
                if (!(actor->stateFlags & 0x800000000ULL)) {
                    AddSessionCounter(7, 1);
                }
                actor->stateFlags |= 0x10000000;
            }
        }
        if (held) {
            source->flags &= 0xfbff;
        }
    }
    if (!result && HasFlagsAt0xc(source, 2)) {
        actor->changeMode(actor, 2);
        if (actor->mode == 2) {
            result = TRUE;
        }
    }
    if (!result && HasFlagsAt0xc(source, 0x800)
            && IsPlayerEntryFlagSet(actor->player, 10)
            && AlarmCallback(source)) {
        actor->changeMode(actor, 8);
        result = TRUE;
    }
    return result;
}
