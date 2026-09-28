typedef void (*WirelessChannelCallback)(void *result);
extern int func_020122d8(WirelessChannelCallback callback, int option3,
                        int option17, unsigned short channel, int option30);
int RequestWirelessChannelMeasurement(WirelessChannelCallback callback,
                                      unsigned short channel) {
    return func_020122d8(callback, 3, 0x11, channel, 0x1e);
}
