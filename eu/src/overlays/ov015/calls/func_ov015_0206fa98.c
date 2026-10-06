#include "nitro/types.h"

typedef struct {
    u8 data[0x70];
} PlayerCard;

typedef struct {
    u8 pad_0000[0xec];
    int selectedCard;
    u8 pad_00f0[0xcf58 - 0xf0];
    PlayerCard cards[1];
} WirelessContext;

extern int DispatchContextCommand(int a, int b, int c, int d);
extern int CountMatchingSlotIds(PlayerCard *card);
extern WirelessContext *data_ov015_0207e960;

void func_ov015_0206fa98(void) {
    int total;
    int bonus;

    total = DispatchContextCommand(8, 0, 0, 0) + 1;
    bonus = CountMatchingSlotIds(&data_ov015_0207e960->cards[data_ov015_0207e960->selectedCard]);
    if (DispatchContextCommand(5, 0, 0, 0) != 0) {
        return;
    }
    DispatchContextCommand(0x80000009, total + bonus, 0, 0);
}
