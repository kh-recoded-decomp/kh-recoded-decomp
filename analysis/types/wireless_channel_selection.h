/* BK9E overlay 15. Only observed fields are described. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct WirelessChannelState {
    u8 unknown00[4];
    u16 minimumOccupancy;
    u16 selectedChannel;
    u8 unknown08[4];
    u16 tiedChannels;
    u8 unknown0e[0x2a];
    u32 randomState;
} WirelessChannelState;

typedef struct WirelessChannelMeasurement {
    u16 apiId;
    u16 errorCode;
    u16 commandId;
    u16 commandResult;
    u16 channel;
    u16 occupancy;
} WirelessChannelMeasurement;

typedef void (*WirelessChannelCallback)(WirelessChannelMeasurement *result);
