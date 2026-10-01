#include "nitro/types.h"

#define REG_BG1OFS    (*(vu32 *)0x04000014)
#define REG_DB_BG0OFS (*(vu32 *)0x04001010)

typedef struct SlotEntry {
    u8 pad_00[0x8c];
    s32 ownerId;
    u8 pad_90[0x4];
    s32 unk_94;
    s32 unk_98;
} SlotEntry;

typedef struct SlotCard {
    u8 pad_000[0x12c];
    s32 unk_12C;
    u8 pad_130[0x8];
} SlotCard;

typedef struct SlotCursor {
    u8 pad_00[0x28];
    s32 unk_28;
    u8 pad_2C[0x24];
    s32 unk_50;
} SlotCursor;

typedef struct SlotScene {
    u8 pad_0000[0x1090];
    SlotEntry *slots;
    SlotCard *cards;
    SlotCursor *cursors;
    u8 pad_109C[0x30];
    s32 transitionFrame;
} SlotScene;

typedef struct SlotSceneHolder {
    u32 unk_00;
    SlotScene *scene;
} SlotSceneHolder;

extern SlotSceneHolder data_ov036_020c3920;
extern void func_01ff8830(void *dst, int value, int size);

void ResetSlotScene_020bb428(void)
{
    int i;
    SlotScene *scene = data_ov036_020c3920.scene;

    scene->transitionFrame = 0;
    func_01ff8830(scene->cursors, 0, 0xa8);
    REG_BG1OFS = 0;
    REG_DB_BG0OFS = 0;
    func_01ff8830(scene->slots, 0, 0x4e0);
    func_01ff8830(scene->cards, 0, 0x618);
    for (i = 0; i < 2; i++) {
        scene->cursors[i].unk_50 = -1;
        scene->cursors[i].unk_28 = scene->cursors[i].unk_50;
    }
    for (i = 0; i < 8; i++) {
        scene->slots[i].ownerId = -1;
        scene->slots[i].unk_98 = -1;
        scene->slots[i].unk_94 = scene->slots[i].unk_98;
    }
    for (i = 0; i < 5; i++) {
        scene->cards[i].unk_12C = -1;
    }
}
