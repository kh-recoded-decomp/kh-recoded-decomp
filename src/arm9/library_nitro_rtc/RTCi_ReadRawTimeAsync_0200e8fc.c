extern void *RtcSendPxiCommand();

void *RTCi_ReadRawTimeAsync_0200e8fc() {
    return RtcSendPxiCommand(0x12);
}
