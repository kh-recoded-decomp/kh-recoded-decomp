/* Selects a channel from the tied-channel bitmap, records it, and returns it after selecting idle state.
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
extern short SelectWirelessChannelFromBitmap(u16 bitmap);
u16 FinishWirelessChannelSelection(void) {
    SetWirelessState(1);
    channelState.selectedChannel = SelectWirelessChannelFromBitmap(channelState.tiedChannels);
    return channelState.selectedChannel;
}
