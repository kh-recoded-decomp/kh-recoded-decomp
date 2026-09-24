/* Seeds the channel-selection generator from MAC words and the shared frame counter, resets measurement state, and starts the first allowed channel.
 * Independently reconstructed from BK9E ARM instructions and call relocations. */
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
extern WirelessChannelState channelState;
extern void SetWirelessState(int state);
extern void ReadMacAddress(u8 *address);
extern void ReportWirelessResult(int result);
extern u16 MeasureNextAllowedWirelessChannel(u16 channel);
static inline u32 ReadFrameCounter(void) {
    return *(volatile u32 *)0x02fffc3c;
}
int BeginWirelessChannelMeasurement(void) {
    u16 mac[3];
    u16 result;
    ReadMacAddress((u8 *)mac);
    channelState.randomState = (((mac[0] + ReadFrameCounter()) + mac[1]) + mac[2]) * 69069U + 12345U;
    channelState.selectedChannel = 0;
    channelState.minimumOccupancy = 101;
    SetWirelessState(3);
    result = MeasureNextAllowedWirelessChannel(1);
    if (result == 24) {
        ReportWirelessResult(24);
        SetWirelessState(9);
        return 0;
    }
    if (result == 2) return 1;
    ReportWirelessResult(result);
    SetWirelessState(9);
    return 0;
}
