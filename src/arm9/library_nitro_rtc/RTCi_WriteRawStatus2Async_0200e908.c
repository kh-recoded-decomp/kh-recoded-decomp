extern void *RtcSendPxiCommand();

void *RTCi_WriteRawStatus2Async_0200e908() {
    return RtcSendPxiCommand(0x27);
}
