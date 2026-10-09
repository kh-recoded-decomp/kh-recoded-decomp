#include "nitro/types.h"

typedef struct {
    u8 id;
    u8 pad_01[0x11];
    u16 angle;
    u8 pad_14[0x10];
    u8 unk_24;
    u8 visible;
    s16 count;
    s16 prevIndex;
    s16 kind;
} MarkerRequest;

typedef struct {
    u8 pad_00[0xc];
    u16 flags;
} FieldUnit;

typedef struct Actor Actor;
typedef int (*StateGetter)(Actor *actor);
typedef void (*StateSetter)(Actor *actor, int state);

struct Actor {
    u8 pad_0000[0x1dc];
    int state;
    u8 pad_01e0[0x22c - 0x1e0];
    StateGetter getState;
    u8 pad_0230[0x9ac - 0x230];
    u64 flags;
    u8 player;
    u8 pad_09b5[0x9c4 - 0x9b5];
    int power;
    u8 pad_09c8[0xa44 - 0x9c8];
    int cooldown;
    u8 pad_0a48[0x1034 - 0xa48];
    s8 slotA;
    u8 pad_1035;
    s8 slotB;
    u8 pad_1037[0x10ec - 0x1037];
    StateSetter setState;
};

extern FieldUnit *func_ov001_0206db78(int player);
extern u16 GetId10_020a755c(FieldUnit *unit);
extern BOOL AnySubObjectBit0Set_020cfb58(Actor *actor);
extern BOOL func_ov001_020645c8(u32 value);
extern BOOL IsPlayerEntryFlagSet_02050014(int player, u32 id);
extern void AddSessionCounter_02063a80(int index, int amount);
extern BOOL HandleMemberMenuInput_020d0524(Actor *actor);
extern BOOL ConsumeActionInterruptFlag_020cc274(Actor *actor);
extern BOOL HasFlagsAt0xc_020a751c(FieldUnit *unit, u16 mask);
extern void func_ov021_020a8ab4(MarkerRequest *request);
extern int func_ov021_020a8ca0(MarkerRequest *request, int groupId);
extern int func_ov001_0206db8c(int index);
extern u16 GetLinkedAngleOffset_020ceb7c(Actor *actor);

static inline int GetActorState(Actor *actor)
{
    if (actor->getState != NULL) {
        return actor->getState(actor);
    }
    return actor->state;
}

BOOL TryStartChargedAction_020c88f4(Actor *actor)
{
    MarkerRequest request;
    BOOL ready;
    BOOL result;
    BOOL raised;
    FieldUnit *unit;
    BOOL handled;
    u16 id;
    int kind;
    int power;
    int cooldown;

    unit = func_ov001_0206db78(actor->player);
    handled = FALSE;
    power = actor->power;
    ready = FALSE;
    result = FALSE;
    cooldown = actor->cooldown;

    if (cooldown > 0) {
        return handled;
    }
    if (power < 0x9000) {
        return handled;
    }
    if (GetActorState(actor) == 4) {
        return FALSE;
    }
    id = GetId10_020a755c(unit);
    raised = FALSE;
    if (AnySubObjectBit0Set_020cfb58(actor) && !func_ov001_020645c8(0x3520)) {
        ready = TRUE;
    }
    if (ready && IsPlayerEntryFlagSet_02050014(actor->player, 0x47) && id == 0 && (actor->flags & 0x800000000ULL) == 0) {
        if (IsPlayerEntryFlagSet_02050014(actor->player, 0x11)) {
            id = 1;
        } else {
            if (!IsPlayerEntryFlagSet_02050014(actor->player, 0x19)) {
                goto checked;
            }
            unit->flags |= 0x400;
        }
        raised = TRUE;
    }
checked:
    if (ready) {
        if (id != 0) {
            if (id == 1) {
                if (AnySubObjectBit0Set_020cfb58(actor) && !func_ov001_020645c8(0x3520) && IsPlayerEntryFlagSet_02050014(actor->player, 0x11)) {
                    if ((actor->flags & 0x800000000ULL) == 0) {
                        AddSessionCounter_02063a80(7, 1);
                    }
                    actor->flags |= 0x10100000;
                    actor->setState(actor, 0xc);
                    handled = TRUE;
                }
            }
        } else {
            if (IsPlayerEntryFlagSet_02050014(actor->player, 0x19)) {
                if (HandleMemberMenuInput_020d0524(actor)) {
                    actor->flags |= 0x10000000;
                    kind = 0;
                    if (actor->slotA >= 0) {
                        kind = 0x15;
                    } else if (actor->slotB >= 0) {
                        kind = 0x17;
                    }
                    if (kind != 0) {
                        actor->setState(actor, kind);
                        if (ConsumeActionInterruptFlag_020cc274(actor)) {
                            result = TRUE;
                        }
                    }
                    if (result) {
                        if ((actor->flags & 0x800000000ULL) == 0) {
                            AddSessionCounter_02063a80(7, 1);
                        }
                        actor->flags |= 0x10000000;
                        handled = TRUE;
                    }
                }
                if (raised) {
                    unit->flags &= ~0x400;
                }
            }
        }
    }
    if (!handled && IsPlayerEntryFlagSet_02050014(actor->player, 0xf) && HasFlagsAt0xc_020a751c(unit, 2)) {
        actor->setState(actor, 0x14);
        handled = TRUE;
    }
    if (handled) {
        func_ov021_020a8ab4(&request);
        request.id = actor->player;
        request.visible = 1;
        result = TRUE;
        request.count = 1;
        request.unk_24 = 0;
        request.prevIndex = 0;
        request.kind = 0x37;
        request.angle = GetLinkedAngleOffset_020ceb7c(actor) + 0x8000;
        func_ov021_020a8ca0(&request, func_ov001_0206db8c(3));
    }
    return result;
}
