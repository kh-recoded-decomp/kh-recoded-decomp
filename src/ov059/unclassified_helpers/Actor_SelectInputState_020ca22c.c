#include "nitro/types.h"

typedef struct Actor Actor;
typedef void (*ActorStateFunc)(Actor *actor, int state);

struct Actor {
    u8 pad_0000[0x930];
    u8 playerIndex;
    u8 pad_0931[0x944 - 0x931];
    int state;
    u8 pad_0948[0x1808 - 0x948];
    ActorStateFunc setState;
};

extern void *func_ov001_0206db78(u8 index);
extern s32 func_ov059_020c9880(Actor *actor);
extern BOOL HasFlagsAt0xc_020a751c(void *holder, u16 mask);
extern BOOL func_ov021_020a7504(void *target);
extern BOOL Actor_TryAcquireTargetAngle_020cb910(Actor *actor);
extern BOOL func_ov059_020cd154(Actor *actor);
extern BOOL func_ov001_020645c8(u32 value);
extern BOOL IsPlayerEntryFlagSet_02050014(int player, u32 id);
extern void func_ov059_020c9b6c(Actor *actor, void *input);

int Actor_SelectInputState_020ca22c(Actor *actor) {
    void *input = func_ov001_0206db78(actor->playerIndex);

    if (func_ov059_020c9880(actor) == 0) {
        if (HasFlagsAt0xc_020a751c(input, 2)) {
            actor->setState(actor, 2);
            if (actor->state == 2) {
                return 2;
            }
        }
        if (HasFlagsAt0xc_020a751c(input, 0x800)) {
            if (func_ov021_020a7504(input) && Actor_TryAcquireTargetAngle_020cb910(actor)) {
                actor->setState(actor, 5);
                if (actor->state == 5) {
                    return 5;
                }
            } else if (func_ov059_020cd154(actor) && !func_ov001_020645c8(0x3520)
                       && IsPlayerEntryFlagSet_02050014(actor->playerIndex, 11)) {
                actor->setState(actor, 6);
                if (actor->state == 6) {
                    return 6;
                }
            }
        }
        func_ov059_020c9b6c(actor, input);
    }
    return actor->state;
}
