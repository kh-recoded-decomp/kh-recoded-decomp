extern int RtcSendPxiCommand_0200e914(int cmd);

int RTCi_TriggerAsyncCommand_0200e8f0(void) {
    return RtcSendPxiCommand_0200e914(0x11);
}
