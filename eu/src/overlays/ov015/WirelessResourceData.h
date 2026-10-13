#ifndef KH_RECODED_WIRELESS_RESOURCE_DATA_H
#define KH_RECODED_WIRELESS_RESOURCE_DATA_H

#include "nitro/types.h"

/* The reward selector reads weight; GrantRewardEntry consumes the first
 * four halfwords and copies the whole 12-byte record into its output. */
enum {
    WIRELESS_REWARD_ITEM = 0,
    WIRELESS_REWARD_RANDOM_RECORD = 9
};

typedef struct WirelessRewardEntry {
    s16 type;
    s16 id;
    u16 level;
    u16 kind;
    u8 weight;
    u8 reserved09[3];
} WirelessRewardEntry;

/* Each tier contains five weighted rewards. The selector includes all tiers
 * up to the player's current tier when summing their weights. */
typedef struct WirelessResourceData {
    WirelessRewardEntry tiers[10][5];
} WirelessResourceData;

typedef char WirelessRewardEntrySizeCheck[(sizeof(WirelessRewardEntry) == 12) ? 1 : -1];
typedef char WirelessResourceDataSizeCheck[(sizeof(WirelessResourceData) == 600) ? 1 : -1];

extern const WirelessResourceData *gWirelessResourceTableA[10];
extern const WirelessResourceData *gWirelessResourceTableB[10];
extern const WirelessResourceData *gWirelessResourceTableC[10];
extern const WirelessResourceData *const *gWirelessResourceTables[7];

extern const WirelessResourceData gWirelessResourceDataA0;
extern const WirelessResourceData gWirelessResourceDataA1;
extern const WirelessResourceData gWirelessResourceDataA2;
extern const WirelessResourceData gWirelessResourceDataA3;
extern const WirelessResourceData gWirelessResourceDataA4;
extern const WirelessResourceData gWirelessResourceDataA5;
extern const WirelessResourceData gWirelessResourceDataA6;
extern const WirelessResourceData gWirelessResourceDataA7;
extern const WirelessResourceData gWirelessResourceDataA8;
extern const WirelessResourceData gWirelessResourceDataB0;
extern const WirelessResourceData gWirelessResourceDataB1;
extern const WirelessResourceData gWirelessResourceDataB2;
extern const WirelessResourceData gWirelessResourceDataB3;
extern const WirelessResourceData gWirelessResourceDataB4;
extern const WirelessResourceData gWirelessResourceDataB5;
extern const WirelessResourceData gWirelessResourceDataB6;
extern const WirelessResourceData gWirelessResourceDataB7;
extern const WirelessResourceData gWirelessResourceDataB8;
extern const WirelessResourceData gWirelessResourceDataC0;
extern const WirelessResourceData gWirelessResourceDataC1;
extern const WirelessResourceData gWirelessResourceDataC2;
extern const WirelessResourceData gWirelessResourceDataC3;
extern const WirelessResourceData gWirelessResourceDataC4;
extern const WirelessResourceData gWirelessResourceDataC5;
extern const WirelessResourceData gWirelessResourceDataC6;
extern const WirelessResourceData gWirelessResourceDataC7;
extern const WirelessResourceData gWirelessResourceDataC8;
extern const WirelessResourceData gWirelessResourceDataC9;

#endif
