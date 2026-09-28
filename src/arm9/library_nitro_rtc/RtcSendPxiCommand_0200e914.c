extern int PXI_SendWordByFifo(int channel, int data, int flag);

int RtcSendPxiCommand_0200e914(int cmd) {
    return PXI_SendWordByFifo(5, (cmd << 8) & 0x7f00, 0) >= 0;
}
