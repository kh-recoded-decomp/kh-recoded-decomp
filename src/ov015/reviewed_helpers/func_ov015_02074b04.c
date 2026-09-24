/* Requests wireless channel measurement with a callback and fixed options.
 * Its return status is consumed by the next-channel routine. Adapted CC0 C from
 * Yokimitsuro/khdays-decomp, ab832f38b943c15f461228968a89002e1a99c03e,
 * src/overlays/ov105/calls/func_ov105_020bf480.c. */

typedef void (*WirelessChannelCallback)(void *result);
extern int func_020122d8(WirelessChannelCallback callback, int option3,
                        int option17, unsigned short channel, int option30);
int RequestWirelessChannelMeasurement(WirelessChannelCallback callback,
                                      unsigned short channel) {
    return func_020122d8(callback, 3, 0x11, channel, 0x1e);
}
