#ifndef KH_RECODED_WIRELESS_RESOURCE_DATA_H
#define KH_RECODED_WIRELESS_RESOURCE_DATA_H

#include "nitro/types.h"

/* Fixed-size resource groups; individual halfword meanings remain unknown. */
typedef struct WirelessResourceData {
    u16 groups[10][30];
} WirelessResourceData;

typedef char WirelessResourceDataSizeCheck[(sizeof(WirelessResourceData) == 600) ? 1 : -1];

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
