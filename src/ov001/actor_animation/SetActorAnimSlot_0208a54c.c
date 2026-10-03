#include "nitro/types.h"

typedef struct AnimSlot {
    u8 pad_00[4];
    s16 animId;
    u8 pad_06[2];
    u32 param;
    char name[0x20];
} AnimSlot;

typedef struct AnimActor {
    u8 pad_000[0xd0];
    AnimSlot slots[6][5];
    u8 pad_5f8[0xd18 - 0x5f8];
    u8 **model;
    u8 pad_d1c[4];
    void *messages;
    u8 pad_d24[0xef4 - 0xd24];
    u32 flags;
    u8 pad_ef8[8];
    int entryIndex;
} AnimActor;

extern char data_ov001_0209f2f0[];

extern u32 GetBoundedEntryField_0206db5c(int index);
extern u8 *func_ov001_02088c1c(u32 entry);
extern void CommitPendingAnimationSwap_0202f5c8(u16 *state);
extern char *strcpy_02021e60(char *dst, const char *src);
extern int Strlen_02021e44(const char *str);
extern int strcmp_02021fa8(const char *str1, const char *str2);
extern void *Msg_OpenContainerAndReadHeader_0202cc6c(const char *name, u32 mode, BOOL allocFromEnd);
extern void func_ov001_02088d14(AnimActor *actor, int slot);
extern void func_ov001_0208a3e0(AnimActor *actor);
extern void func_ov001_02088b48(AnimActor *actor);

void SetActorAnimSlot_0208a54c(AnimActor *actor, const char *name, s16 animId, int slot, u32 param)
{
    BOOL inUse = FALSE;
    u16 *state;
    char buffer[0x20];
    int i;
    AnimSlot *entry;

    if (actor->flags & 0x4000) {
        state = (u16 *)(func_ov001_02088c1c(GetBoundedEntryField_0206db5c(actor->entryIndex)) + 8);
    } else {
        state = (u16 *)(*actor->model + 4);
    }
    if (*state & 4) {
        CommitPendingAnimationSwap_0202f5c8(state);
    }
    if (*name != '\0') {
        strcpy_02021e60(buffer, name);
        if (strcmp_02021fa8(&buffer[Strlen_02021e44(buffer) - 3], data_ov001_0209f2f0) == 0 && actor->messages == NULL) {
            actor->messages = Msg_OpenContainerAndReadHeader_0202cc6c(buffer, 0xd, FALSE);
        }
    } else {
        buffer[0] = '\0';
    }
    entry = &actor->slots[0][slot];
    entry->animId = animId;
    entry->param = param;
    strcpy_02021e60(entry->name, buffer);
    func_ov001_02088d14(actor, slot);
    for (i = 0; i < 6; i++) {
        actor->slots[i][slot].animId = -1;
    }
    for (i = 0; i < 5; i++) {
        if (actor->slots[0][i].animId != -1) {
            inUse = TRUE;
        }
    }
    if (!inUse) {
        actor->flags &= ~0x200;
    }
    if ((actor->flags & 0x80) && slot == 0) {
        func_ov001_0208a3e0(actor);
    }
    if (actor->flags & 0x40) {
        func_ov001_02088b48(actor);
    }
}
