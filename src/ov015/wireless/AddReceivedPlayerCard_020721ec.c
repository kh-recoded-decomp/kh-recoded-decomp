#include "nitro/types.h"

typedef struct {
    u16 fieldF0 : 7;
    u16 fieldF4 : 4;
    u16 fieldF8 : 5;
} CardInfo;

typedef struct {
    u32 header[4];
    u8 ownName[0x16];
    u8 otherName[0x16];
    u8 pad_3C[0x20];
    CardInfo info;
    u8 macAddress[6];
    u8 pad_64[0xc];
} PlayerCard;

typedef struct {
    u8 pad_00[4];
    s8 cardCount;
    s8 macWriteIndex;
    u8 knownMacs[30][6];
    u8 pad_BA[0xe0 - 0xba];
    u8 lowBits : 2;
    u8 busy : 1;
    u8 midBits : 4;
    u8 newCardFlag : 1;
    u8 slotMask : 3;
    u8 highBitsE1 : 5;
    u8 pad_E2[0xf0 - 0xe2];
    int unk_F0;
    int unk_F4;
    int unk_F8;
    u8 pad_FC[0xcf58 - 0xfc];
    PlayerCard cards[3];
    u8 pad_D0A8[0xdeb8 - 0xd0a8];
    u32 slotCounters[3];
} WirelessContext;

extern void func_01ff89a8(const void *src, void *dst, u32 size);
extern void func_01ff869c(const void *src, void *dst, u32 size);
extern int func_ov002_02066c78(int query, int index, int arg2, void *out);
extern int compareByteStrings_02021c54(u8 *leftBytes, u8 *rightBytes, int length);
extern BOOL TestContextFlagBit_0206f460(int index);
extern void SetContextFlagBit_0206f418(int index);
extern BOOL MacAddressesEqual_0206f4f8(u8 *macA, u8 *macB);
extern WirelessContext *data_ov015_0207e960;

BOOL AddReceivedPlayerCard_020721ec(PlayerCard *incoming) {
    CardInfo info;
    PlayerCard card;
    PlayerCard existing;
    int i;
    int slot;
    int count;

    if (data_ov015_0207e960->busy) {
        return FALSE;
    }
    if (data_ov015_0207e960->cardCount >= 3) {
        return FALSE;
    }
    func_01ff89a8(incoming, &card, sizeof(PlayerCard));
    for (i = 0; i < 30; i++) {
        if (MacAddressesEqual_0206f4f8(card.macAddress, data_ov015_0207e960->knownMacs[i]) == TRUE) {
            return FALSE;
        }
    }
    count = func_ov002_02066c78(1, 0, 0, 0);
    for (i = 0; i < count; i++) {
        func_ov002_02066c78(0, i, 0, &existing);
        if (compareByteStrings_02021c54(existing.ownName, card.ownName, 0x16) == 0
            && compareByteStrings_02021c54((u8 *)existing.header, (u8 *)card.header, 0x10) == 0) {
            return FALSE;
        }
    }
    if (!TestContextFlagBit_0206f460(0)) {
        slot = 0;
    } else if (!TestContextFlagBit_0206f460(1)) {
        slot = 1;
    } else if (!TestContextFlagBit_0206f460(2)) {
        slot = 2;
    }
    SetContextFlagBit_0206f418(slot);
    func_01ff869c(incoming, &data_ov015_0207e960->cards[slot], sizeof(PlayerCard));
    info.fieldF0 = data_ov015_0207e960->unk_F0;
    info.fieldF4 = data_ov015_0207e960->unk_F4;
    info.fieldF8 = data_ov015_0207e960->unk_F8;
    data_ov015_0207e960->cards[slot].info = info;
    func_01ff89a8(data_ov015_0207e960->cards[slot].macAddress, data_ov015_0207e960->knownMacs[data_ov015_0207e960->macWriteIndex], 6);
    data_ov015_0207e960->slotCounters[slot] = 0;
    data_ov015_0207e960->newCardFlag = 1;
    data_ov015_0207e960->slotMask |= 1 << slot;
    data_ov015_0207e960->cardCount++;
    data_ov015_0207e960->macWriteIndex++;
    if (data_ov015_0207e960->macWriteIndex >= 30) {
        data_ov015_0207e960->macWriteIndex = 0;
    }
}
