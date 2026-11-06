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

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void MIi_CpuCopy16(const void *src, void *dst, u32 size);
extern int DispatchContextCommand(int query, int index, int arg2, void *out);
extern int CompareByteStrings(u8 *leftBytes, u8 *rightBytes, int length);
extern BOOL TestContextFlagBit(int index);
extern void SetContextFlagBit(int index);
extern BOOL MacAddressesEqual(u8 *macA, u8 *macB);
extern WirelessContext *gWirelessMenuWork;

BOOL AddReceivedPlayerCard(PlayerCard *incoming) {
    CardInfo info;
    PlayerCard card;
    PlayerCard existing;
    int i;
    int slot;
    int count;

    if (gWirelessMenuWork->busy) {
        return FALSE;
    }
    if (gWirelessMenuWork->cardCount >= 3) {
        return FALSE;
    }
    MI_CpuCopy8(incoming, &card, sizeof(PlayerCard));
    for (i = 0; i < 30; i++) {
        if (MacAddressesEqual(card.macAddress, gWirelessMenuWork->knownMacs[i]) == TRUE) {
            return FALSE;
        }
    }
    count = DispatchContextCommand(1, 0, 0, 0);
    for (i = 0; i < count; i++) {
        DispatchContextCommand(0, i, 0, &existing);
        if (CompareByteStrings(existing.ownName, card.ownName, 0x16) == 0
            && CompareByteStrings((u8 *)existing.header, (u8 *)card.header, 0x10) == 0) {
            return FALSE;
        }
    }
    if (!TestContextFlagBit(0)) {
        slot = 0;
    } else if (!TestContextFlagBit(1)) {
        slot = 1;
    } else if (!TestContextFlagBit(2)) {
        slot = 2;
    }
    SetContextFlagBit(slot);
    MIi_CpuCopy16(incoming, &gWirelessMenuWork->cards[slot], sizeof(PlayerCard));
    info.fieldF0 = gWirelessMenuWork->unk_F0;
    info.fieldF4 = gWirelessMenuWork->unk_F4;
    info.fieldF8 = gWirelessMenuWork->unk_F8;
    gWirelessMenuWork->cards[slot].info = info;
    MI_CpuCopy8(gWirelessMenuWork->cards[slot].macAddress, gWirelessMenuWork->knownMacs[gWirelessMenuWork->macWriteIndex], 6);
    gWirelessMenuWork->slotCounters[slot] = 0;
    gWirelessMenuWork->newCardFlag = 1;
    gWirelessMenuWork->slotMask |= 1 << slot;
    gWirelessMenuWork->cardCount++;
    gWirelessMenuWork->macWriteIndex++;
    if (gWirelessMenuWork->macWriteIndex >= 30) {
        gWirelessMenuWork->macWriteIndex = 0;
    }
}
