#include "nitro/types.h"

typedef struct {
    s32 mode : 8;
    s32 rest : 24;
} ModeWord;

typedef struct {
    u8 pad_0000[0x934];
    ModeWord state;
    u8 active : 8;
    u8 pad_0939[0x15b4 - 0x939];
    u8 queue[0x1704 - 0x15b4];
    s32 timer;
    u8 pad_1708[0x181c - 0x1708];
    s16 groupId;
} Actor;

extern void EntryQueue_Clear_020cf3dc(void *queue);
extern u16 GetGroupSlotValue_020a8f1c(int groupId, int index);
extern void SetSlotEntryValue_020a8f4c(int groupId, int slot, int value);

void Actor_ExitCommandMode_020cb968(Actor *actor)
{
    int mode = actor->state.mode;

    if (mode == 2 || mode == 3) {
        EntryQueue_Clear_020cf3dc(actor->queue);
        if (actor->state.mode == 2) {
            actor->state.mode = 1;
            actor->active = 1;
            actor->timer = 0;
        } else {
            actor->state.mode = 0;
        }
        SetSlotEntryValue_020a8f4c(actor->groupId, 0, GetGroupSlotValue_020a8f1c(actor->groupId, 0) & ~4);
    } else if (mode == 4) {
        actor->state.mode = 0;
    }
}
