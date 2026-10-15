#include "nitro/types.h"

typedef struct AnimSlot {
    u8 reserved00[4];
    s16 animationId;
    u8 reserved06[2];
    u32 parameter;
    char name[0x20];
} AnimSlot;

typedef struct AnimActor {
    u8 reserved000[0xd0];
    AnimSlot slots[6][5];
    u8 reserved5f8[0xd18 - 0x5f8];
    u8 **model;
    u8 reservedd1c[4];
    void *messages;
    u8 reservedd24[0xef4 - 0xd24];
    u32 flags;
    u8 reservedef8[8];
    int entryIndex;
} AnimActor;

typedef char AnimSlotSizeCheck[sizeof(AnimSlot) == 0x2c ? 1 : -1];
typedef char AnimActorFlagsOffsetCheck[
    (u32)&((AnimActor *)0)->flags == 0xef4 ? 1 : -1];

extern char sP2Extension_0209f310[];
extern u32 GetBoundedEntryField(int index);
extern u8 *GetActorFieldBySessionMode(u32 entry);
extern void CommitPendingAnimationSwap(u16 *state);
extern char *strcpy(char *destination, const char *source);
extern int strlen(const char *text);
extern int strcmp(const char *first, const char *second);
extern void *Msg_OpenContainerAndReadHeader(const char *name, u32 mode, BOOL allocFromEnd);
extern void ApplyActorAnimationRequest(AnimActor *actor, int slot);
extern void ClearActorTimerFields(AnimActor *actor);
extern void ClearActorFlagBit40(AnimActor *actor);

void SetActorAnimSlot(AnimActor *actor, const char *name, int animationId,
                      int slot, u32 parameter)
{
    BOOL inUse = FALSE;
    u16 *state;
    char buffer[0x20];
    int i;
    AnimSlot *entry;

    if (actor->flags & 0x4000) {
        state = (u16 *)(GetActorFieldBySessionMode(GetBoundedEntryField(actor->entryIndex)) + 8);
    } else {
        state = (u16 *)(*actor->model + 4);
    }
    if (*state & 4) {
        CommitPendingAnimationSwap(state);
    }
    if (*name != '\0') {
        strcpy(buffer, name);
        if (strcmp(&buffer[strlen(buffer) - 3], sP2Extension_0209f310) == 0
            && actor->messages == NULL) {
            actor->messages = Msg_OpenContainerAndReadHeader(buffer, 0xd, FALSE);
        }
    } else {
        buffer[0] = '\0';
    }
    entry = &actor->slots[0][slot];
    entry->animationId = animationId;
    entry->parameter = parameter;
    strcpy(entry->name, buffer);
    ApplyActorAnimationRequest(actor, slot);
    for (i = 0; i < 6; i++) {
        actor->slots[i][slot].animationId = -1;
    }
    for (i = 0; i < 5; i++) {
        if (actor->slots[0][i].animationId != -1) {
            inUse = TRUE;
        }
    }
    if (!inUse) {
        actor->flags &= ~0x200;
    }
    if ((actor->flags & 0x80) && slot == 0) {
        ClearActorTimerFields(actor);
    }
    if (actor->flags & 0x40) {
        ClearActorFlagBit40(actor);
    }
}
