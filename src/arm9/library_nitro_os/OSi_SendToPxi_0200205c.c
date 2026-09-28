extern int PXI_SendWordByFifo(int channel, int data, int flag);

void OSi_SendToPxi_0200205c(int data) {
    int payload = data << 8;
    int channel = 0xc;
    int zero = 0;
    while (PXI_SendWordByFifo(channel, payload, zero) != 0) {
        ;
    }
}
